void get_ir_bat() {
  right_US_ir_Value = digitalRead(usirPin2);
  left_US_ir_Value = digitalRead(usirPin1);
  rawValue = analogRead(batteryPin);
  voltage = (float)rawValue / 4095.0 * 3.4;
  actualVoltage = voltage * (R1 + R2) / R2;
  server.send(200, "text/plain", String(right_US_ir_Value) + " " + String(left_US_ir_Value) + " " + String(actualVoltage));
}
void get_ir_us() {
  right_US_ir_Value = digitalRead(usirPin2);
  left_US_ir_Value = digitalRead(usirPin1);
  distance = sonar.ping_cm();
  server.send(200, "text/plain", String(right_US_ir_Value) + " " + String(left_US_ir_Value) + " " + String(distance));
}
void get_ir() {
  right_US_ir_Value = digitalRead(usirPin2);
  left_US_ir_Value = digitalRead(usirPin1);
  server.send(200, "text/plain", String(right_US_ir_Value) + " " + String(left_US_ir_Value));
}