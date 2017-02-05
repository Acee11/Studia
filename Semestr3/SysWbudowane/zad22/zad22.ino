#define CLED 4
#define BUZZ 5
#include "pitches.h"

unsigned long time;
unsigned long h = 1000;
byte led[3] = {2, 6, 8};
byte button[3] = {3, 7, 9};
bool buttonRead[3];
int score[3] = {0, 0, 0};

bool penalty = false, winner = false;

typedef struct 
{
	int note;
	int tempo;
} note;


const note notes[] = {{NOTE_E5, 125}, {NOTE_G5, 125}, {NOTE_E6, 125}, {NOTE_C5, 125},
{NOTE_D5, 125}, {NOTE_G6, 125}};

void playWinnerMusic(int pin)
{
	int sig = HIGH;
	for(int i = 0; i < 6; ++i)
	{
		tone(BUZZ, notes[i].note);
		delay(notes[i].tempo);
		digitalWrite(led[pin], sig);
		sig = !sig;
	}
	noTone(BUZZ);
	digitalWrite(led[pin], LOW);
}

void setup()
{
	for(int i = 0; i < 3; ++i)
	{
		pinMode(led[i], OUTPUT);
		pinMode(button[i], INPUT);
	}

	pinMode(BUZZ, OUTPUT);
	pinMode(CLED, OUTPUT);

	randomSeed(analogRead(A0));

	Serial.begin(9600);
}

void loop()
{
	time = millis() + random(1000, 3000);
	while(millis() < time)
	{
		for(int i = 0; i < 3; ++i)
		{
			if(digitalRead(button[i]))
			{
				penalty = true;
				score[i] -= 50;
				digitalWrite(led[i], HIGH);
				tone(BUZZ, 90, 2000);
				delay(2000);
				digitalWrite(led[i], LOW);
				break;
			}
		}
		if(penalty)
			break;
	}
	if(!penalty)
	{
		tone(BUZZ, 500);
		digitalWrite(CLED, HIGH);
		time = millis();
		while(true)
		{
			if(millis() >= time + 500)
			{
				noTone(BUZZ);
				digitalWrite(CLED, LOW);
			}
			for(int i = 0; i < 3; ++i)
			{
				if(digitalRead(button[i]))
				{
					noTone(BUZZ);
					digitalWrite(CLED, LOW);
					winner = true;
					score[i] += max(map(millis(), time, time + h, 100, 0), 0);
					playWinnerMusic(i);
					break;
				}
			}
			if(winner)
				break;
			
		}
	}
	penalty = false;
	winner = false;

	Serial.print("Player 1: ");
	Serial.println(score[0]);
	Serial.print("Player 2: ");
	Serial.println(score[1]);
	Serial.print("Player 3: ");
	Serial.println(score[2]);
	Serial.print("---------------\n");
}