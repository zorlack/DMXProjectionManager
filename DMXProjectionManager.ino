// Code for a Arduino-based DMX Receiver Device which can
// operate a servo to douse a projector, and also send keyboard
// instructions to a computer running a slide show.
//
// initial version hard-coded to DMX address and to key-send 
// thresholds.
//
// Based on an example by:
// Copyright (c) 2011 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx


#include "DMXSerial.h"
#include <Servo.h> 
// Constants for demo program

//Define DMX Addresses
int dmxServoAddress = 178;
int dmxKeyboardAddress = 179;

//Define variables for Servo
int servoPWMPin = 9;
Servo dowserServo;
float servoStartPosition = 0.0;
float servoEndPosition = 180.0;
int dmxLastServoValue = -128;

//Define thresholds for keyboard data
char dmxValueLeftKeyCode = KEY_PAGE_UP;
int dmxValueLeftMin = 32;
int dmxValueLeftMax = 96;
char dmxValueRightKeyCode = KEY_PAGE_DOWN;
int dmxValueRightMin = 160;
int dmxValueRightMax = 192;
int dmxLastKeyboardValue = 0;
int keyPressDuration = 20; //ms




void setup () {
  //initiailize DMX Receiver
  DMXSerial.init(DMXReceiver);

  //connect servo object to the appropriate pin
  dowserServo.attach(servoPWMPin);
  
  //initialize keyboard emulation
  Keyboard.begin();
  
  //write some default values to the DMX Serial object
  DMXSerial.write(dmxServoAddress, 0);
  DMXSerial.write(dmxKeyboardAddress, 0);
  
  //initialize debug output
  Serial.begin(9600);
  Serial.println("System Initialized!");
}


void loop() {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();
    
  int dmxServoValue = DMXSerial.read(dmxServoAddress);
  int dmxKeyboardValue = DMXSerial.read(dmxKeyboardAddress);
  
  //write the appropriate value to the servo:
  if(dmxServoValue != dmxLastServoValue) 
  {    
    float servoValue = (float)dmxServoValue * ((servoEndPosition-servoStartPosition)/255.0);
    Serial.print("Changing Servo to: ");
    Serial.print(servoValue);
    Serial.println(" degrees");
    
    //write the values
    dowserServo.write(servoValue);
    dmxLastServoValue = dmxServoValue;
  }
  
  if(dmxKeyboardValue != dmxLastKeyboardValue) 
  {
    //We've detected a change in keyboard value!
    //lets write out the appropriate value!
    if( dmxKeyboardValue  >= dmxValueLeftMin && dmxKeyboardValue < dmxValueLeftMax)
    {
      Serial.println("Writing Left Arrow Key");
      
      //write the keypress
      Keyboard.press(dmxValueLeftKeyCode);
      delay(keyPressDuration);
      Keyboard.release(dmxValueLeftKeyCode);
    }
    if( dmxKeyboardValue  >= dmxValueRightMin && dmxKeyboardValue < dmxValueRightMax)
    {
      Serial.println("Writing Right Arrow Key");
      Keyboard.press(dmxValueRightKeyCode);
      delay(20);
      Keyboard.release(dmxValueRightKeyCode);
    }
    
    //update the value of dmxLast.
    dmxLastKeyboardValue = dmxKeyboardValue;    
  }
}

// End.
