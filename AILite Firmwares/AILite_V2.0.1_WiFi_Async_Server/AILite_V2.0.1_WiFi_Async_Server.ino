#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NewPing.h>
#include <FastLED.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

AsyncWebServer server(80);
String command;
String page;

// Function prototypes
void HTTP_handleRoot(AsyncWebServerRequest *request);
void HTTP_handleCommand(AsyncWebServerRequest *request);
float readVoltage();
void print_right_us_ir();
void print_left_us_ir();
void print_ultrasonic();
void Forward();
void Backward();
void Left();
void Right();
void stop();
void blinkRed();
String ColorSensor();

// Global variables
const char *ssid = "AILITE_ASYN";
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
int receivedSpeed = 200;

const int batteryPin = 39;
const float R1 = 150.0;
const float R2 = 560.0;
int rawValue;
float voltage;
float actualVoltage;

const int irPin1 = 21;
const int irPin2 = 12;
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

const float MIN_BATTERY_VOLTAGE = 4.3;
bool clientConnected = false;
bool batterystatus = false;

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

  // Initialize FastLED
  FastLED.addLeds<NEOPIXEL, LED_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_PIN_2>(leds2, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  // Set up AsyncWebServer
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();

  // Set up motor pins
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

  // Check battery status
  float voltage = readVoltage();
  if (voltage < MIN_BATTERY_VOLTAGE) {
    batterystatus = false;
  } else {
    batterystatus = true;
    blinkRed();
  }
}


void loop() {
  if (batterystatus == false) {
    readVoltage();
  }

  int numClients = WiFi.softAPgetStationNum();

  if (actualVoltage > MIN_BATTERY_VOLTAGE) {
    batterystatus = true;

    if (numClients == 0) {
      blinkcyan(); // No clients connected
    }
    else if (numClients == 1) {
      setConstantYellowLed2(); // One client connected
    }
    else {
      setConstantGreenLed2(); // Multiple clients connected
    }

    if (numClients >= 1) {
      server.handleClient();
    }
  } else if (actualVoltage < MIN_BATTERY_VOLTAGE) {
    blinkRed(); // Low battery voltage  
  }
}
