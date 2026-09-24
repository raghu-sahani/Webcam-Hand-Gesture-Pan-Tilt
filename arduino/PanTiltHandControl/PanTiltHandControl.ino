#include <Servo.h>

Servo panServo;
Servo tiltServo;

float currentPan  = 90.0;
float currentTilt = 90.0;

float targetPan  = 90.0;
float targetTilt = 90.0;

char inputBuffer[30];
byte bufferIndex = 0;

unsigned long lastServoUpdate = 0;

const unsigned long SERVO_INTERVAL = 10;
const float SMOOTH_FACTOR = 0.09;
const float DEAD_BAND = 0.20;

const int MIN_US = 600;
const int MAX_US = 2400;

void setup() {
  Serial.begin(115200);

  panServo.attach(3, MIN_US, MAX_US);
  tiltServo.attach(5, MIN_US, MAX_US);

  writeServo(panServo, 90);
  writeServo(tiltServo, 90);

  delay(1000);
  Serial.println("READY");
}

void loop() {
  readSerial();

  if (millis() - lastServoUpdate >= SERVO_INTERVAL) {
    lastServoUpdate = millis();
    updateServos();
  }
}

void readSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      inputBuffer[bufferIndex] = '\0';
      parseData();
      bufferIndex = 0;
    }
    else if (c != '\r') {
      if (bufferIndex < sizeof(inputBuffer) - 1) {
        inputBuffer[bufferIndex++] = c;
      }
    }
  }
}

void parseData() {
  char *comma = strchr(inputBuffer, ',');

  if (comma == NULL) {
    return;
  }

  *comma = '\0';

  int pan = atoi(inputBuffer);
  int tilt = atoi(comma + 1);

  targetPan = constrain(pan, 0, 180);
  targetTilt = constrain(tilt, 0, 180);
}

void updateServos() {
  float panDifference = targetPan - currentPan;
  float tiltDifference = targetTilt - currentTilt;

  if (abs(panDifference) > DEAD_BAND) {
    currentPan += panDifference * SMOOTH_FACTOR;
    writeServo(panServo, currentPan);
  }

  if (abs(tiltDifference) > DEAD_BAND) {
    currentTilt += tiltDifference * SMOOTH_FACTOR;
    writeServo(tiltServo, currentTilt);
  }
}

void writeServo(Servo &servo, float angle) {
  angle = constrain(angle, 0, 180);

  int pulse =
    MIN_US +
    (angle / 180.0) *
    (MAX_US - MIN_US);

  servo.writeMicroseconds(pulse);
}
