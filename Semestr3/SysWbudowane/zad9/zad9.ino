
#define LED0 2
#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define DTIME 4
#define LETTER_DELAY 12

//b   
//0  # #
//1  #   #
//2  # #
//3  #   #
//4  # # 
//
//   0 1 2 t
//
const byte t[][3] = {
  {0b11111, 
   0b10100, 
   0b11111}, //A
  {0b11111, 0b10101, 0b01010}, //B
  {0b11111, 0b10001, 0b11011}, //C
  {0b11111, 0b10001, 0b01110}, //D
  {0b11111, 0b10101, 0b10101}, //E
  {0b11111, 0b10100, 0b10100}, //F
  {0b11111, 0b10101, 0b10111}, //G
  {0b11111, 0b00100, 0b11111}, //H
  {0b00000, 0b11111, 0b00000}, //I
  {0b00011, 0b00001, 0b11111}, //J
  {0b11111, 0b01010, 0b10001}, //K
  {0b11111, 0b00001, 0b00001}, //L
  {0b11111, 0b01000, 0b11111}, //M
  {0b11111, 0b10000, 0b01111}, //N
  {0b11111, 0b10001, 0b11111}, //O
  {0b11111, 0b10100, 0b11100}, //P
  {0b11111, 0b10011, 0b11111}, //Q
  {0b11111, 0b10110, 0b11101}, //R
  {0b11101, 0b10101, 0b10111}, //S
  {0b10000, 0b11111, 0b10000}, //T
  {0b11111, 0b00001, 0b11111}, //U
  {0b11110, 0b00001, 0b11110}, //V
  {0b11111, 0b00010, 0b11111}, //W
  {0b11011, 0b00100, 0b11011}, //X
  {0b10000, 0b01111, 0b10000}, //Y
  {0b10011, 0b10101, 0b11001}  //Z
};

String str = "twi";

void setup()
{
  Serial.begin(9600);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  str.toLowerCase();
}

void loop()
{
  for(unsigned int i = 0; i < str.length(); ++i)
  {
    unsigned int n = str.charAt(i) - 'a';
    for(int j = 0; j < 5; ++j)
    {
       byte b = t[n][j];
       digitalWrite(LED0, bitRead(b, 4));
       digitalWrite(LED1, bitRead(b, 3));
       digitalWrite(LED2, bitRead(b, 2));
       digitalWrite(LED3, bitRead(b, 1));
       digitalWrite(LED4, bitRead(b, 0));
       delay(DTIME);
    }
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(LETTER_DELAY);
  }

}



