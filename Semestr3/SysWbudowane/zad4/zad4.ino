#include <TinkerKit.h>

#define EPS 5

TKHallSensor hs(I0);	
                      
int buzzPin = 3;
int ledPin = 4;
int buttonPin = 5;

int val = random(1023);

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int hall = hs.read();
  
  hall = abs(val - hall);
  float duration = 1000.0/1023.0 * float(hall);
  if(hall <= EPS)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
  
  tone(buzzPin, 40000, 100);
  delay(duration);
  Serial.println(hall);
  
  if(digitalRead(buttonPin) == HIGH)
    val = random(1023);
}


