#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262
#define BUTTON 2

int melody[] = {
  NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3,
  NOTE_A3, NOTE_A3, NOTE_G3, 0 };

int noteDurations[] = {
 4,4,4,4,4,4,4,4
};

int thisNote = -1; int noteDuration = 0;
long previousTime = 0,
     presentTime = 0,
     pauseBetweenNotes = 0;

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

byte another[8] = {
  B00100100,
  B01100110,
  B11100111,
  B11100111,
  B11100111,
  B11100111,
  B01100110,
  B00100100
};

byte previousState = 1, presentState = 1;

void checkToPlay(){
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes){
    thisNote += 1;
    if(thisNote >= 8){
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }else{
      noteDuration = 500 / noteDurations[thisNote];
      tone(9, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}


void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);  
    pinMode(dataPin, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
}

void loop()
{ 
  presentState = digitalRead(BUTTON);
  for(int i = 0; i < 8; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    if(presentState == 1){
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    }else shiftOut(dataPin, clockPin, MSBFIRST, another[i]);
      digitalWrite(latchPin, HIGH);
      checkToPlay();
      delay(1);
    
      
    }
}
