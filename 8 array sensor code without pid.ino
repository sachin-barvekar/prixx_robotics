// Left sensors value initialization
int s1 = 0; // D0-->Pin2
int s2 = 0;
int s3 = 0;

// Middle sensors value initialization
int s4 = 0; // D3-->Pin5
int s5 = 0;

// Right sensors value initialization
int s6 = 0;
int s7 = 0;
int s8 = 0; // D7-->Pin9

#define led 13
// Motor Speed PWM
int spd = 85;

// Motor Pin Declaration Left Motor
const int lmf = A5;
const int lmb = A4;

// Motor Pin Declaration Right Motor
const int rmf = A2;
const int rmb = A3;

// Speed controller PWM pins for both motors
#define lpwm 10
#define rpwm 11 // Changed from 10 to 11

void setup() {
  Serial.begin(9600); // Initialize serial communication
  // Pin 2,3,4,5,6,7,8,9 are for sensor array(D0,D1,D2,D3,D4,D5,D6,D7,D8), Set as input
  for (int i = 2; i <= 9; i++) {
    pinMode(i, INPUT);
  }
  // Motor pin set for output
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);

  // PWM pins as output
  pinMode(lpwm, OUTPUT);
  pinMode(rpwm, OUTPUT);
}

void loop() {
  // Reading sensor array value
  s1 = digitalRead(2);
  s2 = digitalRead(3);
  s3 = digitalRead(4);
  s4 = digitalRead(5);
  s5 = digitalRead(6);
  s6 = digitalRead(7);
  s7 = digitalRead(8);
  s8 = digitalRead(9);

  // Print sensor values to serial monitor
  Serial.print("Sensor Values: ");
  Serial.print(s1);
  Serial.print(", ");
  Serial.print(s2);
  Serial.print(", ");
  Serial.print(s3);
  Serial.print(", ");
  Serial.print(s4);
  Serial.print(", ");
  Serial.print(s5);
  Serial.print(", ");
  Serial.print(s6);
  Serial.print(", ");
  Serial.print(s7);
  Serial.print(", ");
  Serial.println(s8);

  // Forward
  if (s4 == 1 || s5 == 1) { // Reverse logic: black line detected (HIGH)
    forward();
    digitalWrite(led, HIGH);
  }

  // Right
  if (s6 == 1 && s7 == 1 || s8 == 1) { // Reverse logic: black line detected (HIGH)
    left();
    //right();
    digitalWrite(led, LOW);
  }
  // Left
  if (s1 == 1 || s2 == 1 && s3 == 1) { // Reverse logic: black line detected (HIGH)
    right();
    digitalWrite(led, LOW);
  }

  if ((s1 == 1 && s4 == 1 && s8 == 1) || (s1 == 1 && s5 == 1 && s8 == 1) || (s1 == 1 && s4 == 1 && s5 == 1 && s8 == 1)) {

    digitalWrite(led, HIGH);
    delay(4);
  }


  // if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0 && s6 == 0 && s7 == 0 && s8 == 0) {
  //   Stop();
  // }
}

void forward() {
  analogWrite(lpwm, 100);
  analogWrite(rpwm, 100);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  delay(10);
}

void right() {
  analogWrite(lpwm, spd);
  analogWrite(rpwm, spd);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  delay(10);
}

void left() {
  analogWrite(lpwm, spd);
  analogWrite(rpwm, spd);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  delay(10);
}

void Stop() {
  analogWrite(lpwm, 0); // Stop left motor
  analogWrite(rpwm, 0); // Stop right motor
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, LOW);
  digitalWrite(led, HIGH);
}
