#include "Motor.h"

PhotonRover::Motor::Motor()
{
  pin_stdby = PIN_STDBY;
  pin_in1 = PIN_AIN1;
  pin_in2 = PIN_AIN2;
  pin_pwm = PIN_PWMA;
}

PhotonRover::Motor::Motor(char which)
{
  pin_stdby = PIN_STDBY;
  if (which == 'A') {
    pin_in1 = PIN_AIN1;
    pin_in2 = PIN_AIN2;
    pin_pwm = PIN_PWMA;
  } else if (which == 'B') {
    pin_in1 = PIN_BIN1;
    pin_in2 = PIN_BIN2;
    pin_pwm = PIN_PWMB;
  }
}

PhotonRover::Motor::Motor(int in1, int in2, int pwm, int stdby)
{
  pin_in1 = in1;
  pin_in2 = in2;
  pin_pwm = pwm;
  pin_stdby = stdby;
}

void PhotonRover::Motor::setup(float mult)
{
  powerMult = mult;
  pinMode(pin_in1, OUTPUT);
  pinMode(pin_in2, OUTPUT);
  pinMode(pin_pwm, OUTPUT);
  pinMode(pin_stdby, OUTPUT);
  stop();
  standby();
}

void PhotonRover::Motor::turn_cw(int power)
{
  power = (int)(powerMult * power);
  digitalWrite(pin_stdby, HIGH);
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  analogWrite(pin_pwm, power);
}

void PhotonRover::Motor::turn_ccw(int power)
{
  power = (int)(powerMult * power);
  digitalWrite(pin_stdby, HIGH);
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  analogWrite(pin_pwm, power);
}
void PhotonRover::Motor::stop()
{
  digitalWrite(pin_stdby, HIGH);
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_pwm, HIGH);
}

void PhotonRover::Motor::standby()
{
  digitalWrite(pin_stdby, LOW);
}
