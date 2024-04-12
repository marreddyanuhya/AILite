float readVoltage() {
  rawValue = analogRead(batteryPin);
  voltage = (float)rawValue / 4095.0 * 3.4;
  actualVoltage = voltage * (R1 + R2) / R2;
  Serial.print("Voltage: ");
  Serial.println(actualVoltage);
  return actualVoltage;
}
   