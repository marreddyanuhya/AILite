#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <NewPing.h>
#include <FastLED.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

WebServer server(80);
String command;

const char *ssid = "AILITE_ADVENTURER";                                                                                                     
const char *password = "123456789";

IPAddress local_IP(192, 168, 60, 4);
IPAddress gateway(192, 168, 60, 1);                               
IPAddress subnet(255, 255, 255, 0);

#define motorpinLF1 14
#define motorpinLF2 16
#define motorpinLB1 32
#define motorpinLB2 33
#define motorpinRF1 19
#define motorpinRF2 17
#define motorpinRB1 25
#define motorpinRB2 26

#define encoderPinA1 36
#define encoderPinA2 35
#define encoderPinA3 34
#define encoderPinA4 27


// int leftIR;
// int rightIR;
// int ultrasonic;

const int motorEnablePin = 13;

int receivedSpeed_left = 216;
int receivedSpeed_right = 220;

const int batteryPin = 39;
const float R1 = 150.0;
const float R2 = 560.0;

int rawValue;
float voltage;
float actualVoltage;
const float MIN_BATTERY_VOLTAGE = 3.4;
bool baterrystatus = true;

const int usirPin1 = 23;
const int usirPin2 = 2;

int left_US_ir_Value;
int right_US_ir_Value;


#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;

// #define LED_PIN_1 4
#define LED_PIN_2 15
#define NUM_LEDS 1
// CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

#define servoPin 22  // Servo control pin
Servo servo;

int numClients = 0;

#define TCS3414CS_ADDRESS 0x29                                                                 //ColorSensor address 0x29
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Initializing ColorSensor


void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("AP Config Failed");
    return;
  }

  Serial.println("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();

  pinMode(batteryPin, INPUT);

  // FastLED.addLeds<NEOPIXEL, LED_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_PIN_2>(leds2, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

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
  delay(1000);


  voltage = readVoltage();
  if (voltage < MIN_BATTERY_VOLTAGE) {
    baterrystatus = false;
    blinkRed();
  } else {
    baterrystatus = true;
  }
}


void loop() {
  // readVoltage();
  server.handleClient();
  numClients = WiFi.softAPgetStationNum();
  // Serial.print("no of clients ");
  // Serial.println(numClients);
  if (baterrystatus == true && numClients == 0) {
    blinkcyan();
  }
  if (baterrystatus == true && numClients == 1) {
    setConstantGreenLed2();
  }
  if (baterrystatus == true && numClients == 2) {
    setConstantmegentaLed2();
  }
}
