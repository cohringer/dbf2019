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

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void setup() {

  pinMode(Open_LLS, INPUT); 
  pinMode(Close_LLS, INPUT); 
  pinMode(Open_RLS, INPUT); 
  pinMode(Close_RLS, INPUT); 
  pinMode(Bomb_drop, INPUT);
  pinMode(Wing_fold, INPUT);
  pinMode(Or, INPUT); 
  
  Serial.begin(9600);
  pwm.begin(); // Initializes driver read
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield()
}
void loop() {
// #Define limits as LeftStowed=LS Left(Flight)Ready=LR RightStow=RS Right(Flight)Ready=RR
// #limitR/LS=limitRight/LeftStowed, limitR/LF=limitRight/LeftFlight
// open is stowed configuration
  
  Switch = digitalRead(Or); // Reads status of safety switch
  limitLS= digitalRead(Open_LLS);
  limitLF = digitalRead(Close_LLS);
  limitRS = digitalRead(Open_RLS);
  limitRF = digitalRead(Close_RLS);
  Wing_read = digitalRead(Wing_fold); // Read state of wing fold signal
  bombdrop = digitalRead(Bomb_drop); // Read state of bomb drop signal

  // the below can have both wing fold and bomb drop codes incorporated within, but, the else if part i.e else if(Switch==0) , has to have only bomb dropping mechanism.
  // Add reset to the else if that basically has the flight ready config with pins locking the folding mechanism and potentially have LED's on outside of aircraft to determine these states.
  while bombdrop==1
    for (i=0;i<7;i++) {
    bombdrop = digitalRead(Bomb_drop); // Read state of bomb drop signal
    if(bombdrop == 1){
      Serial.println(servonum);
      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        pwm.setPWM(servonum, 0, pulselen); //pick one of these, define SERVOMIN/MAX as the open or closed position for the bombs
      }
    

      //delay(500);
      //for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        //pwm.setPWM(servonum, 0, pulselen);
      //}
//
  //    delay(500);
    }
    else if(bombdrop ==0){
      servonum++;
    //pins 1-6 on servo driver for bombs

    //wingfold
  if((Switch==1) && (Wing_read==1)){  // If fail safe switch is on and if wing fold commd. is given //I think it makes sense for these to be loops
    if servo locked
      unlock
     while(LOpen==0){ 
      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
        pwm.setPWM(8, 0, pulselen);
        delay(500)
        LOpen = digitalRead(Open_LLS);
      }
    }
    while(ROpen==0) {
      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
        pwm.setPWM(9, 0, pulselen);
        delay(500)
        ROpen = digitalRead(Open_RLS);
      }
      
      }
      
    }

    else if(Switch==1 && Wing_read==0){ // If wing actuation is given a low signal //loops as above
      if servo locked
        unlock
      while(LL==0) {  // Left wing rolls back into flight ready config.
        for (uint16_t pulselen = Open_Lpulselen ; pulselen > SERVOMIN; pulselen--){
          pwm.setPWM(8, 0, pulselen);
          delay(500)
          LClose = digitalRead(Close_LLS);
        }
      }
      if(LClose==1){   // Right servo locks when RLS Close limit switch is high
        for (uint16_t pulselen = LockServoMin; pulselen < LockServoMax; pulselen++){
          pwm.setPWM(10, 0, pulselen);
          delay(50)
          LClose = digitalRead(Close_LLS);
        } 
      }
      for (uint16_t pulselen = Open_Rpulselen ; pulselen > SERVOMIN; pulselen--) {  // Right wing rolls back into flight ready config.
        while(RClose==0){
          pwm.setPWM(9, 0, pulselen);
          delay(500)
          RClose = digitalRead(Close_RLS);
        }
      }
      if(RClose==1){   // Right servo locks when RLS Close limit switch is high
        for (uint16_t pulselen = LockServoMin; pulselen < LockServoMax; pulselen++){
          pwm.setPWM(11, 0, pulselen);
          delay(50)
          
        } 
      }
    }

    
  }
// Fix Akshay's convention to what I originally designated


}




   
