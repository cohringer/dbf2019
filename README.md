# dbf2019

#servoshield
https://learn.adafruit.com/adafruit-16-channel-pwm-slash-servo-shield/overview
https://learn.adafruit.com/16-channel-pwm-servo-driver/using-the-adafruit-library
Servo min/max built into the library
https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf
Pinout for our Arduino

# Tasking from Nick
Read PWM signal into code

'pulsein' in loop

2 subloops for bomb drop and wing fold

Bomb: PWM high
drop index i
i+1

if i=6 reset

pin 1-6 on servo driver for bombs

Wing Fold:

loop until high

Unlock locking servo (servo driver pin 10/11 LR)
pause
Actuate wing fold motor (servo driver pin 8/9 LR)
digital input from limit switch (2-5 on Arduino)
stop folding
Signal low
fold
limit switch
stop folding
lock
look for bomb drop