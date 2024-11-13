#include <Servo.h>

Servo armBase;
Servo armMiddle;
#define aBase 16 //arm base
#define aMid 17 //arm middle
#define SensorL 1 //ir sensor Left
#define SensorM 2 //ir sensor Middle
#define SensorR 3 //ir sensor Right
#define LeftFrontforward 4 //front left wheel forward
#define LeftFrontreverse 5 //front left wheel reverse
#define RightFrontforward 6 //front right wheel forward
#define RightFrontreverse 7 //front right wheel reverse
#define LeftRearforward 8 //rear left wheel forward
#define LeftRearreverse 9 //rear left wheel reverse
#define RightRearforward 10 //rear right wheel forward
#define RightRearreverse 11 //rear right wheel reverse
#define LFCtrl 12 //left front control
#define RFCtrl 13 //right front control
#define LRCtrl 14 //left rear control
#define RRCtrl 15 //right rear control



    /////////////////
    //MOTOR CONTROL//
    /////////////////
void TurnFrontLeft(int val){
  if(val<0){
    digitalWrite(LeftFrontforward, LOW);
    digitalWrite(LeftFrontreverse, HIGH);
    analogWrite(LFCtrl, val*-1);
  } else if(val>0){
    digitalWrite(LeftFrontforward, HIGH);
    digitalWrite(LeftFrontreverse, LOW);
    analogWrite(LFCtrl, val);
  } else{
    digitalWrite(LeftFrontforward, LOW);
    digitalWrite(LeftFrontreverse, LOW);
    analogWrite(LFCtrl, val);
  }
}
void TurnFrontRight(int val){
  if(val<0){
    digitalWrite(RightFrontforward, LOW);
    digitalWrite(RightFrontreverse, HIGH);
    analogWrite(RFCtrl, val*-1);
  } else if(val>0){
    digitalWrite(RightFrontforward, HIGH);
    digitalWrite(RightFrontreverse, LOW);
    analogWrite(RFCtrl, val);
  } else{
    digitalWrite(RightFrontforward, LOW);
    digitalWrite(RightFrontreverse, LOW);
    analogWrite(RFCtrl, val);
  }
}
void TurnRearLeft(int val){
  if(val<0){
    digitalWrite(LeftRearforward, LOW);
    digitalWrite(LeftRearreverse, HIGH);
    analogWrite(LRCtrl, val*-1);
  } else if(val>0){
    digitalWrite(LeftRearforward, HIGH);
    digitalWrite(LeftRearreverse, LOW);
    analogWrite(LRCtrl, val);
  } else{
    digitalWrite(LeftRearforward, LOW);
    digitalWrite(LeftRearreverse, LOW);
    analogWrite(LRCtrl, val);
  }
}
void TurnRearRight(int val){
  if(val<0){
    digitalWrite(RightRearforward, LOW);
    digitalWrite(RightRearreverse, HIGH);
    analogWrite(RRCtrl, val*-1);
  } else if(val>0){
    digitalWrite(RightRearforward, HIGH);
    digitalWrite(RightRearreverse, LOW);
    analogWrite(RRCtrl, val);
  } else{
    digitalWrite(RightRearforward, LOW);
    digitalWrite(RightRearreverse, LOW);
    analogWrite(RRCtrl, val);
  }
}

//control variables
bool Auto = true;
bool onLine = false;
bool atEnd = false;
int aBasePos = 0;
int aMidPos = 0;


void setup(){
  armBase.attach(aBase);
  armMiddle.attach(aMid);
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
  delay(1000);
  
  //reset all positions
  TurnFrontLeft(0);
  TurnFrontRight(0);
  TurnRearLeft(0);
  TurnRearRight(0);
  armBase.write(0);
  armMiddle.write(0);
}

void loop(){

          //////////////
          //Autonomous//
          //////////////
  if(Auto){
    ///////////////
    //follow line//
    ///////////////
      if(digitalRead(SensorM)==1){
        onLine=true;
        TurnFrontLeft(128); //move forward
        TurnFrontRight(128);
        TurnRearLeft(128);
        TurnRearRight(128);
      } else{
        onLine=false;
      }
      if(!onLine){
        if(digitalRead(SensorL)==1){
          TurnFrontLeft(0); //move right side forward
          TurnFrontRight(128);
          TurnRearLeft(0);
          TurnRearRight(0);
        } else if(digitalRead(SensorR)==1){
          TurnFrontLeft(128); //move left side forward
          TurnFrontRight(0);
          TurnRearLeft(0);
          TurnRearRight(0);
        }
      } else{
        if(digitalRead(SensorL)==1&&digitalRead(SensorR)==1){
          atEnd = true;
          TurnFrontLeft(0); //stop vehicle
          TurnFrontRight(0);
          TurnRearLeft(0);
          TurnRearRight(0);
        }
      }

      //////////////////
      //pick up bucket//
      //////////////////
      if(atEnd){ //only straight forward code here. Use delay to wait for action to finish
        armBase.write(90); //extend arm out from under
        armMiddle.write(0);
        delay(1000);
        armBase.write(90); //extend arm fully
        armMiddle.write(90);
        delay(1000);
        TurnFrontLeft(128); //move forward
        TurnFrontRight(128);
        TurnRearLeft(128);
        TurnRearRight(128);
        delay(1000);
        armBase.write(135); //Raise arm but keep front part level(maybe a bit tilted is ok)
        armMiddle.write(45);
        delay(1000);
        Auto=false;
      }
  } 

      ///////////
      //Tele-op//
      ///////////
  else{

  }
  
}
