#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);
  pinMode(2,OUTPUT);//change the pins as needed
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);     

}

void loop() {
  // put your main code here, to run repeatedly:
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    //This is just for front pair of motors
    Serial.print("UP");
    digitalWrite(2, HIGH);//in1
    digitalWrite(3, LOW);//in2
    digitalWrite(4, HIGH);//in3
    digitalWrite(5, LOW);//in4
    digitalWrite(6, HIGH);//enable for front left motor
    digitalWrite(7, HIGH);//enable for front right motor

    //this for back pair
    digitalWrite(8, HIGH);//in1
    digitalWrite(9, LOW);//in2
    digitalWrite(10, HIGH);//in3
    digitalWrite(11, LOW);//in4
    digitalWrite(12, HIGH);//enable for back left motor
    digitalWrite(13, HIGH);//enable for back right motor

  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");//robot moves backwards
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);

    digitalWrite(8, HIGH);//in1
    digitalWrite(9, LOW);//in2
    digitalWrite(10, HIGH);//in3
    digitalWrite(11, LOW);//in4
    digitalWrite(12, HIGH);//enable for bac left motor
    digitalWrite(13, HIGH);//enable for back right motor
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");//moves rover left in theory
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);

    delay(100)

    digitalWrite(8, LOW);//in1
    digitalWrite(9, HIGH);//in2
    digitalWrite(10, LOW);//in3
    digitalWrite(11, HIGH);//in4
    digitalWrite(12, HIGH);//enable for back left motor
    digitalWrite(13, LOW);//enable for back right motor
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");//moves the rover right in theory prob kinda janky
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(100)

    digitalWrite(8, LOW);//in1
    digitalWrite(9, HIGH);//in2
    digitalWrite(10, LOW);//in3
    digitalWrite(11, HIGH);//in4
    digitalWrite(12, LOW);//enable for front left motor
    digitalWrite(13, HIGH);//enable for front right motor
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    //we could tell it to turn on the automatic mode if we click this button
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    digitalWrite(2, HIGH);
        

  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  

}
