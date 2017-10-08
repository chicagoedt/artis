/*Note: Technically, the servo is only "writing" to angles 0 and 180,
But to get from 0 to 180, the servo has to hit all angles, hence it gives the illusion of
"writing" to all angles. Same idea goes for 180 to 0. 
*/

#include <Servo.h>

// using define for static variables will save big time on memory
// #define VeriableName value
#define SERVO_DELAY 3000
#define SERVO_PIN 9

//int position = 0;

Servo myservo; // Creating a Servo object

void setup() {

  myservo.attach(SERVO_PIN); // Attaching pin 9 to myservo object
}

void servo_sweep(int pos, int pause){ // Sweeps to a position and exits after a delay;
  myservo.write(pos);
  delay(pause);
  return;
}


void loop() {

  servo_sweep(0,SERVO_DELAY);
  servo_sweep(180,SERVO_DELAY);

}


