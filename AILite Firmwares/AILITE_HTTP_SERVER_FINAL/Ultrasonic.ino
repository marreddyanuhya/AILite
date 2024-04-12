
void print_ultrasonic() {
  delay(50);
  distance = sonar.ping_cm();
  int int_distance = int(distance);  // Convert float to int
  Serial.print("Ping: ");
  Serial.print(int_distance);
  Serial.println("cm");
  server.send(200, "text/plain", String(int_distance));
}


