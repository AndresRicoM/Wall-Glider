/*

██╗    ██╗ █████╗ ██╗     ██╗          ██████╗ ██╗     ██╗██████╗ ███████╗██████╗ 
██║    ██║██╔══██╗██║     ██║         ██╔════╝ ██║     ██║██╔══██╗██╔════╝██╔══██╗
██║ █╗ ██║███████║██║     ██║         ██║  ███╗██║     ██║██║  ██║█████╗  ██████╔╝
██║███╗██║██╔══██║██║     ██║         ██║   ██║██║     ██║██║  ██║██╔══╝  ██╔══██╗
╚███╔███╔╝██║  ██║███████╗███████╗    ╚██████╔╝███████╗██║██████╔╝███████╗██║  ██║
 ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚══════╝     ╚═════╝ ╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

 Wall Glider is a  modular omnidirectional robotic assistant that is designed to navigate 
 magnetically attached to walls while following a user’s position and actions. The robot 
 has modular magnetic mechanisms that can be switched and adapted for the robot to be used 
 for different purposes such as lighting, security, medical assistance, tool holding and even
 as a space exploration companion. 

 Code for running Wall Glider with a remote control for experimenting interaction and functionality. 

 Andres Rico - 2018
 
 */

#include <AFMotor.h> //Motor Driver Library

AF_DCMotor m1(1); //Create Motor 1
AF_DCMotor m2(2); //Create Motor 2
AF_DCMotor m3(3); //Create Motor 3

int x, y, theta, mag, vx, vy, w1, w2, w3; // Declare control variables. 
//int x, y;

int rc_on = 16; //Receiver for controller. 

void read_values(){
  y = (pulseIn(14, HIGH) - 1500) / 2;
  x = (pulseIn(15, HIGH) - 1500) / 2;
  Serial.print(x);
  Serial.print(" , ");
  Serial.println(y);
  delay(5);
}

//Possible movements for Wall Glider

void east() { //Move East
  m1.setSpeed(0);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m1.run(RELEASE);
  m2.run(BACKWARD);
  m3.run(FORWARD);
}

void northeast() { //Move Northeast
  m1.setSpeed(255);
  m2.setSpeed(0);
  m3.setSpeed(255);
  m1.run(FORWARD);
  m2.run(RELEASE);
  m3.run(BACKWARD);
}

void north() { //Move North
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m1.run(FORWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
}

void northwest() { //Move Northwest
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(0);
  m1.run(FORWARD);
  m2.run(BACKWARD);
  m3.run(RELEASE);
}

void west() { //Move west
  m1.setSpeed(0);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m1.run(RELEASE);
  m2.run(FORWARD);
  m3.run(BACKWARD);
}

void southwest() { //Move southwest
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(0);
  m1.run(BACKWARD);
  m2.run(FORWARD);
  m3.run(RELEASE);
}

void south() { //Move south
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m1.run(BACKWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
}

void southeast() { //Move southeast
  m1.setSpeed(255);
  m2.setSpeed(0);
  m3.setSpeed(255);
  m1.run(BACKWARD);
  m2.run(RELEASE);
  m3.run(FORWARD);
}


void setup() {
  
  Serial.begin(9600); //Begin serial communication
  pinMode(14, INPUT); //Activate input pins for RC Receiver.
  pinMode(15, INPUT);
  pinMode(16, OUTPUT);
  digitalWrite(rc_on, HIGH);
}

void loop() {
  
  read_values(); //Read Control variables

  //Control configuration cases for operation. 

  while (((x > -50) && (x < 50)) && ((y > -50) && (y < 50)))  {
    m1.run(RELEASE);
    m2.run(RELEASE);
    m3.run(RELEASE);
    read_values();
  }

  while ((x > 255) or (x < -255)) {
    m1.run(RELEASE);
    m2.run(RELEASE);
    m3.run(RELEASE);
    read_values();
  }

  while ((x > 50) && ((y > -50) && (y < 50))) {
    east();
    read_values();  
  }

  while ((x > 50) && (y > 50)) {
    northeast();
    read_values();
  }

  while ((y > 50) && ((x > -50) && (x < 50))) {
    north();
    read_values();
  }

  while ((x < -50) && (y > 50)) {
    northwest();
    read_values(); 
  }

  while ((x < -50) && ((y > -50) && (y < 50))) {
    west();
    read_values();
  }

  while ((x < -50) && (y < -50)) {
    southwest();
    read_values();
  }

  while ((y < -50) && ((x > -50) && (x < 50))) {
    south();
    read_values();
  }

  while ((y < -50) && (x < -50)) {
    southeast();
    read_values(); 
  }

  m1.run(RELEASE); //Stop motors when there is no indications from controller. 
  m2.run(RELEASE);
  m3.run(RELEASE);
}
