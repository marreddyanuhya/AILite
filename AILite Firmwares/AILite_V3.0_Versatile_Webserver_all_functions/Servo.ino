void setServoAngle(int angle) {
  // Map the angle value to the servo range (0 to 180 degrees)
  int servoAngle = map(angle, 0, 180, 0, 180);
  myServo.write(servoAngle);  // Set the servo position
}
