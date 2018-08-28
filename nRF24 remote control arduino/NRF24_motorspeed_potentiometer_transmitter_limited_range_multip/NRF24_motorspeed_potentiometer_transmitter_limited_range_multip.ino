// Sketch uses a potentiometer to control speed

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int msg1[1];
int msg2[1];
RF24 radio(9,10); // Create a radio by identifying Chip Enable pin and Slave Select pin - RF24 radio(CE_PIN, CSN_PIN) 
const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipeTwo = 0xE8E8F0F0D2LL; // Second pipe, must share first 32bits (first 8 characters)
int sensorPin1 = A0; // Potentiometer 1 for first motor
int sensorPin2 = A1; // Potentiometer 2 for second motor
int ledPin1 = 6; // PWM pin for Potentiometer 1 - change brightness of led to give viusal feedback
int ledPin2 = 3; // PWM pin for Potentiometer 2 - change brightness of led to give viusal feedback

// int oldvalue; // this variable is used to determine if motorSpeed is increasing or decreasing

void setup(void){
 Serial.begin(9600);
 radio.begin();
 
 pinMode(ledPin1, OUTPUT); //  setup LED pin
 pinMode(ledPin2, OUTPUT); //  setup LED pin

 }

void loop(void){
  int sensorValue1;
  int motorSpeed1;
  int sensorValue2;
  int motorSpeed2;
 
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  
//  if (sensorValue <= 200) // corresponds to 50/255 or 20%
//  {motorSpeed = 0;}
//  if (sensorValue >= 480) // corresponds to 120/255 or 47%
//    {motorSpeed = 120;}
//  else 
//    {
     motorSpeed1 =  motorSpeed1 = map(sensorValue1, 0, 1023, 255, 0);
     motorSpeed1 = constrain(motorSpeed1, 0, 255); 
     
     motorSpeed2 =  motorSpeed2 = map(sensorValue2, 0, 1023, 255, 0);
     motorSpeed2 = constrain(motorSpeed2, 0, 255); 
//   }
    
  msg1[0] = motorSpeed1; 
  msg2[0] = motorSpeed2;
  Serial.print("Motor1 - ");
  Serial.print(msg1[0] );
  Serial.print("Motor2 - ");
  Serial.println(msg2[0] );

//Send to motor 1
 radio.openWritingPipe(pipe);
 radio.write(msg1, 1);

//Send to motor 2 
 radio.openWritingPipe(pipeTwo);
 radio.write(msg2, 1);

  analogWrite(ledPin1, motorSpeed1); // Adjust LED brightness to reflect motorSpeed
  analogWrite(ledPin2, motorSpeed2); // Adjust LED brightness to reflect motorSpeed


/*   if (MotorSpeed > oldvalue) 
       {Serial.print("Speed is increasing :)"); Serial.println(motorSpeed);}
     if (motorSpeed < oldvalue)
       {Serial.print("Speed is decreasing :("); Serial.println(motorSpeed);}
      
     oldvalue = motorSpeed;
*/
}
