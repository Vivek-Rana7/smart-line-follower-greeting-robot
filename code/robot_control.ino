#include <Servo.h>

/* ------------ ULTRASONIC ------------ */
const int trigPin = 9;
const int echoPin = 10;

/* ------------ VOICE MODULE ------------ */
const int isdPin = 8;

/* ------------ SERVO ------------ */
const int servoPin = 6;
Servo head;

/* ------------ RGB LED ------------ */
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

/* ------------ MOTOR DRIVER (L298N) ------------ */
const int ENA = 11;
const int IN1 = 12;
const int IN2 = 13;
const int ENB = 2;
const int IN3 = 4;
const int IN4 = 7;

/* ------------ LINE SENSORS ------------ */
const int leftSensor = A0;
const int rightSensor = A1;

/* ------------ VARIABLES ------------ */
char mode = 'M';                  // M = Manual, A = Automatic
const int ALERT_RANGE = 30;       // cm

/* ------------ BASIC FUNCTIONS ------------ */
void setColor(bool r, bool g, bool b) {
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 100;
  return duration * 0.034 / 2;
}

/* ------------ MOTOR CONTROL ------------ */
void stopRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void uTurn() {
  right();
  delay(900);
  stopRobot();
}

/* ------------ HUMAN DETECTION ACTION ------------ */
void humanReaction() {
  stopRobot();
  setColor(1, 0, 0);     // Red alert

  // Play recorded voice
  digitalWrite(isdPin, HIGH);
  delay(1200);
  digitalWrite(isdPin, LOW);

  // Head movement
  for (int pos = 60; pos <= 120; pos++) {
    head.write(pos);
    delay(12);
  }
  for (int pos = 120; pos >= 60; pos--) {
    head.write(pos);
    delay(12);
  }

  setColor(0, 0, 1);     // Back to normal
}

/* ------------ SETUP ------------ */
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(isdPin, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);

  head.attach(servoPin);
  head.write(90);

  Serial.begin(9600);   // Bluetooth UART
}

/* ------------ LOOP ------------ */
void loop() {
  int distance = getDistance();

  /* ---- Human detection (both modes) ---- */
  if (distance > 0 && distance <= ALERT_RANGE) {
    humanReaction();
    delay(1500);
    return;
  }

  /* ---- Bluetooth commands ---- */
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'M' || cmd == 'A') {
      mode = cmd;
      stopRobot();
    }

    if (mode == 'M') {
      setColor(0, 1, 0);   // Green = Manual
      switch (cmd) {
        case 'F': forward(); break;
        case 'B': backward(); break;
        case 'L': left(); break;
        case 'R': right(); break;
        case 'U': uTurn(); break;
        case 'S': stopRobot(); break;
      }
    }
  }

  /* ---- Automatic Line Following ---- */
  if (mode == 'A') {
    setColor(0, 0, 1);    // Blue = Auto

    int leftVal = digitalRead(leftSensor);
    int rightVal = digitalRead(rightSensor);

    if (leftVal == LOW && rightVal == LOW) forward();
    else if (leftVal == LOW) left();
    else if (rightVal == LOW) right();
    else stopRobot();
  }

  delay(50);
}

