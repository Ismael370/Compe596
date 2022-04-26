
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

Motor motor1(AIN1, AIN2, PWMA, offsetA, STBY);

Motor motor2(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
}

void loop()
{
   forward(motor1, motor2, 150);
   delay(1000);
   back(motor1, motor2, -150);
   delay(1000);
   left(motor1, motor2, 100);
   delay(1000);
   right(motor1, motor2, 100);
   delay(1000);
}
