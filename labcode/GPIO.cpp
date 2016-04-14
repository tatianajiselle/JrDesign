#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include "GPIO.h"
#include "I2CDevice.h"
#include "LCD.h"

GPIO::GPIO(){}

GPIO::GPIO(int block, int pin) { 
	this->value = 0;
	
	// Convert pin number to console number 
	gpio = block * 32 + pin;
	
	// Open and write to file
	std::fstream file("/sys/class/gpio/export",std::ofstream::out);
	if(!file.good()){
		std::cout << "GPIO::GPIO(int,int): File did not open" << std::endl;
		exit(1);
	}
	file << this->gpio << std::endl;
	file.close();
}

GPIO::~GPIO() {}

void GPIO::setValue(int value){
	char* fileString;

	// Store value
	this->value = value;
	
	// Prepare file path
	sprintf(fileString, "/sys/class/gpio/gpio%d/value", gpio);

	// Open file
	std::fstream file(fileString,std::ofstream::out);
	if(!file.good()){
		std::cout << "GPIO::setValue(int): File did not open" << std::endl;
		exit(1);
	}
	file << this->value << std::endl;
	file.close();
}

void GPIO::setDirection(char direction[3]){ 
	char* fileString;

	strcpy(this->direction,direction);

	// Prepare file path
	sprintf(fileString, "/sys/class/gpio/gpio%d/direction", gpio);
	
	// Open file
	std::fstream file(fileString,std::ofstream::out);
	if(!file.good()){
	  	std::cout << "GPIO::setDirection(char): File did not open" << std::endl;
	  	exit(1);
	}
	
	file << this->direction << std::endl;
	file.close();
}

int GPIO::getValue(){ 
	char* fileString, val;
	
	// Prepare file path
	sprintf(fileString, "/sys/class/gpio/gpio%d/value", gpio);
	
	// Open file
	std::fstream file(fileString,std::ifstream::in);
	if(!file.good()){
		std::cout << "GPIO::getValue(): File did not open" << std::endl;
	  	exit(1);
	}
	
	file >> val;
	this->value = val - '0';
	file.close();
	
	return this->value;
}

void GPIO::getDirection(){ 
	char* fileString;

	// Prepare file path
	sprintf(fileString, "/sys/class/gpio/gpio%d/direction", gpio);

	// Open file
	std::fstream file(fileString,std::ifstream::in);
	if(!file.good()){
		std::cout << "GPIO::getDirection(): File did not open" << std::endl;
	  	exit(1);
	}
	
	file >> this->direction;
	file.close();
	
	return;
}

#ifdef TEST
int main(int argc, char *argv){
	//GPIO TGPIO = GPIO(,);
	// get voltage from thermister voa gpio pin
}
#endif 
