#include <iostream>
#include "LCD.h"
#include <unistd.h>
#include <cstdlib>
#include <fstream>

#define REGADDR 0x12
#define ENTRYMODESET 0x06
#define DISPLAYCONTROL 0x0E
#define FUNCTIONSET 0x38

LCD::LCD(): gpio_expander(2, 32)
{
	// Initilize i2C device 
	//this->gpio_expander(2, 32);
	// Initialize GPIO
	this->rs = GPIO(2, 9);
	rs.setValue(0);
	rs.setDirection("out");
	this->en = GPIO(2, 8);
	en.setValue(0);
	en.setDirection("out");
	// Initialiaze display 
	initializeDisplay();
}

LCD::~LCD()
{

}

void LCD::initializeDisplay()
{
	unsigned int delay = 400; //400us
	
	// Set GPIOA to all outputs
	
	gpio_expander.writeRegister(0x00, 0x00);
	
	// Start sending initialization bytes to display
	
	clearDisplay();
	usleep(delay);
	
	gpio_expander.writeRegister(REGADDR, FUNCTIONSET);
	usleep(delay);
	en.setValue(1);
	en.setValue(0);
	usleep(delay);
	
	gpio_expander.writeRegister(REGADDR, DISPLAYCONTROL);
	usleep(delay);
	
	en.setValue(1);
	en.setValue(0);
	usleep(delay);
	
	gpio_expander.writeRegister(REGADDR, ENTRYMODESET);
	usleep(delay);
	
	en.setValue(1);
	en.setValue(0);
	usleep(delay);
	
	clearDisplay();
	usleep(delay);
}

void LCD::clearDisplay()
{
	unsigned int delay = 400;
	rs.setValue(0);
	gpio_expander.writeRegister(REGADDR, 0x01);
	usleep(delay);
	en.setValue(1);
	en.setValue(0);
}

void LCD::sendByte(char byte, int rsValue)
{
	unsigned int delay = 400; //400us
	rs.setValue(rsValue);
	gpio_expander.writeRegister(REGADDR, byte);
	en.setValue(1);
	en.setValue(0);
	usleep(delay);
}

void LCD::newLine()
{
	rs.setValue(0);
	en.setValue(0);
	gpio_expander.writeRegister(REGADDR, 0xC0);
	en.setValue(1);
	en.setValue(0);

}

void LCD::space()
{
	rs.setValue(1);
	en.setValue(0);
	gpio_expander.writeRegister(REGADDR, 0x20);
	en.setValue(1);
	en.setValue(0);
}

void LCD::sendString(char string[])
{
	unsigned int delay = 400;
	
	for(int i = 0; string[i] != '\0'; i++){
		rs.setValue(1);
		gpio_expander.writeRegister(REGADDR,string[i]);
		en.setValue(1);
		en.setValue(0);
		usleep(delay);
	}

}
void LCD::getVoltage(int AINNum)
{
	char fileString[50];
	// Prepare file path
	sprintf(fileString, "/sys/devices/ocp.3/helper.12/AIN%d", AINNum);
	
	// Open file
	std::fstream file(fileString,std::ifstream::in);
	
	if(!file.good()) {
		std::cout << "LCD::getVoltage(): File did not open" << std::endl;
	  	exit(1);
	}
	
	file >> this->voltage;
	file.close();
	
	return;
}