// Servo Master

//Controls Slave servo with I2C bus
//generats a random angle 0-180 
//pass angle to servo slave
//when slave finishes the motion repeat
//---------------------------------------------//

#include <Wire.h>

//-----Static Variables-----//
#define ELBOW 5

//-----Global Variables-----//


void setup() {
   Wire.begin();   // Sets up I2C BUS (MASTER)
}

void loop() {
  uint8_t angle = lowByte(random(180));  //create a random number 0 to 180 (8bits)
  uint8_t done = 255;
  
  Wire.beginTransmission(ELBOW);  //conect with ELBOW slave
  Wire.write(angle);              //send data to ELBOW
  Wire.endTransmission();         //end transmition

  do{ //check if the slave is done
  Wire.requestFrom(ELBOW, 1, true); //request 1 byte from slave
      done = Wire.read();           //save data to done
  delay(50); //final code use time object NOT DELAY
  }while (done != angle);           //when done = angle move on

}
