//Code created by Jake Denison
//Version 4.0
//PC NASA ASCEND TEAM
///////////////////////////////////////////

#include <Wire.h>

//Define all the pins for the motors
int fwdPin = 11; //foward pin
int revPin = 10; //reverse pin
int motor1Pin = 2; //first motor
int motor2Pin = 3; //second motor
int motor3Pin = 4; //third motor
int motor4Pin = 5; //fourth motor
int motor5Pin = 6; //fifth motor
int i;
int motorSelect;
boolean sampled0 = true; // because we don't want to sample off the bat
boolean sampled1 = true;
boolean sampled2 = true;
boolean sampled3 = true;
boolean sampled4 = true;
int state = -1;
int driver = 12;
int done = 13;
boolean started = false;

void driveMotor(int motorNum); // forward declaration, for compiler

///////////////////////////////////////////

void setup(){
  
//set output pins
  for (int i = 3; i < 8; i++ ){ // set pins 3 - 7 to output for each motor enable
    pinMode(i, OUTPUT);
  }  
  
  pinMode(fwdPin, OUTPUT); 
  pinMode(revPin, OUTPUT);
  pinMode(done, OUTPUT);
  digitalWrite(done, LOW);
  pinMode(driver, INPUT);
}
///////////////////////////////////////////////////////

void loop() {
  if(digitalRead(driver) == HIGH && !started) {
    state = 0;
    started = true;
  }
  switch (state){
    case 0:
      if(!sampled0)
        driveMotor (motor1Pin);
      if(digitalRead(driver) == LOW)
        state++;
      break;
    case 1:
      if(!sampled1)
        driveMotor (motor2Pin);
      if(digitalRead(driver) == HIGH)
        state++;  
      break;
    case 2:
      if(!sampled2)
        driveMotor (motor3Pin);
      if(digitalRead(driver) == LOW)
        state++;  
      break;
    case 3:
      if(!sampled3)
        driveMotor (motor4Pin);
      if(digitalRead(driver) == HIGH)
        state++;  
      break;
    case 4:
      if(!sampled4)
        driveMotor (motor5Pin);
      if(digitalRead(driver) == LOW)
        state++;  
      break;
    default:
      break;
  }
}
///////////////////////////////////////////////////
void driveMotor(int motorNum){
  switch(motorNum) {
    case 2:
      sampled0 = true;
      break;
    case 3:
      sampled1 = true;
      break;
    case 4:
      sampled2 = true;
      break;
    case 5:
      sampled3 = true;
      break;
    case 6:
      sampled4 = true;
      break;        
  }
  digitalWrite(done, LOW);
  int fwdDel(120000); 
  digitalWrite(motorNum, HIGH); //enable first selected motor
  digitalWrite(fwdPin, HIGH); //begin sample collection
  digitalWrite(revPin, LOW); 
  delay(fwdDel); //sample collection completed
  digitalWrite(fwdPin, LOW);
  digitalWrite(revPin, LOW); //shutdown
  digitalWrite(done, HIGH);
}
