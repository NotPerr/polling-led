
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
};

byte rowDataMatrix[8] = {
  B10000001,
  B11000011,
  B11100111,
  B11100111,
  B11100111,
  B11100111,
  B11000011,
  B10000001
};




void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);  
    pinMode(dataPin, OUTPUT);
}

void loop()
{ 
  for(byte i = 0; i < 8; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    digitalWrite(latchPin, HIGH);
    delay(1);
    }
}
