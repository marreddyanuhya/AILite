void HTTP_handleRoot(void) {
  //Serial.println("HTTP_handleRoot called");

  if (server.hasArg("cmd")) {
    String command = server.arg("cmd");
    Serial.print("Received command: ");
    Serial.println(command);
///////////////////////////////////////////////////////////MOTOR WITH DELAY/////////////////////////////////////////////////
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
    /////////////////////////////////////////////////SERVO ANGLE CONTROL////////////////////////////////////////////////////

    else if (command.startsWith("servo(") && command.endsWith(")")) {
      int openParenIndex = command.indexOf('(');
      int closeParenIndex = command.indexOf(')');
      if (openParenIndex != -1 && closeParenIndex != -1 && openParenIndex < closeParenIndex - 1) {
        String angleString = command.substring(openParenIndex + 1, closeParenIndex);
        int angle = angleString.toInt();
        if (angle >= 0 && angle <= 180) {
          setServoAngle(angle);  // Set the servo angle
          Serial.print("Servo angle set to: ");
          Serial.println(angle);
          server.send(200, "text/plain", "Servo angle set successfully");
        } else {
          Serial.println("Invalid servo angle value");
          server.send(400, "text/plain", "Invalid servo angle value");
        }
      } else {
        Serial.println("Invalid command format");
        server.send(400, "text/plain", "Invalid command format");
      }
    } 
    /////////////////////////////////////////////////MOTOR CONTROL/////////////////////////////////////////////////////////

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
    /////////////////////////////////////////////////ULTRASONIC BLOCK////////////////////////////////////////////////////////

    else if (command == "USRIR") {
      print_right_us_ir();
    } else if (command == "USLIR") {
      print_left_us_ir();
    } else if (command == "US") {
      print_ultrasonic();
    } 
    /////////////////////////////////////////////////BATTERY VOLTAGE//////////////////////////////////////////////////////////

    else if (command == "V") {
      readVoltage();
    } 
    /////////////////////////////////////////////////CUSTOM FUNCTIONS/////////////////////////////////////////////////////////

    else if (command == "getirbat") {
      get_ir_bat();
    } else if (command == "getirus") {
      get_ir_us();
    } else if (command == "getir") {
      get_ir();
    } 
    ////////////////////////////////////////////////////SERVO CONTROL/////////////////////////////////////////////////////////

    else if (command == "x") {
      setServoAngle(90);
    } else if (command == "y") {
      setServoAngle(160);
    } else if (command == "z") {
      setServoAngle(20);
    } 
    /////////////////////////////////////////////////////COLOR SENSOR//////////////////////////////////////////////////////////
    
    else if (command == "cs") {
      String frontColor = ColorSensor();
      server.send(200, "text/plain", String("Front Color: ") + frontColor);
    } 
    /////////////////////////////////////////////////////MOTOR SPEED CONTROL////////////////////////////////////////////////////
    
    else if (command.startsWith("left_speed=")) {
      // Extract the speed value after the "=" sign
      String speedValue = command.substring(11);
      // Convert the extracted string to an integer and assign it to receivedSpeed_left
      receivedSpeed_left = speedValue.toInt();
      // Respond with a success message
      server.send(200, "text/plain", "Left motor speed set successfully");
    } else if (command.startsWith("right_speed=")) {
      // Extract the speed value after the "=" sign
      String speedValue = command.substring(12);
      // Convert the extracted string to an integer and assign it to receivedSpeed_right
      receivedSpeed_right = speedValue.toInt();
      // Respond with a success message
      server.send(200, "text/plain", "Right motor speed set successfully");
    } else {
      Serial.println("Invalid command");
      server.send(400, "text/plain", "Invalid command");
    }
  }
}
