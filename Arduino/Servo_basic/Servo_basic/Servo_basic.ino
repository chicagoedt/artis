#include <Servo.h>

int position = 0;

Servo myservo; // Creating a Servo object

void setup() {

	myservo.attach(13); // Attaching pin 13 to myservo object
}

void servo_sweep(int pos, int pause){ // Sweeps to a position and exits after a delay;
	myservo.write(pos);
	delay(pause);
	return;
}


void loop() {

	servo_sweep(0,800);
	servo_sweep(180,800);

}


