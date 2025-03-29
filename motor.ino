int const FLMT1 = 2 ;
int const FLMT2 = 3 ;
int const FRMT1 = 4 ;
int const FRMT2 = 5 ;
int const BLMT1 = 6 ;
int const BLMT2 = 7 ;
int const BRMT1 = 8 ;
int const BRMT2 = 9 ;
int distance;
void setup() {
  Serial.begin(9600);
  for(int i = 2; i <= 9; i++) pinMode(i, OUTPUT);
}

void motordrive() {
  digitalWrite(FLMT1, HIGH); digitalWrite(FLMT2, LOW);
  digitalWrite(FRMT1, HIGH); digitalWrite(FRMT2, LOW);
  digitalWrite(BLMT1, LOW); digitalWrite(BLMT2, HIGH);
  digitalWrite(BRMT1, LOW); digitalWrite(BRMT2, HIGH);
}
void stopMotors() {
  // Stop all motors
  digitalWrite(FLMT1, LOW); digitalWrite(FLMT2, LOW);
  digitalWrite(FRMT1, LOW); digitalWrite(FRMT2, LOW);
  digitalWrite(BLMT1, LOW); digitalWrite(BLMT2, LOW);
  digitalWrite(BRMT1, LOW); digitalWrite(BRMT2, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the distance from the first board
    distance = Serial.parseInt();
    Serial.print("Distance received: ");
    Serial.println(distance);

    // Control motors based on distance
    if (distance < 7) {
      motordrive();
        // Stop if object is too close
    } else {
      stopMotors();// Move if safe
    }
  }
}


