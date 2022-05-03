#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

#define SIZE 20
#define SAMPLE_SPEED 250 // 250ms between samples
//void enqueue();
//void dequeue();
//int inp_arr[SIZE];
//int Rear = - 1;
//int Front = - 1;


//Moving Average
int index = 0;
float value = 0;
float average = 0;
float sum = 0;
float arr[SIZE];

//9DOF SENSOR
LSM9DS1 imu; //9dof sensor
float fwd_accel = 0; //in m/s^2
float velocity = 0; //in m/s
float deltaT = (SAMPLE_SPEED/1000.0);
  
//void enqueue(float a)
//{
//    if (Rear == SIZE - 1)
//       printf("Overflow \n");
//    else
//    {
//        if (Front == - 1)
//          Front = 0;
//          
//        Rear = (Rear + 1)%SIZE;
//        inp_arr[Rear] = a;
//    }
//} 
  
//float dequeue()
//{
//    float b
//    if (Front == - 1 || Front > Rear)
//    {
//        printf("Underflow \n");
//        return 0;
//    }
//    else
//    {
//        printf("Element deleted from the Queue: %d\n", inp_arr[Front]);
//        b = inp_arr[Front];
//        Front = (Front + 1)%SIZE;
//        return b;
//    }
//} 

//float myFilter(float a){
//  enqueue(a)
//  if count < SIZE
//    return 0;
//  else
//  {
//    b = dequeue()
//    Average(inp_arr)
//    if (b+threshold > average or b -threshold < average)
//      b = average
//    if(b < 0 )
//      b = 0
//    return b;
//  }
//}

void movingAvgFilter()
{
  sum -= arr[index];
  arr[index]= value;
  sum += value;
  index = (index+1)%SIZE;
  average = sum/20.0;
}

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
  value = getSpeed();
  movingAvgFilter();
  Serial.print(value);
  Serial.print(",");
  Serial.println(average);
}
