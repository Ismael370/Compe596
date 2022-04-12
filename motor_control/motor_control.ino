
#include <LSM9DS1_Registers.h>
#include <LSM9DS1_Types.h>
#include <SparkFunLSM9DS1.h>

#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define AIN1 A0
#define BIN1 A2
#define AIN2 A1
#define BIN2 A3
#define PWMA 2
#define PWMB 3
#define STBY 22

// these constants are used to allow you to make your motor configuration 


// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

Motor motor1(AIN1, AIN2, PWMA, offsetA, STBY);

Motor motor2(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
}

void loop()
{

   //Use of the forward function, which takes as arguements two motors
   //and optionally a speed.  If a negative number is used for speed
   //it will go backwards
   forward(motor1, motor2, 150);
   delay(1000);

   //Use of the back function, which takes as arguments two motors 
   //and optionally a speed.  Either a positive number or a negative
   //number for speed will cause it to go backwards
   back(motor1, motor2, -150);
   delay(1000);

   //Use of the brake function which takes as arguments two motors.
   //Note that functions do not stop motors on their own.
   brake(motor1, motor2);
   delay(1000);

   //Use of the left and right functions which take as arguements two
   //motors and a speed.  This function turns both motors to move in 
   //the appropriate direction.  For turning a single motor use drive.
   left(motor1, motor2, 100);
   delay(1000);
   right(motor1, motor2, 100);
   delay(1000);

   //Use of brake again.
   brake(motor1, motor2);
   delay(1000);
}
