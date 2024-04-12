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

IPAddress local_IP(192, 168, 80, 4);
IPAddress gateway(192, 168, 80, 1);
IPAddress subnet(255, 255, 255, 0);

#define motorpinLF1 14
#define motorpinLF2 16
#define motorpinLB1 32
#define motorpinLB2 33
#define motorpinRF1 19
#define motorpinRF2 17
#define motorpinRB1 25
#define motorpinRB2 26

const int motorEnablePin = 13;
int receivedSpeed = 150;

int receivedSpeed_left = 160;
int receivedSpeed_right = 155;

const int batteryPin = 39;
const float R1 = 150.0;
const float R2 = 560.0;

int rawValue;
float voltage;
float actualVoltage;
const float MIN_BATTERY_VOLTAGE = 3.4;
bool baterrystatus = true;

const int usirPin1 = 2;
const int usirPin2 = 23;

int ultrasonic;
#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define LED_PIN_1 4
#define LED_PIN_2 15
#define NUM_LEDS 1
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

int numClients = 0;

#define TCS3414CS_ADDRESS 0x29
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);
Servo myServo; // Declare myServo globally

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

  myServo.attach(27); // Servo Pin attached to 27

  FastLED.addLeds<NEOPIXEL, LED_PIN_1>(leds1, NUM_LEDS);
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

  voltage = readVoltage();
  if (voltage < MIN_BATTERY_VOLTAGE) {
    baterrystatus = false;
    blinkRed();  // Blink red if battery voltage is low
  } else {
    baterrystatus = true;
  }
}

void loop() {
  // readVoltage();

  numClients = WiFi.softAPgetStationNum();
  Serial.print("no of clients ");
  Serial.println(numClients);
  if (baterrystatus == true && numClients == 0) {
    blinkcyan();
    digitalWrite(motorEnablePin, LOW);
  }
  if (baterrystatus == true && numClients == 1) {
    setcyanLed2();
    server.handleClient();
    digitalWrite(motorEnablePin, HIGH);
  }
  if (baterrystatus == true && numClients == 2) {
    setConstantGreenLed2();
    server.handleClient();
    digitalWrite(motorEnablePin, HIGH);
  }
}
