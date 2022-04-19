#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

#define SAMPLE_SPEED 250 // 250 ms between samples

LSM9DS1 imu; //9dof sensor

float velocity = 0;

void setup() {
  Wire.begin();
  imu.begin();

  Serial.begin(9600);
}

void loop() {
  if(imu.accelAvailable())
  {
    imu.readAccel();
  }

//  Serial.print("x: ");
//  Serial.print(imu.calcAccel(imu.ax));
//
  Serial.print(" y: ");
  Serial.println(imu.calcAccel(imu.ay)/9.8);
//  
//  Serial.print(" z: ");
//  Serial.println(imu.calcAccel(imu.az));

//  velocity = velocity + (imu.calcAccel(imu.ay)*(SAMPLE_SPEED/1000));
//  Serial.println(velocity);

  delay(SAMPLE_SPEED);
}
