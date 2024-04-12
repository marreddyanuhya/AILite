void defaultRGB(CRGB color) {
  leds1[0] = color;
  FastLED.show();
}

void blockRGB(CRGB leds[], CRGB color) {
  leds[0] = color;
  FastLED.show();
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
void setConstantmegentaLed2()
{
    leds2[0] = CRGB(255, 0, 255);
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

