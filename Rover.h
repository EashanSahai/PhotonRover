#ifndef _PHOTON_ROVER_ROVER
#define _PHOTON_ROVER_ROVER

#include "Motor.h"

#define TURN_MODE_IN_PLACE  0
#define TURN_MODE_PIVOT     1
#define MIN_POWER           40
#define MAX_POWER           80

namespace PhotonRover {
  class Rover {
  public:
    Rover();
    Rover(char left, char right);        // left or right Motor => 'A' or 'B'
    void setup(float leftMotorMult, float rightMotorMult);
    void forward(int power);  // Power should be a value between 0 - 255
    void reverse(int power);
    void forward(int powerLeft, int powerRight);  // Power should be a value between 0 - 255
    void reverse(int powerLeft, int powerRight);
    void turn_left(int mode, int power);
    void turn_right(int mode, int power);
    void turn_left(int power);    // Same as above with mode => TURN_MODE_IN_PLACE
    void turn_right(int power);
    void stop();              // Stop the Rover
    void standby();           // Wait for button press

  private:
    Motor   leftMotor;
    Motor   rightMotor;
  };
}
#endif
