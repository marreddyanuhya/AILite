
void blinkRed() {
  for (int i = 0; i < 10; i++) {  // Blink red 10 times

    setRedLed2();
    delay(500);  // 500ms on
   
    turnOffLed2();
    delay(500);  // 500ms off
  }

  // After blinking, set LEDs to constant red
  setRedLed2();
}


void blinkBlue() {
  for (int i = 0; i < 1; i++) {  // Blink blue 5 times
  
    setBlueLed2();
    delay(500);  // 500ms on

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


void setConstantmegentaLed2() {
  leds2[0] = CRGB(255, 0, 255);
  FastLED.show();
}


void setRedLed2() {
  leds2[0] = CRGB::Red;
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


void turnOffLed2() {
  leds2[0] = CRGB::Black;
  FastLED.show();
}
