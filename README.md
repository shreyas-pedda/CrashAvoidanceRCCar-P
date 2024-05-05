# CrashAvoidanceRCCar
Modified RC Car that has safety features and self-driving capabilities.

Current goals 
  1) Get the remote control to work simulteneously with the ESP32 program commands. --> Replaced with a joystick connected to another ESP32. \
    1.1) RC Car should take input from joystick and drive around, but if an obstacle is detected it stops the car and doesn't allow the joystick to move the car UNTIL the user lets go of the joystick fully. Then the code will start accepting the joystick analogReadings again.
  2) Use PWM to reduce speed of the car when we do self-driving commands --- (limit top speed lower in general) \
     2.1) Base the PWM duty cycle off the joystick input values, this allows us to control the speed turn angle using the joystick
  3) Connect ultrasound sensors to the car and get it to stop when an obstacle is in front of it \
     3.1) Figure out method to connect various ultrasound sensors to the ESP32 board
  4) Create proper body for the actual physical car, and make sure it is structurally sound and capable of withstanding collisions as that will be likely occuring often \
  5) Make the vehicle function somewhat like a rover and add a camera which can send video feed back to our laptop.

