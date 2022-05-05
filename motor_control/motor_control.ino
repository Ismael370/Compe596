#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define AIN1 A0
#define BIN1 A2
#define AIN2 A1
#define BIN2 A3
#define PWMA 2
#define PWMB 3
#define STBY 7

// these constants are used to allow you to make your motor configuration 


// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

Motor motor1(AIN1, AIN2, PWMA, offsetA, STBY); //Left motor
Motor motor2(BIN1, BIN2, PWMB, offsetB, STBY); //Right motor

void motor_fwd(Motor motor1, Motor motor2, int speed1, int speed2)
{
  motor1.drive(speed1);
  motor2.drive(speed2);
}

void motor_back(Motor motor1, Motor motor2, int speed1, int speed2)
{
  int temp1 = abs(speed1);
  int temp2 = abs(speed2);
  motor1.drive(-temp1);
  motor2.drive(-temp2);
}

void setup() {
}

void loop()
{
//  forward(motor2, motor2, 100);
   motor_fwd(motor2, motor1, 100, 100);
   delay(500);
//   back(motor1, motor2, 100);
   motor_back(motor2, motor1, 100, 100);
   delay(500);
}
