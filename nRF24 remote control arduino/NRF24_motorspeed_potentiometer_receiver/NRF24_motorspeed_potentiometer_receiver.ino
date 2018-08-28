/*Sketch receives a message from RF24 unit and writes the 
message to a PWM pin, to spin a motor.
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg1[1];
int msg2[1];
RF24 radio(9,10); // Uno
// RF24 radio(40,53); // Mega // Create a radio by identifying Chip Enable pin and Slave Select pin - RF24 radio(CE_PIN, CSN_PIN)
const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipeTwo = 0xE8E8F0F0D2LL; // Second pipe, must share first 32bits (first 8 characters)

int Motor = 3; //needs to be a PWM pin
int MotorSpeed;
int ledPin = 6; // PWM pin for Potentiometer 2 - change brightness of led to give viusal feedback

void setup(void){
 Serial.begin(9600);
 radio.begin();

 radio.openReadingPipe(1,pipe); //for motor 1 setup
// radio.openReadingPipe(1,pipeTwo); //for motor 2 setup

 radio.startListening();
 
 pinMode(ledPin, OUTPUT); //  setup LED pin 
 pinMode(Motor, OUTPUT);
 
}

void loop(void){
 if (radio.available()){
   bool done = false;    
   while (!done){
     done = radio.read(msg1, 1); //for motor 1
   Serial.println(msg1[0]);      //for motor 1
//     done = radio.read(msg2, 1);   // for motor 2   
//     Serial.println(msg2[0]);      // for motor 2
     
     MotorSpeed = msg1[0];       // for motor 1
//     MotorSpeed = msg2[0];         // for motor 2
     analogWrite(Motor, MotorSpeed);
     analogWrite(ledPin, MotorSpeed);

   }  
 }
 else{Serial.println("No radio available");}
 delay(1000);
}
