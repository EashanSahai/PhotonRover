#include "Rover.h"

PhotonRover::Rover::Rover()
{
  rightMotor = PhotonRover::Motor('A');
  leftMotor = PhotonRover::Motor('B');
}

PhotonRover::Rover::Rover(char left, char right)
{
  leftMotor = PhotonRover::Motor(left);
  rightMotor = PhotonRover::Motor(right);
}

void PhotonRover::Rover::setup(float leftMotorMult, float rightMotorMult)
{
  leftMotor.setup(leftMotorMult);
  rightMotor.setup(rightMotorMult);
}

void PhotonRover::Rover::forward(int power)
{
  forward(power, power);
}

void PhotonRover::Rover::reverse(int power)
{
  reverse(power, power);
}

void PhotonRover::Rover::forward(int powerLeft, int powerRight) {
  leftMotor.turn_ccw(powerLeft);
  rightMotor.turn_cw(powerRight);
}

void PhotonRover::Rover::reverse(int powerLeft, int powerRight) {
  leftMotor.turn_cw(powerLeft);
  rightMotor.turn_ccw(powerRight);
}

void PhotonRover::Rover::turn_left(int mode, int power)
{
  if (mode == TURN_MODE_IN_PLACE) {
    leftMotor.turn_cw(power);
  } else {
    leftMotor.stop();
  }
  rightMotor.turn_cw(power);
}

void PhotonRover::Rover::turn_right(int mode, int power)
{
  if (mode == TURN_MODE_IN_PLACE) {
    rightMotor.turn_ccw(power);
  } else {
    rightMotor.stop();
  }
  leftMotor.turn_ccw(power);
}

void PhotonRover::Rover::turn_left(int power)
{
  turn_left(TURN_MODE_IN_PLACE, power);
}

void PhotonRover::Rover::turn_right(int power)
{
  turn_right(TURN_MODE_IN_PLACE, power);
}

void PhotonRover::Rover::stop()
{
  rightMotor.stop();
  leftMotor.stop();
}

void PhotonRover::Rover::standby()
{
  rightMotor.standby();
  leftMotor.standby();
}
