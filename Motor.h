#ifndef _PHOTON_ROVER_MOTOR
#define _PHOTON_ROVER_MOTOR

#include "application.h"

#define PIN_PWMA  A4
#define PIN_AIN1  D3
#define PIN_AIN2  D2

#define PIN_PWMB  A5
#define PIN_BIN1  D5
#define PIN_BIN2  D6

#define PIN_STDBY D4

namespace PhotonRover {
  class Motor {
  public:
    Motor();
    Motor(char which);        // which parameter refers to Motor 'A' or 'B'
    Motor(int in1, int in2, int pwm, int stdby);  // Pins connected to various controls
    void setup(float powerMult);
    void turn_cw(int power);  // Power should be a value between 0 - 255
    void turn_ccw(int power); // Power should be a value between 0 - 255
    void stop();              // Stop the motor
    void standby();           // Cut-off power to the motor

  private:
    int   pin_in1;
    int   pin_in2;
    int   pin_pwm;
    int   pin_stdby;
    float powerMult;
  };
}
#endif
