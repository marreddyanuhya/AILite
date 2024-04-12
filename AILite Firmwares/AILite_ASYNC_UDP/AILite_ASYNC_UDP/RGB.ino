
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


void blinkRed() {
  for (int i = 0; i < 10; i++) {  // Blink red 10 times
    setRedLed1();
    setRedLed2();
    delay(500);  // 500ms on
    turnOffLed1();
    turnOffLed2();
    delay(500);  // 500ms off
  }

  // After blinking, set LEDs to constant red
  setRedLed1();
  setRedLed2();
}


void setConstantGreenLed2() {
  leds2[0] = CRGB::Green;
  FastLED.show();
}


void setRedLed2() {
  leds2[0] = CRGB::Red;
  FastLED.show();
}


void setRedLed1() {
  leds1[0] = CRGB::Red;
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