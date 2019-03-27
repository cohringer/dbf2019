#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#define LockServoMin 130
#define LockServoMax 600
#define SERVOMIN  0
#define SERVOMAX  4096
#define BOMB_DROP_HIGH_THRESH 1700
#define BOMB_DROP_LOW_THRESH 1100
#define WING_FOLD_HIGH_THRESH 1700
#define WING_FOLD_LOW_THRESH 1100

// Instantiate global pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Constant variables
const int Open_LLS  = 2;   // LLS = Left Limit Switch, open indicates that it hits this limit switch when the wing is stowed
const int Close_LLS = 3;   // Close indicates that when it hits this limit switch, the wing is in its flight ready config
const int Open_RLS  = 4;   // Right side open 
const int Close_RLS = 5;   // Right side close 
const int Wing_fold = 6;   // Input to see if the wing should be folded
const int bombdrop  = 7;   // Input to see if a bomb should be dropped
const int Or        = 8;   // Switch that sets wing folding ability on or off
const int bombLED   = 12;  // LED when dropping bombs

// Global variables
int pulselen_R_Close = 430; 
int pulselen_R_Open = 200;
int pulselen_L_Close = 300;
int pulselen_L_Open = 460;
int LOpen = 1;
int LClose = 1;
int ROpen = 1;
int RClose = 1;
int Wing_read = 0;
int LLockServoMax = 335;
int RLockServoMax = 325;
int bombVal;
int wingVal;
int bombInc = 1;
int j = 1;
int k = 1;
int pass = 1;
int toggle = 0;

void setup() {
  Serial.begin(9600); 
 
  // Initial settings for pwm object
  pwm.begin();         // Initializes driver read
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // Pin setup
  pinMode(Open_LLS, INPUT); 
  pinMode(Close_LLS, INPUT); 
  pinMode(Open_RLS, INPUT); 
  pinMode(Close_RLS, INPUT); 
  pinMode(Wing_fold, INPUT);
  pinMode(bombdrop, INPUT);
  //pinMode(Or, INPUT); 

  // Setup servos
  setupBombServos();
  
  delay(1000);
}

void loop() {
  
  wingVal = pulseIn(Wing_fold, HIGH);
  bombVal = pulseIn(bombdrop, HIGH);

  if (bombVal > BOMB_DROP_HIGH_THRESH) {
    delay(2000);
    bombVal = pulseIn(bombdrop, HIGH);
    if (bombVal > BOMB_DROP_HIGH_THRESH) {
      // Enter bomb dropping state
      digitalWrite(bombLED, HIGH);
      dropBombs();  // Will block
      digitalWrite(bombLED, LOW);
      delay(2000);
      setupBombServos();  // Reset servos
    }
  } 

  if (wingVal < WING_FOLD_LOW_THRESH && toggle == 0) {
    // Go to flight configuration/state when command recved
    foldWingToFlight();
  }

  if (wingVal > WING_FOLD_HIGH_THRESH && toggle == 1) {
    // Go to stowed configuration/state when command recved
    foldWingToStowed(); 
  }

  delay(1000);
  
}

/*
 * Wings fold down and servos lock
 */
void foldWingToFlight(void) {
  while (digitalRead(Close_RLS) == 1) {
     pwm.setPWM(9, 0, pulselen_R_Close);
     RClose = digitalRead(Close_RLS);
     delay(100);
   }
   if (digitalRead(Close_RLS) == 0) {
     pwm.setPWM(9, 0, 345);
     delay(1000);
     for (uint16_t pulselen = 320; pulselen < 331; pulselen++) {
       pwm.setPWM(11, 0, pulselen);
     }
   }
   delay(1000);

   while (digitalRead(Close_LLS) == 1) {
     pwm.setPWM(8, 0, pulselen_L_Close);
     LClose = digitalRead(Close_LLS);
     delay(100);
   }
   if (digitalRead(Close_LLS) == 0) {
     pwm.setPWM(8, 0, 345);
     delay(1000);
     for (uint16_t pulselen = 320; pulselen < 336; pulselen++) {
       pwm.setPWM(10, 0, pulselen);
     }
   }

   toggle = 1;
}


/*
 * Drop 6 bombs. Leaves function when button to drop a bomb is hit one more
 * time after all bombs have been dropped (signals plane has landed)
 */
void dropBombs(void) {
  // You are now committed to bomb dropping sequence
  pass = 1;

  // Read data
  while (bombInc < 7) {  
    digitalWrite(bombLED, HIGH);
    
    delay(2000);
    bombVal = pulseIn(bombdrop, HIGH);

    if(bombVal > 1700 && pass == 1) {
      for (uint16_t pulselen = 140; pulselen < 417; pulselen++) {
        pwm.setPWM(bombInc, 0, pulselen);
      }
      j++;
      pass = 0;
      delay(1000);
    }  
    delay(500);
    bombVal = pulseIn(bombdrop, HIGH);

    if(pass == 0 && bombVal < BOMB_DROP_LOW_THRESH) {
      delay(2000);
      bombInc++;
      pass = 1;
    }
  }
  
  // Only exit bomb dropping state when commanded 
  // Check ******** NEED TO CHECK
  bool blocking = true;
  while (blocking) {
    if (bombVal > BOMB_DROP_HIGH_THRESH) {
      delay(2000);
      bombVal = pulseIn(bombdrop, HIGH);
      if (bombVal > BOMB_DROP_HIGH_THRESH) {
        blocking = false;
      }
    } 
  }
  
}

/*
 * Unlock locking servos and fold wings up
 */
void foldWingToStowed(void) {
  for (uint16_t pulselen = 331; pulselen > 280; pulselen--) {
    pwm.setPWM(11, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = 335; pulselen > 280; pulselen--) {
    pwm.setPWM(10, 0, pulselen);
  }
  
  while (digitalRead(Open_RLS) == 1) {
    pwm.setPWM(9, 0, pulselen_R_Open);
    ROpen = digitalRead(Open_RLS);
  }
  
  if (digitalRead(Open_RLS) == 0) {
    pwm.setPWM(9, 0, 345);
  }

  delay(1000);

  while (digitalRead(Open_LLS) == 1) {
    pwm.setPWM(8, 0, pulselen_L_Open);
    LOpen = digitalRead(Open_LLS);
  }

  if (digitalRead(Open_LLS) == 0) {
    pwm.setPWM(8, 0, 345);
  }

  toggle = 0;
}

void setupBombServos(void) {
  k = 1;
  while (k < 7){
    for (uint16_t pulselen = 180; pulselen >140; pulselen--) {
      pwm.setPWM(k, 0, pulselen);
    }
    k++;
  }
}


