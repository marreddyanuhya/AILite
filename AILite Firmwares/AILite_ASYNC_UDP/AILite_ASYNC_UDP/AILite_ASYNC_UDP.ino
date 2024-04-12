#include <WiFi.h>
#include <AsyncUDP.h>
#include <FastLED.h>
#include <ESP32Servo.h>
#include <Adafruit_TCS34725.h>
#include <NewPing.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid = "AILITE_ADVENTURER";
const char* password = "123456789";
const int udpPort = 12345;

#define motorpinLF1 14
#define motorpinLF2 16
#define motorpinLB1 32
#define motorpinLB2 33
#define motorpinRF1 19
#define motorpinRF2 17
#define motorpinRB1 25
#define motorpinRB2 26

const int motorEnablePin = 13;
int receivedSpeed_left = 190;
int receivedSpeed_right = 170;

#define LED_PIN_1 4
#define LED_PIN_2 15
#define NUM_LEDS 1
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int usirPin1 = 2;
const int usirPin2 = 23;
int left_US_ir_Value;
int right_US_ir_Value;

#define servoPin 22  // Servo control pin
Servo servo;

const int batteryPin = 39;
const float R1 = 150.0;
const float R2 = 560.0;

// Declare the readVoltage function
float readVoltage();

int rawValue;
float voltage;
float actualVoltage;
const float MIN_BATTERY_VOLTAGE = 3.2;
bool baterrystatus = true;

unsigned long previousMillis = 0;
const long interval = 1000;  // Interval for LED blinking

// Function prototypes
void Forward();
void Backward();
void Left();
void Right();
void Stop();
float readVoltage();
void blinkRed();  // Add function prototype if blinkRed() is defined elsewhere
void blinkcyan();
void setcyanLed2();
void setConstantGreenLed2();
void setServoAngle(int angle);  // Assuming this function exists

AsyncUDP udp;
int numClients = 0;

void setup() {
  Serial.begin(115200);
  // delay(1000); // No need for this delay

  pinMode(motorEnablePin, OUTPUT);
  digitalWrite(motorEnablePin, HIGH);

  pinMode(motorpinLF1, OUTPUT);
  pinMode(motorpinLF2, OUTPUT);
  pinMode(motorpinLB1, OUTPUT);
  pinMode(motorpinLB2, OUTPUT);
  pinMode(motorpinRF1, OUTPUT);
  pinMode(motorpinRF2, OUTPUT);
  pinMode(motorpinRB1, OUTPUT);
  pinMode(motorpinRB2, OUTPUT);

  servo.attach(servoPin);

  FastLED.addLeds<NEOPIXEL, LED_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_PIN_2>(leds2, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  IPAddress local_IP(192, 168, 80, 4);
  IPAddress gateway(192, 168, 80, 1);
  IPAddress subnet(255, 255, 255, 0);

  Serial.println("Setting up AILITE");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(ip);

  voltage = readVoltage();
  if (voltage < MIN_BATTERY_VOLTAGE) {
    baterrystatus = false;
    // blinkRed();  // Remove this line if blinkRed() is not defined
  } else {
    baterrystatus = true;
  }

  if (udp.listen(udpPort)) {
    Serial.println("UDP server started");
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.printf("Received %u bytes from %s, port %u\n", packet.length(), packet.remoteIP().toString().c_str(), packet.remotePort());

      // Allocate buffer of type uint8_t*
      uint8_t* packetBuffer = new uint8_t[packet.length() + 1];

      // Read packet data into buffer
      packet.read(packetBuffer, packet.length());
      packetBuffer[packet.length()] = 0;

      // Print packet contents
      Serial.printf("UDP packet contents: %s\n", (char*)packetBuffer);

      // Convert packetBuffer to String
      String command = (char*)packetBuffer;

      // Check the received message and perform corresponding actions
      if (command.startsWith("f(") || command.startsWith("b(") || command.startsWith("l(") || command.startsWith("r(")) {
        // Extract the direction and delay value from the command
        char direction = command.charAt(0);
        int openParenIndex = command.indexOf('(');
        int closeParenIndex = command.indexOf(')');
        if (openParenIndex != -1 && closeParenIndex != -1 && openParenIndex < closeParenIndex - 1) {
          String delayString = command.substring(openParenIndex + 1, closeParenIndex);
          int delayValue = delayString.toInt();
          if (delayValue > 0) {
            unsigned long currentMillis = millis();
            unsigned long previousMotorMillis = currentMillis;
            while (currentMillis - previousMotorMillis < delayValue) {
              currentMillis = millis();
              if (direction == 'f') {
                Forward();  // Execute forward function
              } else if (direction == 'b') {
                Backward();  // Execute backward function
              } else if (direction == 'l') {
                Left();  // Execute left function
              } else if (direction == 'r') {
                Right();  // Execute right function
              }
            }
            Stop();  // Stop the motor after the delay
            Serial.print("Command executed: ");
            Serial.println(command);
          } else {
            Serial.println("Invalid delay value");
          }
        } else {
          Serial.println("Invalid command format");
        }
      } else if (strcmp((char*)packetBuffer, "forward") == 0) {
        // Call function to move forward
        Forward();
      } else if (strcmp((char*)packetBuffer, "backward") == 0) {
        // Call function to move backward
        Backward();
      } else if (strcmp((char*)packetBuffer, "right") == 0) {
        // Call function to turn right
        Right();
      } else if (strcmp((char*)packetBuffer, "left") == 0) {
        // Call function to turn left
        Left();
      } else if (strcmp((char*)packetBuffer, "stop") == 0) {
        // Call function to stop
        Stop();
      } else if (strcmp((char*)packetBuffer, "servoright") == 0) {
        setServoAngle(20);
      } else if (strcmp((char*)packetBuffer, "servoleft") == 0) {
        setServoAngle(160);
      } else if (strcmp((char*)packetBuffer, "servocentre") == 0) {
        setServoAngle(90);
      } else if (strcmp((char*)packetBuffer, "US") == 0) {
        // Read ultrasonic sensor data
        int distance = sonar.ping_cm();

        // Construct response message
        String response = String(distance);

        // Send response back to the client
        udp.writeTo((const uint8_t*)response.c_str(), response.length(), packet.remoteIP(), packet.remotePort());

        // Print to serial monitor for debugging
        Serial.println(distance);
      } else if (strcmp((char*)packetBuffer, "IR") == 0) {
        // Read IR sensor data
        int left_IR_value = digitalRead(usirPin1);
        int right_IR_value = digitalRead(usirPin2);

        // Construct response message
        String response = String(left_IR_value) + "," + String(right_IR_value);

        // Send response back to the client
        udp.writeTo((const uint8_t*)response.c_str(), response.length(), packet.remoteIP(), packet.remotePort());

        // Print to serial monitor for debugging
        Serial.println("IR sensor data sent");
      } else if (strcmp((char*)packetBuffer, "IRUS") == 0) {
        // Read IR sensor data
        int left_IR_value = digitalRead(usirPin1);
        int right_IR_value = digitalRead(usirPin2);

        // Read ultrasonic sensor data
        int distance = sonar.ping_cm();

        // Construct response message
        String response = String(left_IR_value) + " " + String(right_IR_value) + " " + String(distance);

        // Send response back to the client
        udp.writeTo((const uint8_t*)response.c_str(), response.length(), packet.remoteIP(), packet.remotePort());

        // Print to serial monitor for debugging
        Serial.println("IRUS data sent");
      }

      else {
        // Invalid request received
        Serial.println("Invalid request received");
        // Optionally, you can send an error response back to the client
        // udp.writeTo((const uint8_t*)"Invalid request", 14, packet.remoteIP(), packet.remotePort());
      }
    });
  }
}

void loop() {
  numClients = WiFi.softAPgetStationNum();

  if (baterrystatus == true && numClients == 0) {
    blinkcyan();
  }
  if (baterrystatus == true && numClients == 1) {
    setcyanLed2();
  }
  if (baterrystatus == true && numClients == 2) {
    setConstantGreenLed2();
  }

  // Update FastLED
  FastLED.show();

  // Handle any other tasks that don't involve blocking delays
}
