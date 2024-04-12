void print_ultrasonic() {
  delay(50);
  float distance = sonar.ping_cm();
  int int_distance = int(distance); // Convert float to int
  Serial.print("Ping: ");
  Serial.print(int_distance);
  Serial.println("cm");
  
  // // Return the distance value
  // return int_distance;
}
