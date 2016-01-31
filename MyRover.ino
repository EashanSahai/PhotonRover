#include "Rover.h"
#include "LineSensor.h"

#define NOMINAL_POWER 60
#define KP  0.05
#define DESIRED_POS   1000
#define DARK_THRESHOLD  900

PhotonRover::Rover rover;
PhotonRover::LineSensor sensor;

void setup()
{
  rover = PhotonRover::Rover();
  rover.setup(1.3, 1.0);
  sensor = PhotonRover::LineSensor();
  sensor.setup();
  calibrate();
}

void calibrate()
{
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);    // turn on LED to indicate we are in calibration mode
  Serial.print("Calibrating ...");
  rover.turn_left(MIN_POWER);
  for (int i = 0; i < 100; i++) {
    sensor.calibrate();
  }
  rover.turn_right(MIN_POWER);
  for (int i = 0; i < 200; i++) {
    sensor.calibrate();
  }
  rover.turn_left(MIN_POWER);
  for (int i = 0; i < 100; i++) {
    sensor.calibrate();
  }
  Serial.println(" Done.");
  digitalWrite(D7, LOW);    // turn off LED to indicate we are done with calibration
}

void lineFollow(unsigned int pos)
{
  int error;
  error = (pos - DESIRED_POS);
  int pLeft = clamp(NOMINAL_POWER + error * KP);
  int pRight = clamp(NOMINAL_POWER - error * KP);
  rover.forward(pLeft, pRight);
  sensor.print();
  Serial.println(" POS: " + String(pos) + " ERR: " + String(error) +  " LEFT: " + String(pLeft) + " RIGHT: " + String(pRight));
}

int clamp(int power)
{
  if (power < MIN_POWER)
    return MIN_POWER;
  else if (power > MAX_POWER)
    return MAX_POWER;
  else
    return power;
}

void turn_right()
{
  int count = 0;
  do {
    count++;
    rover.turn_right(TURN_MODE_IN_PLACE, MIN_POWER);
    sensor.readCalibrated();
  }  while(sensor.sensorValues[MID_SENSOR] < DARK_THRESHOLD && count < 300);
  rover.forward(MIN_POWER);
  delay(100);
}


void turn_left()
{
  int count = 0;
  do {
    count++;
    rover.turn_left(TURN_MODE_IN_PLACE, MIN_POWER);
    sensor.readCalibrated();
  }  while(sensor.sensorValues[MID_SENSOR] < DARK_THRESHOLD && count < 300);
  rover.forward(MIN_POWER);
  delay(100);
}

void loop()
{
  static int sawLeftCount = 0;
  static int sawRightCount = 0;
  unsigned int pos = sensor.getPosition();
  if (sensor.sensorValues[MID_SENSOR] > DARK_THRESHOLD &&
    sensor.sensorValues[RIGHT_SENSOR] > DARK_THRESHOLD) {
    sawRightCount++;
    sawLeftCount = 0;
    if (sawRightCount > 10) {
      sawRightCount = 0;
      delay(100);
      turn_right();
    }
    pos = sensor.getPosition();
  }
  lineFollow(pos);
  if (sensor.sensorValues[MID_SENSOR] > DARK_THRESHOLD &&
    sensor.sensorValues[LEFT_SENSOR] > DARK_THRESHOLD) {
      sawLeftCount++;
      sawRightCount = 0;
      if (sawLeftCount > 10) {
        sawLeftCount = 0;
        delay(100);
        turn_left();
      }
    pos = sensor.getPosition();
  }
}



void loopRover(int duration)
{
  rover.forward(MAX_POWER);
  delay(duration);
  rover.reverse(MAX_POWER);
  delay(duration);
  rover.turn_left(MAX_POWER);
  delay(duration);
  rover.turn_right(MAX_POWER);
  delay(duration);
  rover.turn_left(TURN_MODE_PIVOT, MAX_POWER/2);
  delay(duration);
  rover.turn_right(TURN_MODE_PIVOT, MAX_POWER/2);
  delay(duration);
  rover.stop();
  delay(duration);
}

void loopSensor()
{
  unsigned int pos = sensor.getPosition();
  sensor.print();
  Serial.println(pos);
}
