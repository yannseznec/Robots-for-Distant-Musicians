# Robots-for-Distant-Musicians
A set of musically responsive robots that can be controlled by people around the world in real time over the internet.

Made as part of my residency at the MICA Game Lab in Baltimore, Maryland.

More information about the project as a whole here: http://gamelab.mica.edu/?nor-portfolio=robots

The code including in this repo is a Pure Data patch for analyzing incoming audio and converting it to MIDI, and Teensy/Arduino code for taking that MIDI and coverting it to PWM for controlling motors.

Each robot uses the following hardware:
- A smart phone for connecting to Zoom or Discord (or any other communication platform)
- The audio output from the phone is connected to the audio input of a Bela board. The Bela board is running the Pd patch in this repo. Either model of Bela would work: http://www.bela.io
- A Teensy LC microcontroller, connected to the Bela via USB, running the code included in this repo: https://www.pjrc.com/teensy/teensyLC.html
- A potentiometer connected to the Teensy to set the pitch detection sensitivity
- A button connected to the Teensy to change modes
- Powerboost 1000 power chip for motors: https://www.adafruit.com/product/2465
- Switch connected to the power chip
- Powerboost 500 Basic, connected to Powerboost 1000, for regulating power to Bela: https://www.adafruit.com/product/1903
- 2 DC motors: https://www.mouser.com/ProductDetail/Adafruit/2941/?qs=ivJcBTDythXHRFYmjoas8A%3D%3D
- motor controller chip: https://www.adafruit.com/product/2448
- LiPo Battery: https://www.adafruit.com/product/328
- Rear wheel: https://www.adafruit.com/product/2942

Wiring guide coming soon..
