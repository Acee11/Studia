
#define SPEAKER 9   
#define PHOTOCELL A0
#define FREQ_M 7
#define FREQ_P 6
#define MINMAX_SWITCH 5
#define REC_BUTTON 4
#define REC_LED 3
#define PLAY_LED 2

long val = 0;        
long maxRead = 0;    
long minRead = 1000;  
double f = 0;         
double normf = 0;    
double lgf = 0;      
int ilogf = 0;        
long maxFreq = 748;  
long minFreq = 131;   

unsigned short rec[700];
int recIndex = 0;
unsigned long lastSample;
unsigned long recDelay = 20;
boolean recording = false;


//magic numbers that make the intervals sound pleasing
double gap = 1.148698355;  //ratio of consecutive notes (pentatonic)
                             // it's the 5th root of 2
//double gap = 1.059463094;  //ratio of consecutive notes (chromatic)
                              // its the 12th root of 2

                              
void startPlayback()
{
  digitalWrite(PLAY_LED, HIGH);
  for(int i = 0; i < recIndex; ++i)
  {
    tone(SPEAKER, rec[i]);
    delay(recDelay);
  }
  digitalWrite(PLAY_LED, LOW);
}
                              
void setup()
{
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);   
  pinMode(PHOTOCELL, INPUT);
  pinMode(FREQ_M, INPUT);
  pinMode(FREQ_P, INPUT);
  pinMode(REC_BUTTON, INPUT);
  pinMode(REC_LED, OUTPUT);
  pinMode(PLAY_LED, OUTPUT);


  for (int i = 0; i < 500; ++i) 
  {
    val = analogRead(PHOTOCELL); 
    maxRead = max(maxRead, val);      
    minRead = min(minRead, val);
    delay(10);
  } 
}

void loop()
{
  if(digitalRead(FREQ_M) == HIGH)
  {
    if(digitalRead(MINMAX_SWITCH))
      maxFreq = max(minFreq, maxFreq-1);
    else 
      minFreq = max(0, minFreq-1);
     
    delay(50);
  }
  if(digitalRead(FREQ_P) == HIGH)
  {
    if(digitalRead(MINMAX_SWITCH))
      maxFreq = min(1023, maxFreq + 1);
    else
      minFreq = min(maxFreq, minFreq + 1);
    delay(50);
  }
  val = analogRead(PHOTOCELL);
  
  
  f = map(val, minRead, maxRead, minFreq, maxFreq);
  
  normf = f / (double) minFreq; 
  lgf = log(normf) / log(gap); 
  ilogf = round(lgf);           
  f = minFreq * pow(gap,ilogf);  

  if(recording && millis() - lastSample >= recDelay)
  {
     if(recIndex == 700)
     {
        recording = false;
        digitalWrite(REC_LED, LOW);
     }
        
     else
     {
        rec[recIndex] = f;
        ++recIndex;
        lastSample = millis();
     }
  }
  if(digitalRead(REC_BUTTON) == HIGH)
  {
    if(digitalRead(MINMAX_SWITCH) == LOW)
    {
      if(recording)
      {
        recording = false;
        digitalWrite(REC_LED, LOW);
      }
      else
      {
        recording = true;
        recIndex = 0;
        rec[recIndex] = f;
        ++recIndex;
        lastSample = millis();
        digitalWrite(REC_LED, HIGH);
      }
      
    }
    else
    {
      startPlayback();
    }
    delay(100);
  }
  
  
  tone(SPEAKER, f);
  
}
