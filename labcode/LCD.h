#ifndef LCD_H
#define LCD_H
#include "GPIO.h"
#include "I2CDevice.h"

#define I2C_BUS 2
#define SLAVE_ADDR 32

class LCD {
	private:
		char voltage[4];
		I2CDevice gpio_expander;
		GPIO rs;
		GPIO en;
	public:
		LCD();
		~LCD();
		void initializeDisplay();
		void clearDisplay();
		void sendByte(char byte, int rsValue);
		void newLine();
		void space();
		void sendString(char string[]);
		void getVoltage(int AINNum);
};
#endif
