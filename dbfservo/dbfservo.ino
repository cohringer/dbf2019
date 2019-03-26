#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define LockServoMin 130
#define LockServoMax 600
#define SERVOMIN  0
#define SERVOMAX  4096
// our servo # counter
uint8_t servonum = 0;
const int Open_LLS = 2; //LLS stands for left limit switch & Open indicates that when it hits this limit switch the wing is folded
const int Close_LLS = 3;
const int Open_RLS = 4;
const int Close_RLS = 5; //RLS stands for right limit switch and Close indicates that when it hits this limit switch the wing is in its flight ready config.
const int Bomb_drop = 6;
const int Wing_fold = 7;
const int Or = 8; // Switch that sets wing folding ability on or off
int pulselen_R_Close = 420; //blaze it
int pulselen_R_Open = 200;
int pulselen_L_Close = 300;
int pulselen_L_Open = 460;
int LOpen =1;
int LClose =1;
int ROpen =1;
int RClose =1;
int Wing_read =0;
int LLockServoMax=335;
int RLockServoMax=325;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void setup() {

  pinMode(Open_LLS, INPUT); 
  pinMode(Close_LLS, INPUT); 
  pinMode(Open_RLS, INPUT); 
  pinMode(Close_RLS, INPUT); 
  //pinMode(Bomb_drop, INPUT);
  pinMode(Wing_fold, INPUT);
  //pinMode(Or, INPUT); 
  
  Serial.begin(9600);
  pwm.begin(); // Initializes driver read
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}
void loop() {
// #Define limits as LeftStowed=LS Left(Flight)Ready=LR RightStow=RS Right(Flight)Ready=RR
// #limitR/LS=limitRight/LeftStowed, limitR/LU=limitRight/LeftFlight
// open is stowed configuration
  
//  int Switch = digitalRead(Or); // Reads status of safety switch
//  int limitLS = digitalRead(Open_LLS);
//  int limitLF = digitalRead(Close_LLS);
//  int limitRS = digitalRead(Open_RLS);
//  int limitRF = digitalRead(Close_RLS);
//  int Wing_read = digitalRead(Wing_fold); // Read state of wing fold signal
//  int bombdrop = digitalRead(Bomb_drop); // Read state of bomb drop signal
 // the below can have both wing fold and bomb drop codes incorporated within, but, the else if part i.e else if(Switch==0) , has to have only bomb dropping mechanism.
  // Add reset to the else if that basically has the flight ready config with pins locking the folding mechanism and potentially have LED's on outside of aircraft to determine these states.
  //while (bombdrop==1) {
  //  for (i=0;i<7;i++) {
  //  bombdrop = digitalRead(Bomb_drop); // Read state of bomb drop signal
  //  if(bombdrop == 1){
  //    Serial.println(servonum);
  //    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //      pwm.setPWM(servonum, 0, pulselen); //pick one of these, define SERVOMIN/MAX as the open or closed position for the bombs
  //    }
    

      //delay(500);
      //for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        //pwm.setPWM(servonum, 0, pulselen);
      //}
//
  //    delay(500);
    //}
   // else if(bombdrop ==0){
   //   servonum++;
   // //pins 1-6 on servo driver for bombs

   //wingfold
 
  while ((Switch==HIGH) && (Wing_read==HIGH)){  // If fail safe switch is on and wing read is high, we want the wing to stow.
    //if servo locked
     // unlock
     uint16_t LSpulselen = SERVOMIN //CALIBRATE
     uint16_t RSpulselen = SERVOMAX; //CALIBRATE
     while(limitLS==1){
        pwm.setPWM(8, 0, LSpulselen);
        limitLS = digitalRead(Open_LLS);
        Stow_Lpulselen=LSpulselen;
      }
     if (digitalRead(Open_LLS)==0) {
        pwm.setPWM(8, 0, 345);
      }
     delay(3000);
    while(limitRS==1) {
        pwm.setPWM(9, 0, RSpulselen);
        limitRS = digitalRead(Open_RLS);
        Stow_Rpulselen=RSpulselen;
        }
    if (digitalRead(Open_RLS)==0) {
            pwm.setPWM(9, 0, 345);
        }
      
      }
      
    }

    while (Switch==HIGH && Wing_read==LOW){ // While wing actuation is given a low signal, we want the wings to go into flight ready config and the servos to lock.
    //  if servo locked
      //  unlock
      uint16_t LFpulselen = Stow_Lpulselen; //Might need to change if we don't want to rely on the value that it was previously at
      uint16_t RFpulselen = Stow_Rpulselen; //Same Comment
      while(limitLF==LOW) {  // Left wing rolls back into flight ready config.
          pwm.setPWM(8, 0, LFpulselen);
          limitLF = digitalRead(Close_LLS);
          delay(100);
        }
      while(limitRF==1 && RFpulselen > SERVOMIN) {  // Right wing rolls back into flight ready config.
          pwm.setPWM(9, 0, RFpulselen);
          limitRF = digitalRead(Close_RLS);
          delay(100);
        }
      if (digitalRead(Close_RLS)==0) {
        pwm.setPWM(9, 0, 345);
      }

      if(limitLF==HIGH){   // Left servo locks when RLS Close limit switch is high
          pwm.setPWM(10, 0, LLockServoMax);
          delay(50);
          //might need to add a contingency if lockservomax is not well calibrated
        }
      if(limitRF==HIGH){   // Right servo locks when RLS Close limit switch is high
          pwm.setPWM(11, 0, RLockServoMax);
          delay(50);
        } 
      }
    }

    
  }


}




   
