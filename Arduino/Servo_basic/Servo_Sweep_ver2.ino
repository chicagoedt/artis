/*Note: Technically, the servo is only "writing" to angles 0 and 180,
But to get from 0 to 180, the servo has to hit all angles, hence it gives the illusion of
"writing" to all angles. Same idea goes for 180 to 0. 
*/

#include <Servo.h>

// using define for stadic veriables will save big time on memory
// #define VeriableName value
#define ServoDelay 3000
#define ServoPin 9

int position = 0;

Servo myservo; // Creating a Servo object
//int servoPin = 9; // Servo Input Pin
//int servoDelay = 3000;  // Servo Sweep Delay

void setup() {

  myservo.attach(ServoPin); // Attaching pin 9 to myservo object
}

void servo_sweep(int pos, int pause){ // Sweeps to a position and exits after a delay;
  myservo.write(pos);
  delay(pause);
  return;
}


void loop() {

  servo_sweep(0,ServoDelay);
  servo_sweep(180,ServoDelay);

}


