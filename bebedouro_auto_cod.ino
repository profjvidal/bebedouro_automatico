#include <Servo.h>
Servo servoMain; 
#define trigPin  10
#define echoPin 11

void setup() {
  servoMain.attach(9); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

  long duracao, cm;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);

  cm = microssegundosParaCentemetro(duracao);
  

  if(cm < 10)
  {
   servoMain.write(120); 
  }
  else{
   servoMain.write(0);
   }
  delay(500);
}

long microssegundosParaCentemetro(long microssegundos)
{
  return microssegundos / 29 / 2;
}
