#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


// our servo # counter
uint8_t servonum = 0;
const int Open_LLS = 2; //LLS stands for left limit switch & Open indicates that when it hits this limit switch the wing is folded
const int Close_LLS = 3;
const int Open_RLS = 4;
const int Close_RLS = 5; //RLS stands for right limit switch and Close indicates that when it hits this limit switch the wing is in its flight ready config.
const int Bomb_drop = 6;
const int Wing_fold = 7;
const int Or = 8; // Switch that sets wing folding ability on or off
int pulselen = 2100;

#define LockServoMin 130
#define LockServoMax 600

#define SERVOMIN  0
#define SERVOMAX  4096

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

 // Serial.print(Wing_read)
 // Serial.print(Bomb_read)
 pwm.setPWM(8, 0, pulselen)
}
