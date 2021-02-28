#include "Arduino.h"
#include "InfinizerARM3.h"
Ultrasonic::Ultrasonic(int Trigger, int Echo){
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
  _trigger = Trigger;
  _echo = Echo;
}
int Ultrasonic::get_distance(){
  digitalWrite(_trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(_trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger,LOW);
  long dt = pulseIn(_echo,HIGH);
  return dt*0.034*0.5;
}
Robot::Robot(){
  _robot = true;
}
bool Robot::isObstacleInFront(int distance, int sec_distance=20){
  return (distance <= sec_distance) ? true : false;
}
