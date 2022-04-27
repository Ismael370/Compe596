#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

#define SAMPLE_SPEED 250 // 250ms between samples

LSM9DS1 imu; //9dof sensor
double fwd_accel = 0; //in m/s^2
double velocity = 0; //in m/s

void setup() {
  Wire.begin();
  imu.begin(); //Use pins A4 & A5 by default
  Serial.begin(9600);
}

void loop() {
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
}
