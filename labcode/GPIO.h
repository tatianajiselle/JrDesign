#ifndef GPIO_H
#define GPIO_H

class GPIO {
	private:
		int gpio; // Software gpio
		int value; // Value of gpio
		char direction[3]; // Direction of gpio
	public:
		GPIO();
		GPIO(int pin, int block);
		~GPIO();
		void setValue(int value);
		void setDirection(char direction[3]);
		int getValue();
		void getDirection();
};
#endif
