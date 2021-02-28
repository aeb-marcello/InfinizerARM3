#include <QTRSensors.h>

#define Kp 1 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 10 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define Ki 0.1 // Nao deve ser um valor muito grande :)
#define rightMaxSpeed 255 // max speed of the robot
#define leftMaxSpeed 255 // max speed of the robot
#define rightBaseSpeed 250 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 250  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS 8     // number of sensors used
#define TIMEOUT 2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN 2     // emitter is controlled by digital pin 2

#define rightMotor1 5
#define rightMotor2 6
#define rightMotorPWM 10
#define leftMotor1 3
#define leftMotor2 4
#define leftMotorPWM 9
//#define motorPower 8

QTRSensorsRC qtrrc((unsigned char[]) { 14, 15, 16, 17, 18, 19, 11, 12} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19

unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
//  pinMode(motorPower, OUTPUT);
  
  int i;
for (int i = 0; i < 100; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead

  /* comment this part out for automatic calibration 
  if ( i  < 25 || i >= 75 ) // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
     turn_right();  
   else
     turn_left(); */ 
   qtrrc.calibrate();   
   delay(20);
//wait();  
delay(2000); // wait for 2s to position the bot before entering the main loop 
    
    Serial.begin(9600);
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();

    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    
  } 

int lastError = 0;
int I = 0;
int P,D, error, motorSpeed;
void loop()
{
  unsigned int sensors[8];
  int position = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  error = position - 3500;
  P = Kp*error;
  I = I+error;
  I = I*Ki;
  D = Kd * (error - lastError);
  motorSpeed = P+I+D; 
  lastError = error;
  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; //
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; 
  
  //
//  digitalWrite(motorPower, HIGH); // move forward with appropriate speeds
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, rightMotorSpeed);
//  digitalWrite(motorPower, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM, leftMotorSpeed);

}

  
//void wait(){
     //digitalWrite(motorPower, LOW);
