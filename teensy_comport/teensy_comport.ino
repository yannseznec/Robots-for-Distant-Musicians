
#include "SPI.h"

const  int numAnalogs = 0;
const  int numDigitals = 0;
const int numDigitalOuts = 5;


  int newVal[numAnalogs];
  int currentVal[numAnalogs];

  int fromPd = 0;
  
  String analogInput[] = {
  "analog0 ", "analog1 ", "analog2 ", "analog3 ", "analog4 ", "analog5 ", "analog6 ", "analog7 ", "analog8 ", "analog9 ", "analog10 ", "analog11 ", "analog12 ",
};

  String digitalInput[] = {
  "digital0 ", "digital1 ", "digital2 ", "digital3 ", "digital4 ", "digital5 ", "digital6 ", "digital7 ", "digital8 ", "adigital9 ", "digital10 ", "digital11 ", "digital12 ",
};

  int analogPins[] = {
    14,15,16,17,18,19,20,21,22,23,24,25,26
  };
    int digitalPins[] = {
    2,3,4,5,6,7,8,9,10,11,12,13
  };
    int digitalOutputPins[] = {
      2,3,4,5,13,7,8,9,10,11,12
    };

  int digitalFromPd[] = {
    10,12,14,16,18,19,20,22,24,26
  };

void setup() {

  for (int i = 0; i < numAnalogs; i++) {
    pinMode(analogPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < numDigitals; i++) {
    pinMode(digitalPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < numDigitalOuts; i++) {
    pinMode(digitalOutputPins[i], OUTPUT);
  }
    
    Serial.begin(9600);
      while (!Serial) {
    ; 
  }
  
}

void loop() {

  for (int i = 0; i < numAnalogs; i++) {
    newVal[i] = analogRead(analogPins[i]);

    if (abs(newVal[i] - currentVal[i])>1) { 
    
    Serial.print(analogInput[i]);
    Serial.print(analogRead(analogPins[i]));
    Serial.print(" ");
    Serial.println(0);
    currentVal[i] = newVal[i];
    }
  }

for (int i = 0; i < numDigitals; i++) {

    Serial.print(digitalInput[i]);
    Serial.print(digitalRead(digitalPins[i]));
    Serial.print(" ");
    Serial.println(0);
}


  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    fromPd = Serial.read();
      for (int i = 0; i < numDigitalOuts; i++) {
        if (fromPd == digitalFromPd[i]) {
        digitalWrite(digitalOutputPins[i], HIGH);
        };
 
        if (fromPd == (digitalFromPd[i]+1)) {
        digitalWrite(digitalOutputPins[i], LOW);
        };
      }
    delay(5);
  }
}
