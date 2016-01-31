#include "application.h"
#include "LineSensor.h"

PhotonRover::LineSensor::LineSensor()
{
  static unsigned char sensorPins[NUM_SENSORS] = { A0, A1, A2 };
  qtrrc = new QTRSensorsRC(sensorPins, NUM_SENSORS, TIMEOUT, QTR_NO_EMITTER_PIN);
}

void PhotonRover::LineSensor::setup(void)
{
}

void PhotonRover::LineSensor::calibrate(void)
{
  qtrrc->calibrate();
}

unsigned int PhotonRover::LineSensor::getPosition(void)
{
  return qtrrc->readLine(sensorValues);
  //qtrrc->read(sensorValues);
  //return 0;
}

void PhotonRover::LineSensor::readCalibrated(void)
{
  qtrrc->readCalibrated(sensorValues);
}

void PhotonRover::LineSensor::print(void)
{
    Serial.print("LEFT: " + String(sensorValues[LEFT_SENSOR]));
    Serial.print("  MID: " + String(sensorValues[MID_SENSOR]));
    Serial.print("  RIGHT: " + String(sensorValues[RIGHT_SENSOR]));
}
