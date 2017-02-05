byte ledPin = 3;
byte buzzPin = 4;
byte buttonPin = 5;
int current, prev = LOW;

#define DOT_DURATION  115
#define EPS 10

String morse = "_etianmsurwdkgohvf_l_pjbxcy2q__54_3___2_______16_______7___8_90";
String currentLetter = "";
unsigned long lastSignalChange = millis();
unsigned long signalTime;

//ala ma kota  =>  .-  .-..  .-     --  .-     -.-  ---  -  .-
// arduino => .-  .-.  -..  ..-  ..  -.  --- 

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(buzzPin,OUTPUT);
  pinMode(buttonPin,INPUT);
}

void loop() 
{
  current = digitalRead(buttonPin);
  if(current == HIGH)
  {
    tone(buzzPin, 10000);
    digitalWrite(ledPin, HIGH);    
  }
  else
  {
    noTone(buzzPin);
    digitalWrite(ledPin, LOW); 
  }

  signalTime = millis() - lastSignalChange;

  if(currentLetter != "" && current == LOW && signalTime >= 7*DOT_DURATION)
  {
    Serial.write(morseToChar(currentLetter));
    currentLetter = "";
    Serial.write(' ');
  }

  if(current != prev && signalTime > EPS) //button state changed
  {
    lastSignalChange = millis();
    if(prev == HIGH)
    {
      if(signalTime <= 2*DOT_DURATION)
        currentLetter += ".";
      else
        currentLetter += "-"; 
    }
    else if(signalTime > 2*DOT_DURATION + 50 && signalTime < 7*DOT_DURATION)
    {
      Serial.write(morseToChar(currentLetter));
      currentLetter = "";
    }
  }

  prev = current;
}

char morseToChar(String str)
{
  int index = 0;
  for(int i = 0; i < str.length(); ++i)
  {
    index = str[i] == '.' ? (index*2 + 1) : (index*2 + 2);
  }
  if(index > morse.length())
    return '?';
  return morse[index];
}

