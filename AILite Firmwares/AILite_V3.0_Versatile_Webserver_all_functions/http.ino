void HTTP_handleRoot(void) {
  Serial.println("HTTP_handleRoot called");

  if (server.hasArg("cmd")) {
    String command = server.arg("cmd");
    Serial.print("Received command: ");
    Serial.println(command);

    // Check if the command starts with the respective letter and is followed by a delay value in parentheses
    if (command.startsWith("f(") || command.startsWith("b(") || command.startsWith("l(") || command.startsWith("r(")) {
      // Extract the direction and delay value from the command
      char direction = command.charAt(0);
      int openParenIndex = command.indexOf('(');
      int closeParenIndex = command.indexOf(')');
      if (openParenIndex != -1 && closeParenIndex != -1 && openParenIndex < closeParenIndex - 1) {
        String delayString = command.substring(openParenIndex + 1, closeParenIndex);
        int delayValue = delayString.toInt();
        if (delayValue > 0) {
          if (direction == 'f') {
            Forward();  // Execute forward function
          } else if (direction == 'b') {
            Backward();  // Execute backward function
          } else if (direction == 'l') {
            Left();  // Execute left function
          } else if (direction == 'r') {
            Right();  // Execute right function
          }
          delay(delayValue);  // Delay for the specified time (in milliseconds)
          stop();             // Stop the motor after the delay
          Serial.print("Command executed: ");
          Serial.println(command);
          server.send(200, "text/plain", "Command executed successfully");
        } else {
          Serial.println("Invalid delay value");
          server.send(400, "text/plain", "Invalid delay value");
        }
      } else {
        Serial.println("Invalid command format");
        server.send(400, "text/plain", "Invalid command format");
      }
    }
    //////////////////////////////////////////////Motor Control////////////////////////////////////////////
    else if (command == "s") {
      stop();  // Handle stop command
      Serial.println("Stop command executed");
      server.send(200, "text/plain", "Stop command executed");
    } else if (command == "f") {
      Forward();
    } else if (command == "b") {
      Backward();
    } else if (command == "l") {
      Left();
    } else if (command == "r") {
      Right();
    }
    //////////////////////////////////////////////Ultrasonic Block//////////////////////////////////////////
    else if (command == "USRIR") {
      print_right_us_ir();
    } else if (command == "USLIR") {
      print_left_us_ir();
    } else if (command == "US") {
      print_ultrasonic();
    }
    // /////////////////////////////////////////////RGB Commands///////////////////////////////////////////
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
    //////////////////////////////////////////Speed Control////////////////////////////////////////////////////
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
    /////////////////////////////////////////Battery Voltage/////////////////////////////////////////////////////
    else if (command == "V") {
      readVoltage();
    }
    /////////////////////////////////////////Bot 90 degree right and left////////////////////////////////////////
    else if (command == "cw90") {
      cw90();
    } else if (command == "ccw90") {
      ccw90();
    }
    ////////////////////////////////////////////Color Sensor/////////////////////////////////////////////////////
    else if (command == "cs") {
      String frontColor = ColorSensor();
      server.send(200, "text/plain", String("Front Color: ") + frontColor);
    }
    ////////////////////////////////////////////Servo control////////////////////////////////////////////////////
    else if (command.startsWith("angle=")) {
      // Extract the angle value from the command
      int angle = command.substring(6).toInt();  // Assuming "angleXX" where XX is the angle value
      if (angle >= 0 && angle <= 180) {          // Ensure angle is within valid range
        setServoAngle(angle);
      } else {
        Serial.println("Invalid angle value!");
      }
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
  } else {
    Serial.println("Invalid command");
    server.send(400, "text/plain", "Invalid command");
  }
}

