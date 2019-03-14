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

  
  Switch = digitalRead(Or); // Reads status of safety switch
  LOpen = digitalRead(Open_LLS);
  LClose = digitalRead(Close_LLS);
  ROpen = digitalRead(Open_RLS);
  RClose = digitalRead(Close_RLS);
  Wing_read = digitalRead(Wing_fold); // Read state of wing fold signal
  Bomb_read = digitalRead(Bomb_drop); // Read state of bomb drop signal

  // the below can have both wing fold and bomb drop codes incorporated within, but, the else if part i.e else if(Switch==0) , has to have only bomb dropping mechanism.
  // Add reset to the else if that basically has the flight ready config with pins locking the folding mechanism and potentially have LED's on outside of aircraft to determine these states.
  while bombdrop==1
    for i
      drop
      i+1
    if i=6
      reset
      set bomb drop to 0
    #pins 1-6 on servo driver for bombs
  if((Switch==1) && (Wing_read==1)){  // If fail safe switch is on and if wing fold commd. is given //I think it makes sense for these to be loops
    if servo locked
      unlock
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
     
      while(LOpen==0){
        pwm.setPWM(8, 0, pulselen);
        delay(500)
        //this while loop will not exit, need to change LOpen at some point within it
      }
    }
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      while(ROpen==0){
        pwm.setPWM(9, 0, pulselen);
        delay(500)
        //this while loop will not exit, need to change ROpen at some point within it
      }
      
      }
      
    }

    else if(Switch==1 && Wing_read==0){ // If wing actuation is given a low signal //loops as above
      if servo locked
        unlock
      for (uint16_t pulselen = Open_Lpulselen ; pulselen > SERVOMIN; pulselen--) {  // Left wing rolls back into flight ready config.
        while(LClose==0){
          pwm.setPWM(8, 0, pulselen);
          delay(500)
        }
      }
      if(LClose==1){   // Right servo locks when RLS Close limit switch is high
        for (uint16_t pulselen = LockServoMin; pulselen < LockServoMax; pulselen++){
          pwm.setPWM(10, 0, pulselen);
          delay(50)
        } 
      }
      for (uint16_t pulselen = Open_Rpulselen ; pulselen > SERVOMIN; pulselen--) {  // Right wing rolls back into flight ready config.
        while(RClose==0){
          pwm.setPWM(9, 0, pulselen);
          delay(500)
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


}




   
