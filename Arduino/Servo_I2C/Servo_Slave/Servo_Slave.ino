// Servo Slave

//Take in angle from master
//move servo to angle
//pass back current angle
//---------------------------------------------//

#include <Wire.h>
#include <Servo.h>

Servo my_servo; // create an instance of servo

//-----Static Variables-----//
#define ADDRESS 6           // Address needs to be different for each slave (1-255)
#define SERVO_PIN 9

//-----Global Variables-----//
uint8_t target_angle = 90;  //angle to move to
uint8_t current_angle = target_angle;

void setup() {
  Wire.begin(ADDRESS);        //set up I2C BUS (SLAVE(5))
  Wire.onReceive(get_data);   //run get_data function when master activates bus
  Wire.onRequest(send_data);  //run send_data when master requests
  
  my_servo.attach(SERVO_PIN); 
  my_servo.write(target_angle); //brings the servo to "home" at start

}

void loop() {
  if (current_angle < target_angle){  //incoment the angle up to target angle
    my_servo.write(current_angle++);
  }else if (current_angle > target_angle){ //incroment the angle down to target angle
    my_servo.write(current_angle--);
  }
  delay(10); //final code use time object NOT DELAY
  //error checking between each angle
}

void get_data(int packets){ //function for Wire.onReceive
  target_angle = Wire.read();
}
void send_data( ){   //function for Wire.onRequest
  Wire.write(current_angle);
}

