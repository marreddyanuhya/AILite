void print_right_us_ir() {
  int right_US_ir_Value = digitalRead(usirPin2);
  Serial.print("Right US IR Value: ");
  Serial.println(right_US_ir_Value);
  //delay(1000);  // Add a delay for stability during debugging
  server.send(200, "text/plain", String("Right US IR Value: ") + String(right_US_ir_Value));
}

void print_left_us_ir() {
  int left_US_ir_Value = digitalRead(usirPin1);
  Serial.print("Left US IR Value: ");
  Serial.println(left_US_ir_Value);
  // delay(1000);  // Add a delay for stability during debugging
  server.send(200, "text/plain", String("Left US IR Value: ") + String(left_US_ir_Value));
}

void print_ultrasonic() {
  delay(50);
  float distance = sonar.ping_cm();
  int int_distance = int(distance); // Convert float to int
  Serial.print("Ping: ");
  Serial.print(int_distance);
  Serial.println("cm");
  server.send(200, "text/plain", String(int_distance));
}