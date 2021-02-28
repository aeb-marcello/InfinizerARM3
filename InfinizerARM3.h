#ifndef InfinizerARM3_h
#define InfinizerARM3_h
#include "Arduino.h"

class Ultrasonic {
  public:
    Ultrasonic(int Trigger, int Echo);
    int get_distance();
  private:
    int _trigger;
    int _echo;
};
class Robot {
  public:
    Robot();
    bool isObstacleInFront(int distance, int sec_distance=20);
  private:
    bool _robot;
};
#endif
