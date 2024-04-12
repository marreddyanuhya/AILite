float readVoltage() {
  rawValue = analogRead(batteryPin);
  voltage = (float)rawValue / 4095.0 * 3.28;
  actualVoltage = voltage * (R1 + R2) / R2;
  Serial.print("Voltage: ");
  Serial.println(actualVoltage);
  server.send(200, "text/plain", String("Battery Voltage ") + String(actualVoltage));
  return actualVoltage;
}
   