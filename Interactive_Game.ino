#include <Adafruit_CircuitPlayground.h>

int Score = 0;
int HP = 2;
int Pos = 6;
int LButtonPin = 4;
int RButtonPin = 5;
int SwitchPin = 7;
int UserColor;
int DeviceColor;
int DiffScale = 1;
bool Starting = true;
bool SwitchState;
volatile bool Lbuttonflag = false;
volatile bool Rbuttonflag = false;
volatile bool switchFlag = false;
void LbuttonISR();
void RbuttonISR();
void switchISR();

void setup() {
  CircuitPlayground.begin();
  pinMode(SwitchPin, INPUT_PULLUP);
  pinMode(LButtonPin, INPUT_PULLDOWN);
  pinMode(RButtonPin, INPUT_PULLDOWN);
  Serial.begin(9600);
  !while(Serial)
  attachInterrupt(digitalPinToInterrupt(LButtonPin), LbuttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(RButtonPin), RbuttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(SwitchPin), switchISR, CHANGE);
}

void switchISR(){

  switchFlag = true;

}

void LbuttonISR(){

  Lbuttonflag = true;

}

void RbuttonISR(){

  Rbuttonflag = true;

}

void loop() {
// HP LOGIC //
  if(HP = 2){
     CircuitPlayground.setPixelColor(10, 255, 0, 0);
     CircuitPlayground.setPixelColor(9, 255, 0, 0);
  }
  else if(HP = 1){
    CircuitPlayground.setPixelColor(10, 255, 0, 0);
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
  }
  else if(HP = 0){
    CircuitPlayground.setPixelColor(10, 0, 0, 0);
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
    Serial.println(Score);
    //PLay game over sound
    Starting = true;
  }

  CircuitPlayground.setPixelColor(8, 255, 255, 255);

// INPUT LOGIC //
if(Rbuttonflag){
  delay(5);
  CircuitPlayground.setPixelColor(4, 0, 255, 0);
  Color = 1
  Rbuttonflag = false;
}

if(Lbuttonflag){
  delay(5);
  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  Color = 2
  Lbuttonflag = false;
}

if(switchFlag){
  delay(5);
  SwitchState = CircuitPlayground.slideSwitch();
  switchFlag = false;

}

//Sound Logic

// GAME LOGIC //
if(Starting = true){
  if((Score % (5 * DiffScale)) = 1){
    DiffScale++;
  }
//Random Num
if(SwitchState){
//Rand 1-2
}
else if(!SwitchState){
//Rand 1-3
}
if(RandNum = 1){
  r = 0;
  g = 255;
  b = 0;
}
else if(RandNum = 2){
  r = 0;
  g = 0;
  b = 255;
}
else if(RandNum = 3){
  r = 255;
  g = 0;
  b = 0;
}
Starting = false;
}

// Light Logic //
for(int i=7; i<4; i--) {
    CircuitPlayground.setPixelColor(i, r, g, b);
    if(i != 7){
    CircuitPlayground.setPixelColor(i++, 0, 0, 0);
    }
    delay(250 % DiffScale);
    Pos--;
  }
if(Pos = 4){
  CircuitPlayground.setPixelColor(5, 0, 0, 0);
  if(UserColor = DeviceColor){
  Score = Score++
  //Happy Sound
  Starting = true;
  } else {
    HP = HP--;
    for(int i=4; i>0; i--) {
    CircuitPlayground.setPixelColor(i, r, g, b);
    CircuitPlayground.setPixelColor(i++, 0, 0, 0);
    delay(250 % DiffScale);
    }
    if(DiffScale != 1){
      DiffScale--;
    }
    Starting = true;
  }


}
