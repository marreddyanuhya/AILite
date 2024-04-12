float readVoltage() {
  rawValue = analogRead(batteryPin);
  voltage = (float)rawValue / 4095.0 * 3.4;
  actualVoltage = voltage * (R1 + R2) / R2;
  Serial.print("Voltage: ");
  Serial.println(actualVoltage);
  server.send(200, "text/plain", String("Battery Voltage ") + String(actualVoltage));
  return actualVoltage;
}

void Forward() {
  analogWrite(motorpinLF1, receivedSpeed);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, receivedSpeed);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed);
  analogWrite(motorpinRB2, 0);
}

// Function to move the robot backward
void Backward() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed);
}

// Function to turn the robot left
void Left() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed);
  analogWrite(motorpinRF1, receivedSpeed);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed);
  analogWrite(motorpinRB2, 0);
}

// Function to turn the robot right
void Right() {
  analogWrite(motorpinLF1, receivedSpeed);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed);
}

// Function to stop the robot
void stop() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, 0);
}

void defaultRGB(CRGB color) {
  leds1[0] = color;
  FastLED.show();
}

void blockRGB(CRGB leds[], CRGB color) {
  leds[0] = color;
  FastLED.show();
}

void print_right_ir() {
  int rightValue = digitalRead(irPin2);
  Serial.print("right : ");
  Serial.println(rightValue);
  // delay(1000);
  server.send(200, "text/plain", String("Right IR Value: ") + String(rightValue));
}

void print_left_ir() {
  int leftValue = digitalRead(irPin1);
  Serial.print("left : ");
  Serial.println(leftValue);
  // delay(1000);
  server.send(200, "text/plain", String("Left IR Value: ") + String(leftValue));
}

void print_right_us_ir() {
  int right_US_ir_Value = digitalRead(usirPin2);
  Serial.print("Right US IR Value: ");
  Serial.println(right_US_ir_Value);
  //delay(1000);  // Add a delay for stability during debugging
  server.send(200, "text/plain", String("Right US IR Value: ") + String(right_US_ir_Value));
}

void print_left_us_ir() {
  int left_US_ir_Value = digitalRead(usirPin1);
  Serial.print("Left US IR Value: ");
  Serial.println(left_US_ir_Value);
  // delay(1000);  // Add a delay for stability during debugging
  server.send(200, "text/plain", String("Left US IR Value: ") + String(left_US_ir_Value));
}

void print_ultrasonic() {
  delay(50);
  float distance = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(distance);
  Serial.println("cm");
  server.send(200, "text/plain", String("U=") + String(distance));
}

void setServoAngle(int angle) {
  // Map the angle value to the servo range (0 to 180 degrees)
  int servoAngle = map(angle, 0, 180, 0, 180);
  servo.write(servoAngle);  // Set the servo position
}

void blinkRed() {
  for (int i = 0; i < 1; i++) {  // Blink red 5 times
    setRedLed1();
    setRedLed2();
    delay(500);  // 500ms on
    turnOffLed1();
    turnOffLed2();
    delay(500);  // 500ms off
  }
}

void blinkBlue() {
  for (int i = 0; i < 1; i++) {  // Blink blue 5 times
    setBlueLed1();
    setBlueLed2();
    delay(500);  // 500ms on
    turnOffLed1();
    turnOffLed2();
    delay(500);  // 500ms off
  }
}

void blinkcyan() {
  for (int i = 0; i < 1; i++) {  // Blink blue 5 times
    // setmagentaLed1();
    setcyanLed2();
    delay(500);  // 500ms on
    // turnOffLed1();
    turnOffLed2();
    delay(500);  // 500ms off
  }
}

void setConstantGreenLed2() {
  leds2[0] = CRGB::Green;
  FastLED.show();
}

void setConstantYellowLed2() {
 leds2[0] = CRGB(255, 255, 0);
  FastLED.show();
}

void setRedLed1() {
  leds1[0] = CRGB::Red;
  FastLED.show();
}

void setRedLed2() {
  leds2[0] = CRGB::Red;
  FastLED.show();
}

void setBlueLed1() {
  leds1[0] = CRGB::Blue;
  FastLED.show();
}

void setBlueLed2() {
  leds2[0] = CRGB::Blue;
  FastLED.show();
}

void setcyanLed2() {
  leds2[0] = CRGB(0, 255, 255);
  FastLED.show();
}

void turnOffLed1() {
  leds1[0] = CRGB::Black;
  FastLED.show();
}

void turnOffLed2() {
  leds2[0] = CRGB::Black;
  FastLED.show();
}
