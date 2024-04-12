void Forward() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed_left); // Change to receivedSpeed_left
  
}

void Backward() {
  analogWrite(motorpinLF1, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRB2, 0);
  
}

void Left() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinRF1, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRB2, 0);
  
}

void Right() {
  analogWrite(motorpinLF1, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, receivedSpeed_right); // Change to receivedSpeed_right
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, receivedSpeed_left); // Change to receivedSpeed_left
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, receivedSpeed_left); // Change to receivedSpeed_left
}


void Stop() {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, 0);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, 0);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, 0);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, 0);

}

void turn(int speedLeft, int speedRight) {
  analogWrite(motorpinLF1, 0);
  analogWrite(motorpinLF2, speedLeft);
  analogWrite(motorpinLB1, 0);
  analogWrite(motorpinLB2, speedLeft);
  analogWrite(motorpinRF1, 0);
  analogWrite(motorpinRF2, speedRight);
  analogWrite(motorpinRB1, 0);
  analogWrite(motorpinRB2, speedRight);
 
}

