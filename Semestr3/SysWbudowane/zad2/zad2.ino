int lightPin = A0; 
int ledPin = 3;
int minButton = 4;
int maxButton = 5;
int brmax = 85;

void setup() 
{
  pinMode(lightPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.println(analogRead(3));
  /*
  if(digitalRead(minButton) == HIGH && brmax > 0)
      --brmax;
  if(digitalRead(maxButton) == HIGH && brmax < 255)
    ++brmax;
    
  Serial.println(analogRead(lightPin));
  Serial.println(brmax);
  float fLight = float(analogRead(lightPin));
  float lightMax = 260;
  if (fLight > lightMax)
    fLight = lightMax;
  fLight = (fLight / lightMax) * float(brmax);
  int light =  brmax - int(fLight);
  Serial.println(light);
  analogWrite(ledPin, light);
  delay(100);
  */
  
}
