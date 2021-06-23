/* Teensy code for Robots for Distant Musicians
 this code listens for usbMIDI signal and converts it to the PWM signal necessary to control motors
v1.0
by Yann Seznec www.yannseznec.com
no copyright or anything, use however you want

remember to select MIDI as your USB Type in the Tools menu
works fine with a Teensy LC
things that are kind of dumb in this code:

this is written for use with an TB6612 motor controller, and uses a sparkfun library for that purpose
*/





#include <SparkFun_TB6612.h>
// This is the library for the TB6612 that contains the class Motor and all the
// functions

// Pins for all inputs, you can change these but keep in mind the PWM defines must be on PWM pins
#define AIN1 2 // non pwm pin
#define BIN1 3 // pwm pin
#define AIN2 4 //  pwm pin
#define BIN2 5 //  non pwm pin
#define PWMA 6 // pwm
#define PWMB 10 // pwm
#define STBY 9 // pwm

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int const numMotors = 3; 
// this is stupid, i'm actually only using 2 motors but i'm using 3 midi signals,
// one for each motor and one for the master start/stop 

int motorMIDI[] = {
  60,61,62
};
int motorOutput[] = {
  0,0,0
};

//midi channel
const int channel = 1;
int const numPins = 1; //  number of analog inputs (using this for setting threshold)
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {  
  14   // which analog pins to use
};
int analogPinsCC[] = {  
  50   // which CC to use
};

int const numDigPinsCC = 1; // number of digital pins to send CC (0 or 127) (using this to switch modes)
int currentDigCC[numDigPinsCC];
int digPinsCC[] = {
   15 // which digital pins to use for sending CC
};
int digitalPinsCC[] = {
  60
};

int readyLight = 72;
// use this to flash the onboard LED when MIDI is working


void setup() {
  pinMode(13,OUTPUT);
  usbMIDI.setHandleControlChange(OnControlChange);
  for (int i = 0; i < numPins; i++) {
    pinMode(analogPins[i], INPUT_PULLUP);
  }

      for (int i = 0; i < numDigPinsCC; i++) {
    pinMode(digPinsCC[i], INPUT_PULLUP);
  }
  Serial.begin(38400);

}

void loop() {



if (motorOutput[2] == -255) {
     motor1.brake();
     motor2.brake();
 Serial.println("STOP");
} else {
  motor1.drive(motorOutput[0]);
 Serial.println("LEFT ");
 Serial.print(motorOutput[0]);
motor2.drive(motorOutput[1]);
 Serial.println("RIGHT ");
 Serial.print(motorOutput[1]);

}


// digital pins sending CC (0 or 127)

  for (int i = 0; i < numDigPinsCC; i++) {
    if (digitalRead(digPinsCC[i]) == 1 && currentDigCC[i] == 0) {
      usbMIDI.sendControlChange(digitalPinsCC[i], 127, channel); 
      currentDigCC[i] = 1;
    }  
    if (digitalRead(digPinsCC[i]) == 0  && currentDigCC[i] == 1) {
      usbMIDI.sendControlChange(digitalPinsCC[i], 0, channel);
      currentDigCC[i] = 0;
    }  
  }

  // analog pins

  for (int i = 0; i < numPins; i++) {

    newVal[i] = analogRead(analogPins[i]);

    if (abs(newVal[i] - currentVal[i])>3) {
      usbMIDI.sendControlChange(analogPinsCC[i], newVal[i]>>3, channel); 
      currentVal[i] = newVal[i];
    }  
  }

  // i think if you remove these last two lines everything breaks and things are sad and people cry
  while (usbMIDI.read()); // read and discard any incoming MIDI messages
   delay(5); 
}

 

 void OnControlChange(byte channel, byte control, byte value) {


  for (int i = 0; i < numMotors; i++) {
    if (control == motorMIDI[i]) {
     motorOutput[i] = map(value, 0, 127, -255, 255);
  
    }
  }

  if (control == readyLight) {
    digitalWrite(13, value);
  }

     
}
