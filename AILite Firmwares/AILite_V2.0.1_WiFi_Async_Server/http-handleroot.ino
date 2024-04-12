void HTTP_handleRoot(void) {
  Serial.println("HTTP_handleRoot called");
  // setConstantGreenLed1();
  setConstantGreenLed2();
  if (server.hasArg("cmd")) {
    command = server.arg("cmd");
    Serial.print("Received command: ");
    Serial.println(command);

    ////////////////////////////////////////// Motor Control Commands///////////////////////////////////
    if (command == "f") {
      Forward();
    } else if (command == "b") {
      Backward();
    } else if (command == "l") {
      Left();
    } else if (command == "r") {
      Right();
    } else if (command == "s") {
      stop();
    }
    /////////////////////////////////////////////RGB Commands///////////////////////////////////////////
    else if (command == "w") {
      blockRGB(leds1, CRGB::White);  // Change the color as needed for leds1
    } else if (command == "k") {
      // Command to set leds1 to Red
      blockRGB(leds1, CRGB::Red);
    } else if (command == "m") {
      // Command to set leds1 to green
      blockRGB(leds1, CRGB::Green);
    } else if (command == "n") {
      // Command to set leds1 to blue
      blockRGB(leds1, CRGB::Blue);
    } else if (command == "o") {
      // Command to set leds1 to magenta
      blockRGB(leds1, CRGB(255, 0, 255));
    } else if (command == "p") {
      // Command to set leds1 to yellow
      blockRGB(leds1, CRGB(255, 255, 0));
    } else if (command == "q") {
      // Command to set leds1 to violet
      blockRGB(leds1, CRGB(138, 43, 226));
    } else if (command == "off") {
      // Command to turn off leds1
      turnOffLed1();
    }
    //////////////////////////////////////////Bottom IR Sensors///////////////////////////////////////////
    else if (command == "RIR") {
      print_right_ir();
    } else if (command == "LIR") {
      print_left_ir();
    }
    /////////////////////////////////////Ultrasinic & IR Sensors//////////////////////////////////////////
    else if (command == "USRIR") {
      print_right_us_ir();
    } else if (command == "USLIR") {
      print_left_us_ir();
    } else if (command == "US") {
      print_ultrasonic();
    }
    ///////////////////////////////////////Speed Control///////////////////////////////////////////////////
    else if (command.startsWith("speed")) {
      // Extract the speed value from the command
      int speed = command.substring(6).toInt();  // Assuming "speedXX" where XX is the speed value
      if (speed >= 0 && speed <= 255) {          // Ensure speed is within valid range
        receivedSpeed = speed;
        Serial.print("Received speed: ");
        Serial.println(receivedSpeed);
      } else {
        Serial.println("Invalid speed value!");
      }
    }
    //////////////////////////////////////Servo control////////////////////////////////////////////////////
    else if (command.startsWith("angle=")) {
      // Extract the angle value from the command
      int angle = command.substring(6).toInt();  // Assuming "angleXX" where XX is the angle value
      if (angle >= 0 && angle <= 180) {          // Ensure angle is within valid range
        setServoAngle(angle);
      } else {
        Serial.println("Invalid angle value!");
      }
    }
    //////////////////////////////////////Battery Voltage //////////////////////////////////////////////////
    else if (command == "V") {
      readVoltage();
    }
    /////////////////////////////////Servo angle Control Commands///////////////////////////////////////////
    else if (command == "x") {
      setServoAngle(90);
    } else if (command == "y") {
      setServoAngle(160);
    } else if (command == "z") {
      setServoAngle(20);
    }
    server.send(200, "text/plain", "Command processed successfully");
  }
}