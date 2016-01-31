#ifndef _PHOTON_ROVER_LINE_SENSOR
#define _PHOTON_ROVER_LINE_SENSOR

#include "application.h"
#include "QTRSensors.h"

#define NUM_SENSORS   3     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define LEFT_SENSOR   0
#define MID_SENSOR    1
#define RIGHT_SENSOR  2

namespace PhotonRover {
  class LineSensor {
  public:
    LineSensor();
    void setup(void);
    void calibrate(void);
    unsigned int getPosition(void);
    void readCalibrated(void);
    void print(void);
    unsigned int sensorValues[NUM_SENSORS];

  private:
    QTRSensorsRC *qtrrc;
  };
}
#endif
