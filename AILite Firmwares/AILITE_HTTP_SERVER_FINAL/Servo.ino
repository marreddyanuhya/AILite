
void setServoAngle(int angle) {
  // Map the angle value to the servo range (0 to 180 degrees)
  int servoAngle = map(angle, 0, 180, 0, 180);
  servo.write(servoAngle);  // Set the servo position

  // Add a delay to control the speed of servo movement
  delay(2000); // Adjust the delay time as needed
  server.send(200, "text/plain", "servo command executed");
}
