void Forward() {
  analogWrite(motorpinLF1, receivedSpeed_left);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed_left);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, receivedSpeed_right);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed_right);
  analogWrite(motorpinRB2, 0);
}

// Function to move the robot backward
void Backward() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed_left);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed_left);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed_right);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed_right);
}

// Function to turn the robot left
void Left() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed_left);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed_left);
  analogWrite(motorpinRF1, receivedSpeed_right);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed_right);
  analogWrite(motorpinRB2, 0);
}

// Function to turn the robot right
void Right() {
  analogWrite(motorpinLF1, receivedSpeed_left);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed_left);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed_right);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed_right);
}

// Function to stop the robot
void stop() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, 0);
}


void cw90() {
  int receivedSpeed = 200;
  analogWrite(motorpinLF1, 0);  
  analogWrite(motorpinLF2, receivedSpeed);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed);
  analogWrite(motorpinRF1, receivedSpeed);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed);
  analogWrite(motorpinRB2, 0);
  delay(420);
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, 0);
}
void ccw90() {
  int receivedSpeed = 200;
  analogWrite(motorpinLF1, receivedSpeed);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed);
  delay(420);
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, 0);
}

