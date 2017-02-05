#include <TinkerKit.h>

#define NO_MOVE 0
#define LEFT 2
#define RIGHT 4
#define TOP 5
#define BOT 3
#define H 1000
#define L 30

int x;
int y;
int r = random(2,6);
int score = 0;
long penalty = 0;
int userMove;
unsigned long t = millis();
int rounds = 15;

TKJoystick j(I1, I0);

void countdown()
{
  for(int i = 5; i >= 0; --i)
  {
    Serial.print(i);
    Serial.println("...");
    j.readX();
    j.readY();
    delay(1000);
  }
}

void setup() 
{
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(BOT, OUTPUT);
  pinMode(TOP, OUTPUT);
}



void loop() 
{
  Serial.println("How many rounds do you want to play?");
  while(!Serial.available()) {delay(100);}
  rounds = Serial.parseInt();
  r = random(2,6);
  score = 0;
  penalty = 0;
  countdown();
  digitalWrite(r,HIGH);
  for(int i = 0; i < rounds;)
  {
    x = j.readX();
    y = j.readY();
    userMove = NO_MOVE;
    if(x <= L)
      userMove = LEFT;
    else if(x >= H) 
      userMove = RIGHT;
    else if(y <= L) 
      userMove = BOT;
    else if(y >= H) 
      userMove = TOP;
    if(userMove != NO_MOVE)
    {
      if(userMove == r)
      {
        t = millis() - t;
        t = constrain(t, 0, 750);
        t = map(t, 0, 750, 50, 0);
        score += t;
        //penalty = 1;
        digitalWrite(r, LOW);
        r = random(2,6);
        
      }
      else
      {
        score -= penalty;
        penalty += 50;
      }
      Serial.print("Score = ");
      Serial.println(score);
      delay(300);
      t = millis();
      digitalWrite(r, HIGH);
      ++i;
    }
  }
  digitalWrite(r, LOW);
  
}



