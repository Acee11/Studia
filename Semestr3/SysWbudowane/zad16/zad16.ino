#include "pitches.h" 
#define BUZZ_PIN 9

typedef struct {
  int note;
  int tempo;
} notesType;

const notesType notes[] = {
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, 
    {NOTE_A4, 1}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_GS4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 2}, {NOTE_GS4, 1}, {NOTE_G4, 1}, 
    {NOTE_G4, 1}, {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_GS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_FS4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_G4, 1}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_E5, 12}, 
    {NOTE_A5, 2}, {NOTE_AS5, 1}, {NOTE_A5, 1}, {NOTE_E5, 12}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_E5, 2}, {NOTE_A5, 2}, {NOTE_G5, 16}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_E5, 12}, 
    {NOTE_A5, 2}, {NOTE_AS5, 1}, {NOTE_A5, 1}, {NOTE_E5, 12}, 
    {NOTE_A4, 2}, {NOTE_AS4, 1}, {NOTE_A4, 1}, {NOTE_E5, 2}, {NOTE_A5, 2}, {NOTE_AS5, 20}, {NOTE_G5, 2}, {NOTE_A5, 4}
};

int noteSize = sizeof(notes) / sizeof(notesType);

byte leds[] = {2, 3, 4, 5, 6, 7};
int ledSize = sizeof(leds) / sizeof(byte);
int currLed = leds[0];
int inc = -1;

void nextLed()
{
  if(currLed == ledSize-1 || currLed == 0)
    inc = -inc;
  digitalWrite(leds[currLed], LOW);
  if(currLed - 1 >= 0)
    digitalWrite(leds[currLed - 1], LOW);
  if(currLed + 1 <= ledSize - 1)
    digitalWrite(leds[currLed+1], LOW);
  currLed += inc;
  digitalWrite(leds[currLed], HIGH);
  if(currLed - 1 >= 0)
    digitalWrite(leds[currLed - 1], HIGH);
  if(currLed + 1 <= ledSize - 1)
    digitalWrite(leds[currLed+1], HIGH);
}

void setup()
{
  for(int i = 0; i < ledSize; ++i)
    pinMode(leds[i], OUTPUT);
}

void loop()
{
  for(int i = 0; i < noteSize; ++i)
  {
    tone(BUZZ_PIN, notes[i].note, notes[i].tempo*125);
    for(int j = 0; j < notes[i].tempo; ++j)
    {
        nextLed();
        delay(125);
    }
  }
}



