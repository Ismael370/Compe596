#include <avr/interrupt.h>
#include <avr/io.h>

#include <SparkFun_TB6612.h>

#define TRIG_ON PORTB |= (1<<PINB1);
#define TRIG_OFF PORTB &= ~(1<<PINB1);
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define AIN1 A0
#define BIN1 A2
#define AIN2 A1
#define BIN2 A3
#define PWMA 2
#define PWMB 3
#define STBY 22

// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

const int STOP = 0, FORWARD = 1, LEFT = 2, RIGHT = 3; //fsm states

int state = STOP; //Current state
int count = 0; //Counter for RIGHT state
int echoPin = 8;

float spd_m; //measured speed
float spd_reg = 10.0; //regular speed
float spd_dl = 10.0; //desired speed for left motor
float spd_dr = 10.0; //desired speed for right motor

long dist_m = 0; //measured distance
long dist_t = 10; //distance threshold

Motor motor1(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2(BIN1, BIN2, PWMB, offsetB, STBY);

long getDistance()
{
  long distance = 0;
  long duration = 0;

  TRIG_ON
  delayMicroseconds(10);
  TRIG_OFF

  duration = pulseIn(echoPin, HIGH, 150000L);
  distance = duration/58; //Convert duration to cm
  return distance; 
}

void setup() {
  DDRB &= ~(1<<DDB0); //Set pin B0 as input for echo 
  DDRB |= (1<<DDB1); //Set pin B1 as output for trigger
  TRIG_OFF //Set to low to initialize the sensor
  Serial.begin(9600);
}

void loop() {
  dist_m = getDistance();

  switch(state)
  {
    case STOP:
      brake(motor1, motor2);
      if(dist_m > dist_t)
      {
        spd_dl = spd_reg;
        spd_dr = spd_reg;
        state = FORWARD;
      }
      else if(dist_m <= dist_t)
      {
        state = LEFT;
      }
      Serial.println("STOP");
      delay(500);
      break;
      
    case FORWARD:
      forward(motor1, motor2, 150);
      if(dist_m <= dist_t)
      {
        spd_dl = 0;
        spd_dr = 0;
        state = STOP;
      }
      Serial.println("FORWARD");
      delay(500);
      break;
      
    case LEFT:
      left(motor1, motor2, 100);
      if((dist_m > dist_t && count == 0) || (count >= 2))
      {
        spd_dl = 0;
        spd_dr = 0;
        state = STOP;
      }
      else
      {
        count += 1;
      }

      Serial.println("LEFT");
      delay(500);
      break;

      default:
        spd_dl = 0;
        spd_dr = 0;
        state = STOP;
        brake(motor1, motor2);
        break;
  }
}
