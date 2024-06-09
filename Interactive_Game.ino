#include <Adafruit_CircuitPlayground.h>
#include <time.h>

int Score = 0;
int HP = 2;
int Pos = 6;
int LButtonPin = 4;
int RButtonPin = 5;
int SwitchPin = 7;
int UserColor;
int DeviceColor;
int DiffScale = 1;
int r;
int g;
int b;
int RandNum;
bool Boot = true;
bool Starting = true;
bool SwitchState;
volatile bool Lbuttonflag = false;
volatile bool Rbuttonflag = true;
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
  while(!Serial);
  attachInterrupt(digitalPinToInterrupt(LButtonPin), LbuttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(RButtonPin), RbuttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(SwitchPin), switchISR, CHANGE);
  randomSeed(analogRead(0));
  SwitchState = CircuitPlayground.slideSwitch();
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

// INPUT LOGIC //
void buttoncheck(){
if(Rbuttonflag){
  delay(5);
  CircuitPlayground.setPixelColor(2, 0, 255, 0);
  UserColor = 1;
  Rbuttonflag = false;
}

if(Lbuttonflag){
  delay(5);
  CircuitPlayground.setPixelColor(2, 0, 0, 255);
  UserColor = 2;
  Lbuttonflag = false;
}

if(switchFlag){
  delay(5);
  SwitchState = CircuitPlayground.slideSwitch();
  switchFlag = false;

}
if(SwitchState && (CircuitPlayground.soundSensor() > 70)){
   CircuitPlayground.setPixelColor(2, 255, 0, 0);
   UserColor = 3;
}
}

// HP LOGIC //
void HPcheck(){
if(HP == 2){
     CircuitPlayground.setPixelColor(9, 255, 0, 0);
     CircuitPlayground.setPixelColor(8, 255, 0, 0);
  }
  else if(HP == 1){
    CircuitPlayground.setPixelColor(9, 255, 0, 0);
    CircuitPlayground.setPixelColor(8, 0, 0, 0);
  }
  else if(HP == 0){
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
    CircuitPlayground.setPixelColor(8, 0, 0, 0);
  } else if(HP = -1){
    Serial.println("Score: ");
    Serial.println(Score);
    for(int i = 3; i>= 0; i--){
    for(int i=10; i>=0; i--) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
  delay(500);
  CircuitPlayground.clearPixels();
   delay(500);
    }
    //PLay game over sound
    HP = 2;
    Score = 0;
    Rbuttonflag = true;
    Starting = true;
    Boot = true;
  }
}

///Delay Logic///
void delayRamp(){
  if(Score >= 0 && Score <= 5){
    delay(300);
  }else if(Score > 5 && Score <= 10){
    delay(250);
  }else if(Score > 10 && Score <= 20){
    delay(200);
  }else if(Score > 20 && Score <= 30){
    delay(150);
  }
}

void loop() {

HPcheck();

  CircuitPlayground.setPixelColor(7, 255, 255, 255);

buttoncheck();

//Sound Logic

// GAME LOGIC //
if(Starting = true){
  HPcheck();
//Random Num
if(!SwitchState){
 RandNum = random(1, 3);
}
else if(SwitchState){
 RandNum = random(1, 4);
}
if(RandNum == 1){
  r = 0;
  g = 255;
  b = 0;
  DeviceColor = 1;
}
else if(RandNum == 2){
  r = 0;
  g = 0;
  b = 255;
  DeviceColor = 2;
}
else if(RandNum == 3){
  r = 255;
  g = 0;
  b = 0;
  DeviceColor = 3;
}
Starting = false;
}

// Light Logic //
CircuitPlayground.setPixelColor(0, 0, 0, 0);
Pos = 6;
for(int i=6; i>2; i--) {
  buttoncheck();
    CircuitPlayground.setPixelColor(i, r, g, b);
    if(i != 6){
    CircuitPlayground.setPixelColor(i + 1, 0, 0, 0);
    }
    delayRamp();

    Pos--;
  }
if(Pos == 2){
  CircuitPlayground.setPixelColor(3, 0, 0, 0);
  if(UserColor == DeviceColor){
      Score == Score++;
  //Happy Sound
  Starting = true;
  
  } else {
    HP = HP - 1;
    delayRamp();
    for(int i=1; i>=0; i--) {
    buttoncheck();
    CircuitPlayground.setPixelColor(i, r, g, b);
    if(i != 1){
    CircuitPlayground.setPixelColor(i + 1, 0, 0, 0);
    }
    //delay(250 % DiffScale);
    delayRamp();
    }
    Starting = true;
    
 
  }


}
}