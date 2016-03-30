//Code created by Jake Denison
//Version 2.5
//PC NASA ASCEND TEAM
//##########################################################

#include <Wire.h>

//Define all the pins for the motors
int fwdPin = 11; //foward pin (duh)
int revPin = 10; //reverse pin (duh)
int motor1Pin = 3; //first motor
int motor2Pin = 4; //second motor
int motor3Pin = 5; //third motor
int motor4Pin = 6; //fourth motor
int motor5Pin = 7; //fifth motor
int motor6Pin = 8; //sixth motor
int motor7Pin = 9; //seventh motor
int motor8Pin = 10; //eighth motor
int motor9Pin = 12; //nineth motor
int motor10Pin = 13; //tenth motor
int driveTime = 10000; //motor run time
int sampCount = 0; //amount of samples collected
int i;
int motorSelect;
char sCode = '\0';
boolean sampled = true; // because we don't want to sample off the bat

void driveMotor(int motorNum); // forward declaration, for compiler
    
void setup(){
  
//set output pins
  for (int i = 3; i < 14; i++ ){// set pins 3 - 13 to output
    pinMode(i, OUTPUT);
  }  
  
  pinMode(fwdPin, OUTPUT);
  pinMode(revPin, OUTPUT);

  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}


void loop() {
  switch (sCode){
    case '0':
      if(!sampled)
        driveMotor (motor1Pin);
      break;
    case '1':
      if(!sampled)
        driveMotor (motor2Pin);
      break;
    case '2':
      if(!sampled)
        driveMotor (motor3Pin);
      break;
    case '3':
      if(!sampled)
        driveMotor (motor4Pin);
      break;
    case '4':
      if(!sampled)
        driveMotor (motor5Pin);
      break;
    case '5':
      if(!sampled)
        driveMotor (motor6Pin);
      break;
    case '6':
      if(!sampled)
        driveMotor (motor7Pin);
      break;
    case '7':
      if(!sampled)
        driveMotor (motor8Pin);
      break;
    case '8':
      if(!sampled)
        driveMotor (motor9Pin);
      break;
    case '9':
      if(!sampled)
        driveMotor (motor10Pin);
      break;
    default:
      break;
  }

}



void driveMotor(int motorNum){
  sampled = true;
  int revDel(5000); //drive times
  int fwdDel(10000); 
  digitalWrite(motorNum, HIGH); //enable selected motor
  digitalWrite(fwdPin, LOW); //drives motor in reverse to clear out stagnant air before collecting sample
  digitalWrite(revPin, HIGH);
  delay(revDel);
  digitalWrite(revPin, LOW); //airway clear completed

  digitalWrite(fwdPin, HIGH); //begin sample collection
  digitalWrite(revPin, LOW); 
  delay(fwdDel); //sample collection completed

  digitalWrite(fwdPin, LOW);
  digitalWrite(revPin, LOW); //shutdown
}

/*
 * recieveEvent reads bytes sent from the master controller, appends 
 * it to the message string and then marks a message recieved if it
 * is the last message
 */
void receiveEvent(int nBytes) {
  sCode = Wire.read();
  sampled = false;
}

/*
 * requestEvent sends the sCode back to the master controller
 */
void requestEvent() {
  Wire.write(sCode);
  Wire.write(sampled);
}

