
/*
Artis master controler interface. 
University of Illinois at Chicago EDT
by: David Dieken (673533525)
24_Jan.2018
*/

#include "Wire.h"
//__________________________Functions__________________________________________
uint8_t analogToAngle(int pinNumber){
  int analogIn = analogRead(pinNumber); 
  float angle = (float) (analogIn/1023) * 180;
  return ((uint8_t)angle);
}
//___________________________Artis motor class__________________________________
class Motor{
  public:
    Motor(int address, int analogPin, uint8_t angleMin, uint8_t angleMax);
    void initalise();
    bool updateAngle(); //changes the tartget angle and send to motor
    void changeMin(uint8_t newMin); //changes the minimum angle
    void changeMax(uint8_t newMax); //changes the maximim angle
  private:
    int _address;
    int _analogPin;
    uint8_t _targetAngle;
    uint8_t _angleMin;
    uint8_t _angleMax;
};
Motor::Motor(int address, int analogPin, uint8_t angleMin, uint8_t angleMax){ 
	// prevent min > max  logic error
	if (angleMin > angleMax){
		angleMin = angleMax - 1;
	}

	// prevent unexpected value for max
	if ((angleMax < 180)and(angleMax > 0)){ //only save if 0<X<180
		_angleMax = angleMax;
	}else{
		_angleMax = 180;
	}
	// prevent unexpected value for min
 	if ((angleMin < 180)and(angleMin > 0)){ //only save if 0<X<180
	_angleMin = angleMin;
	}else{
	_angleMin = 0;
	}
	_analogPin = analogPin;
	_address = address;
}
void Motor::initalise(){ 
	Wire.beginTransmission(_address);  //conect to I2C
    Wire.write(_angleMin);		//send slave min angle
    Wire.write(_angleMax);      //send slave max angle 
    Wire.endTransmission();          //end transmition
}

bool Motor::updateAngle(){
	uint8_t target = analogToAngle(_analogPin);
	if ((target > _angleMin)and(target < _angleMax)){
		_targetAngle = target;
	}
    Wire.beginTransmission(_address);  //conect to I2C
    Wire.write(_targetAngle);      //send data to adressed slave 
    Wire.endTransmission();          //end transmition

    //chek to make sure the data was sent (TRUE or FALSE)

    return(true);
}
void Motor::changeMin(uint8_t newMin){ //used for adjusting min values for object avoidence
	if ((newMin < _angleMax)and(newMin > 0)){
	_angleMin = newMin;
	}
}
void Motor::changeMax(uint8_t newMax){ //used for adjusting max values for object avoidence
	if ((newMax > _angleMin)and(newMax < 180)){
		_angleMax = newMax;
	}
}

//_________________________________end__________________________________________

//____________________static veriables__________________________________________
/* Static veriable section is used to define ARTIS joint addresses and 
the analong refference to pin 
*/
#define UPDATE_INTERVAL 1000//time between updates in microseconds (1000 = 1 milli)
// Example:
// elbow (analog 0) (address 1)
#define ELBOW_IN 0
#define ELBOW_ADDRESS 1
#define ELBOW_LED 0 // used for debuging

//_________________________________end__________________________________________
//____________________Assign values to motors___________________________________
// Create the motor objects here

//Example:
Motor elbow (ELBOW_ADDRESS, ELBOW_IN, 0, 127);

//_________________________________end__________________________________________

unsigned long previousMicros = 0;
unsigned long currentMicros = 0;
int step = 0;

void setup() {
	Wire.begin();
	elbow.initalise();//initalise the min and max to the slave
}
void loop() {
	currentMicros = micros();
	if ((currentMicros - previousMicros) > UPDATE_INTERVAL){ //state mechine for timing control
		switch (step){
			case 0:
				//light LED when sending information
				digitalWrite(ELBOW_LED, HIGH);
				if (elbow.updateAngle()){ //send new target angle
					digitalWrite(ELBOW_LED, LOW); //turn off led if sucsesfull
				}
				previousMicros = currentMicros;
				step++;
			break;
			default:
				step = 0;
		}
	}
}
