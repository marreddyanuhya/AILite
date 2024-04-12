
// ColorSensor Function
String ColorSensor() {
  uint16_t r, g, b, c;
  tcs1.getRawData(&r, &g, &b, &c);

  // Print raw color values
  Serial.print("Front - Red: ");
  Serial.print(r);
  Serial.print(", Green: ");
  Serial.print(g);
  Serial.print(", Blue: ");
  Serial.print(b);
  Serial.print(", Clear: ");
  Serial.println(c);

  // Determine the dominant color based on raw data

  // Adjusted thresholds for color detection
  const int threshold = 300; // Adjust as needed
  
  if (r > threshold && g < threshold && b < threshold) {
    return "Red";
  } else if (r < threshold && g > threshold && b < threshold) {
    return "Green";
  } else if (r < threshold && g < threshold && b > threshold) {
    return "Blue";
  } else if (r < threshold && g < threshold && b < threshold) {
    return "Black";
  } else if (r > threshold && g > threshold && b > threshold) {
    return "White";
  } else {
    return "No dominant color";
  }
}
