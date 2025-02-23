#include <Servo.h>
// #include <Dabble.h>

Servo armBase;
Servo armMiddle;
Servo buttonPress;

#define bPress 9             //button presser
#define aBase 10             //arm at base
#define aMid 11              //arm in middle
#define SensorL 4            //ir sensor Left
#define SensorM 5            //ir sensor Middle
#define SensorR 6            //ir sensor Right
#define LeftFrontforward 7   //front left wheel forward
#define LeftFrontreverse 8   //front left wheel reverse
#define RightFrontforward 12  //front right wheel forward
#define RightFrontreverse 13  //front right wheel reverse
#define LFCtrl A2            //left front control
#define RFCtrl A3            //right front control
#define LeftRearforward 3   //rear left wheel forward
#define LeftRearreverse 2    //rear left wheel reverse
#define RightRearforward A0  //rear right wheel forward
#define RightRearreverse A1  //rear right wheel reverse
#define LRCtrl A4            //left rear control
#define RRCtrl A5            //right rear control
// #define CUSTOM_SETTINGS
// #define INCLUDE_GAMEPAD_MODULE


//control variables
bool Auto = true;
bool onLine = false;
bool atEnd = false;
int aBasePos = 0;
int aMidPos = 0;
int bPressPos = 0;


/////////////////
//MOTOR CONTROL//
/////////////////
void TurnFrontLeft(int val) {
  if (val < 0) {
    digitalWrite(LeftFrontforward, LOW);
    digitalWrite(LeftFrontreverse, HIGH);
    analogWrite(LFCtrl, val * -1);
  } else {
    digitalWrite(LeftFrontforward, HIGH);
    digitalWrite(LeftFrontreverse, LOW);
    analogWrite(LFCtrl, val);
  }
}
void TurnFrontRight(int val) {
  if (val < 0) {
    digitalWrite(RightFrontforward, LOW);
    digitalWrite(RightFrontreverse, HIGH);
    analogWrite(RFCtrl, val * -1);
  } else {
    digitalWrite(RightFrontforward, HIGH);
    digitalWrite(RightFrontreverse, LOW);
    analogWrite(RFCtrl, val);
  }
}
void TurnRearLeft(int val) {
  if (val < 0) {
    digitalWrite(LeftRearforward, LOW);
    digitalWrite(LeftRearreverse, HIGH);
    analogWrite(LRCtrl, val * -1);
  } else {
    digitalWrite(LeftRearforward, HIGH);
    digitalWrite(LeftRearreverse, LOW);
    analogWrite(LRCtrl, val);
  }
}
void TurnRearRight(int val) {
  if (val < 0) {
    digitalWrite(RightRearforward, LOW);
    digitalWrite(RightRearreverse, HIGH);
    analogWrite(RRCtrl, val * -1);
  } else {
    digitalWrite(RightRearforward, HIGH);
    digitalWrite(RightRearreverse, LOW);
    analogWrite(RRCtrl, val);
  }
}
void Drive(int FrontLeft, int FrontRight, int RearLeft, int RearRight){
    TurnFrontLeft(FrontLeft);
    TurnFrontRight(FrontRight);
    TurnRearLeft(RearLeft);
    TurnRearRight(RearRight);
}
void MoveArm(){
  armBase.write(aBasePos);
  armMiddle.write(aMidPos);
}
void PushButton(){
  buttonPress.write(bPressPos);
}


////////////////
//Tele-Op Mode//
////////////////
void TeleOp(){
  // Dabble.processInput();
  // if(GamePad.isUpPressed()){
  //   Drive(128, 128, 128, 128);
  // } else if(GamePad.isDownPressed()){
  //   Drive(-128, -128, -128, -128);
  // } else if(GamePad.isLeftPressed()){
  //   Drive(-128, 128, -128, 128);
  // } else if(GamePad.isRightPressed()){
  //   Drive(128, -128, 128, -128);
  // }
  // if(GamePad.isSquarePressed()){
  //   if(aBasePos<180){
  //     aBasePos=aBasePos+1;
  //   }
  //   MoveArm();
  // } else if(GamePad.isCirclePressed()){
  //   if(aBasePos>0){
  //     aBasePos=aBasePos-1;
  //   }
  //   MoveArm();
  // }
  // if(GamePad.isTrianglePressed()){
  //   if(aMidPos<850){
  //     aMidPos=aMidPos+1;
  //   }
  //   MoveArm();
  // } else if(GamePad.isCrossPressed()){
  //   if(aMidPos>0){
  //     aMidPos=aMidPos-1;
  //   }
  //   MoveArm();
  // }
  // if(GamePad.isStartPressed()){
  //   //idk
  // } else if(GamePad.isSelectPressed()){
  //   //idk2
  // }
}


///////////////////
//Autonomous Mode//
///////////////////
void autoMode(){
  ///////////////
  //follow line//
  ///////////////
  
  //High = on line

  if (digitalRead(SensorM) == HIGH) {
    onLine = true;
    // Drive(128, 128, 128, 128);  //move forward
    Serial.println("fowarding");
  } else {
    onLine = false;
  }
  if (!onLine) {
    if (digitalRead(SensorL) == HIGH) {
      // Drive(0, 128, 0, 0);  //move right side forward
      Serial.println("lefting");
    } else if (digitalRead(SensorR) == HIGH) {
      // Drive(128, 0, 0, 0);  //move left side forward
      Serial.println("righting");
    }
  } else {
    if (digitalRead(SensorL) == HIGH || digitalRead(SensorR) == HIGH) {
      atEnd = true;
      Drive(0, 0, 0, 0);  //stop vehicle
      Serial.println("end");
    }
  }

  //////////////////
  //pick up bucket//
  //////////////////
  if (atEnd) {         //only straight forward code here. Use delay to wait for action to finish
    Drive(0, 0, 0, 0);  //stop vehicle

    for(int i=0; i<100; i++){  //extend arm out from under
      aBasePos=i;
      MoveArm();
      delay(15);
    }
    delay(1000);

    for(int i=0; i<85; i++){  //extend arm fully
      aMidPos=i;
      MoveArm();
      delay(15);
    }
    delay(1000);

    // Drive(128, 128, 128, 128);  //move forward
    delay(1000);

    Drive(0, 0, 0, 0);  //stop vehicle

    while(aBasePos<135&&aMidPos>45){  //Raise arm but keep front part level(maybe a bit tilted is ok)
      aBasePos++;
      aMidPos--;
      MoveArm();
      delay(15);
    }
    delay(1000);

    Auto = false;
    Serial.println("ended");
  }
}


void setup() {
  armBase.attach(aBase);
  armMiddle.attach(aMid);
  buttonPress.attach(bPress);
  pinMode(SensorL, INPUT);
  pinMode(SensorM, INPUT);
  pinMode(SensorR, INPUT);
  pinMode(LeftFrontforward, OUTPUT);
  pinMode(LeftFrontreverse, OUTPUT);
  pinMode(RightFrontforward, OUTPUT);
  pinMode(RightFrontreverse, OUTPUT);
  pinMode(LeftRearforward, OUTPUT);
  pinMode(LeftRearreverse, OUTPUT);
  pinMode(RightRearforward, OUTPUT);
  pinMode(RightRearreverse, OUTPUT);
  pinMode(LFCtrl, OUTPUT);
  pinMode(RFCtrl, OUTPUT);
  pinMode(LRCtrl, OUTPUT);
  pinMode(RRCtrl, OUTPUT);
  Serial.begin(9600);
  // Dabble.begin(9600);
  delay(1000);

  //reset all positions
  TurnFrontLeft(0);
  TurnFrontRight(0);
  TurnRearLeft(0);
  TurnRearRight(0);
  armBase.write(0);
  armMiddle.write(0);
  buttonPress.write(0);
}

void loop() {

  // for(int i=0; i<180; i++){
  //   bPressPos=i;
  //   PushButton();
  //   delay(15);
  // }
  // for(int i=180; i>0; i--){
  //   bPressPos=i;
  //   PushButton();
  //   delay(15);
  // }

  // Drive(255, 255, 255, 255);
  // delay(1000);
  // Drive(-255, 255, 0, 0);
  // delay(1000);
  // Drive(0, 0, 0, 0);
  // for(int i=0; i<90; i++){
  //   aBasePos=i;
  //   MoveArm();
  //   delay(15);
  // }
  // for(int i=0; i<80; i++){
  //   aMidPos=i;
  //   MoveArm();
  //   delay(15);
  // }
  // for(int i=80; i>0; i--){
  //   aMidPos=i;
  //   MoveArm();
  //   delay(15);
  // }
  // for(int i=90; i>0; i--){
  //   aBasePos=i;
  //   MoveArm();
  //   delay(15);
  // }

  //////////////
  //Autonomous//
  //////////////
  if (Auto) {
    autoMode();
  }

  ///////////
  //Tele-op//
  ///////////
  // else {
  //   TeleOp();
  // }

}
