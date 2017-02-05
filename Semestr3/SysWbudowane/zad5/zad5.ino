#define SIZE 30

unsigned long arr[SIZE];
int i = 0;
int j = 0;

int ledPin = 3;
int buttonPin = 2;
int sigPrev = LOW;
int sig = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  for(int k = 0; k < SIZE; ++k)
    arr[k] = 0;
}

void loop()
{
  
  if(sig != digitalRead(buttonPin)) // obsluga zmiany stanu przycisku
  {
    arr[i] = millis() + 1000;
    sig = !sig;
    i = (i + 1) % SIZE;
  }
  if(arr[j] <= millis() && arr[j] != 0) // zapalanie/gaszenie diody
  {
    sigPrev = !sigPrev;
    arr[j] = 0;
    digitalWrite(ledPin, sigPrev);
    j = (j + 1) % SIZE;
  }    
  
  Serial.println(digitalRead(buttonPin));
  //Serial.println(j);
  
}

