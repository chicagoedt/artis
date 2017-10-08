// Servo Master

//Controls Slave servo with I2C bus
//generats a random angle 0-180 
//pass angle to servo slave
//when slave finishes the motion repeat
//---------------------------------------------//

#include <Wire.h>

//-----Static Variables-----//
#define ELBOW 5
#define WRIST 6

//-----Global Variables-----//
uint8_t elbow_angle = 90;
uint8_t elbow_done = elbow_angle;
uint8_t wrist_angle = 90;
uint8_t wrist_done = wrist_angle;

void setup() {
  Wire.begin();   // Sets up I2C BUS (MASTER)
}

void loop() {
  if(elbow_done == elbow_angle){ //check if elbow is done moving
    elbow_angle = lowByte(random(180));
    next_angle(elbow_angle, ELBOW); //send new angle
  }
  if(wrist_done == wrist_angle){ //check if wrist is done moving
    wrist_angle = lowByte(random(180));
    next_angle(wrist_angle, WRIST); //send new angle
  }
  
  //check current elbow position
  Wire.requestFrom(ELBOW, 1, true); //request 1 byte from slave
      elbow_done = Wire.read();     //save data to elbow_done

  //check current wrist position
  Wire.requestFrom(WRIST, 1, true); //request 1 byte from slave
      wrist_done = Wire.read();     //save data to wrist_done
}

void next_angle(uint8_t angle, int address){
  Wire.beginTransmission(address);  //conect to I2C
  Wire.write(angle);                //send data to adressed slave
  Wire.endTransmission();           //end transmition
}

