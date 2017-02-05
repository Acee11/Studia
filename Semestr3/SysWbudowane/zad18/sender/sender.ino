#define LED_PIN 7
#define DOT_DURATION 110
String str = "sos";

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

void morse(String s)
{
  for(int i = 0; i < s.length(); ++i)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(s[i] == '.' ? DOT_DURATION : (3*DOT_DURATION));
    digitalWrite(LED_PIN, LOW);
    if(i < sizeof(s) - 1)
      delay(DOT_DURATION);
  }
}

void setup() 
{
	pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
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

    delay(100000);
}
