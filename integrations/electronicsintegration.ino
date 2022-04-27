#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

//VARIABLES FOR 9DOF
#define SAMPLE_SPEED 250 // 250ms between samples
LSM9DS1 imu; //9dof sensor
double fwd_accel = 0; //in m/s^2
double velocity = 0; //in m/s

//MOTOR CONTROLLER VARIABLES
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

//HCSO4 VARIABLES
#define TRIG_ON PORTB |= (1<<PINB1);
#define TRIG_OFF PORTB &= ~(1<<PINB1);
int trigPin = 9;
int echoPin = 8;

long getDistance()
{
  long dist_m = 0;
  long duration = 0;

  TRIG_ON
  delayMicroseconds(10);
  TRIG_OFF

  duration = pulseIn(echoPin, HIGH, 150000L);
  dist_m = duration/58;
  return dist_m; 
}

void setup() {
  //SET UP FOR HCSO4
  DDRB &= ~(1<<DDB0); //Set pin B0 as input for echo 
  DDRB |= (1<<DDB1); //Set pin B1 as output for trigger
  TRIG_OFF
  Serial.begin(9600);
  Wire.begin();
  imu.begin(); //Use pins A4 & A5 by default
  Serial.begin(9600);
}

void loop()
{
	//GET THE DISTANCE SENSOR FEED
	long distance = getDistance();
	Serial.println(distance);
	
	//GET THE 
   if(imu.accelAvailable())
  {
    imu.readAccel();
  }

  fwd_accel = (imu.calcAccel(imu.ay)*9.8);
  
  Serial.print("A: ");
  Serial.print(fwd_accel);

  velocity += (fwd_accel*(SAMPLE_SPEED/1000.0));

  if(velocity < 0)
    velocity = 0;
  Serial.print("\tV:");
  Serial.println(velocity);

  delay(SAMPLE_SPEED);

  //TELL MOTORS TO SPIN FORWARD AND BACKWARDS
  if(distance < 5){
	back(motor1, motor2, -150);}
  else{
	forward(motor1, motor2, 150);
  }

}