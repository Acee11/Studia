byte ledPin = 3;
byte buzzPin = 4;

#define DOT_DURATION 110
String str;

const char* letters[] = {
  ".-", //a
  "-...", //b
  "-.-.", //c 
  "-..", //d
  ".", //e
  "..-.", //f
  "--.", //g
  "....", //h
  "..", //i
  ".---", //j
  "-.-", //k
  ".-..", //l
  "--", //m
  "-.", //n
  "---", //o
  ".--.", //p
  "--.-", //q
  ".-.", //r
  "...", //s
  "-", //t
  "..-", //u
  "...-", //v
  ".--", //w
  "-..-", //x
  "-.--", //y
  "--.." //z
};

const char* numbers[] = {
  "-----", //0
  ".----", //1
  "..---", //2
  "...--", //3
  "....-", //4
  ".....", //5
  "-....", //6
  "--...", //7
  "---..", //8
  "----.", //9
};

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.println('a' - 'A' - 1);
  if(Serial.available())
  {
    str = Serial.readStringUntil('\n');
    Serial.println(str); 
    Serial.println(str.length());
    for(int i = 0; i < str.length(); ++i)
    {
      if(isWhitespace(str[i]))
      {
        while(isWhitespace(str[i+1]) && i < sizeof(str))
          ++i;
        delay(7 * DOT_DURATION);
      }
      else if(isAlpha(str[i]))
      {
        if(str[i] <= 'Z')
          str[i] += 'a' - 'A';
        morse(letters[str[i] - 'a']);
        delay(3 * DOT_DURATION);
      }
      else if(str[i] >= '0' && str[i] <=  '9')
      {
        morse(numbers[str[i] - '0']);
        delay(3*DOT_DURATION);
      }
    }
  }
}

void morse(String s)
{
  for(int i = 0; i < s.length(); ++i)
  {
    digitalWrite(ledPin, HIGH);
    tone(buzzPin, 10000);
    delay(s[i] == '.' ? DOT_DURATION : (3*DOT_DURATION));
    noTone(buzzPin);
    digitalWrite(ledPin, LOW);
    if(i < sizeof(s) - 1)
      delay(DOT_DURATION);
  }
}





