#define TRIG_ON PORTB |= (1<<PINB0);
#define TRIG_OFF PORTB &= ~(1<<PINB0);

int trigPin = 8;
int echoPin = 9;

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
  DDRB &= ~(1<<DDB1); //Set pin B0 as input for echo 
  DDRB |= (1<<DDB0); //Set pin B1 as output for trigger
  TRIG_OFF
  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();
  Serial.println(distance);
}
