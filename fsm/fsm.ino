#include <avr/interrupt.h>
#include <avr/io.h>

float dist_a = 0.0, //measured distance
      spd_a; //measured speed
int dist_t = 10, //distance threshold
    spd_reg = 10; //regular speed
const int STOP = 0, FORWARD = 1, LEFT = 2, RIGHT = 3; //fsm states

ISR(ADC_vect)
{
  dist_a = ADC;
}

void setup() {
  //Set ADC at channel 0 with a prescale of 2
  ADCSRA |= (1<<ADEN) | (1<<ADIE); //Enable ADC with interrupts

  //Set ADC sampling frequency

  sei(); //enable global interrupts
}

void loop() {
  int state = 0, //current state
      count = 0;
  float spd_d = 10.0; //desired speed

  switch(state)
  {
    case STOP:
      if(dist_a > dist_t)
      {
        spd_d = spd_reg;
        state = FORWARD;
      }
      else if(dist_a <= dist_t)
      {
        state = LEFT;
      }
      break;
      
    case FORWARD:
      if(dist_a <= dist_t)
      {
        spd_d = 0;
        state = STOP;
      }
      break;
      
    case LEFT:
      if(dist_a > dist_t)
      {
        spd_d = 0;
        state = STOP;
      }
      else if(dist_a <= dist_t)
      {
        state = RIGHT;
      }
      break;
      
    case RIGHT:
      if(dist_a > dist_t || count >= 2)
      {
        spd_d = 0;
        count = 0;
        state = STOP;
      }
      else
      {
        count += 1;
      }
      break;

      default:
        state = STOP;
        break;
  }
}
