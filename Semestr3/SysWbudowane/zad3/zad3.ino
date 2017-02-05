#include <math.h>
#define SIZE 10

int rLed = 9;
int gLed = 10;
int bLed = 11;

float eps = 0.01;

struct RGB
{
  byte r, g, b;
};


RGB rgb = {random(255),random(255),random(255)};

int ledPin = 3;

void setup()
{
  Serial.begin(9600);
	pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);

  randomSeed(analogRead(A0));
}



void loop()
{
	float val = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  if(val < eps)
    rgb = {random(255), random(255), random(255)};
  Serial.println(val);
	analogWrite(rLed, (val/255.0) * rgb.r);
  analogWrite(gLed, (val/255.0) * rgb.g);
  analogWrite(bLed, (val/255.0) * rgb.b);
}  

