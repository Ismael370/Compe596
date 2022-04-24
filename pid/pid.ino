#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#define SAMPLE_SPEED 250 // 250ms between samples

float error = 0;
float previous_error = 0;
float integral = 0;
float derivative = 0;
float deltaT = (SAMPLE_SPEED/1000.0);
float output = 0;

//charles is testing his git access etc :)

float kp = 0.5;
float ki = 0;
float kd = 0;

float spd_d = 10; //Desired speed
float spd_a = 0; //Actual speed
float motor_spd = 0;
float fwd_accel = 0;
float velocity = 0;

LSM9DS1 imu; //9dof sensor

float getSpeed()
{
  if(imu.accelAvailable())
  {
    imu.readAccel();
  }

  fwd_accel = (imu.calcAccel(imu.ay)*9.8);

  velocity += (fwd_accel*deltaT);

  if(velocity < 0)
    velocity = 0;

  return velocity;
}

void setup() {
  Wire.begin();
  imu.begin(); //Use pins A4 & A5 by default
  Serial.begin(9600);
}

void loop() {
  spd_a = getSpeed();
  
  error = spd_d - spd_a;
  integral = integral + (error*deltaT);
  derivative = (error - previous_error)/deltaT;
  previous_error = error;
  output = (kp*error) + (ki*integral) + (kd*derivative);

  Serial.println(output);

  motor_spd += output;
  delay(100);
}
