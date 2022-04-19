float error = 0;
float previous_error = 0;
float integral = 0;
float derivative = 0;
float delta = 1/100;
float output = 0;

//charles is testing his git access etc :)

float kp = 0.5;
float ki = 0;
float kd = 0;

float spd_d = 10; //Desired speed
float spd_a = 0; //Actual speed
float motor_spd = 0;

void setup() {
}

void loop() {
  error = spd_d - spd_a;
  integral = integral + (error*delta);
  derivative = (error - previous_error)/delta;
  previous_error = error;
  output = (kp*error) + (ki*integral) + (kd*derivative);

  motor_spd += output;
}
