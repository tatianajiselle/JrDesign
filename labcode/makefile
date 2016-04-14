all: GPIO

GPIO: GPIO.o LCD.o I2CDevice.o
	g++ GPIO.o LCD.o I2CDevice.o -o gpio

GPIO.o: GPIO.cpp 
	g++ -D TEST -c GPIO.cpp GPIO.h 
	
LCD.o:	LCD.cpp LCD.h I2CDevice.o GPIO.o
	g++ -c LCD.cpp LCD.h I2CDevice.o GPIO.o

I2CDevice.o: I2CDevice.cpp I2CDevice.h
	g++ -c I2CDevice.cpp I2CDevice.h
	
clean:
	rm GPIO.o I2CDevice.o LCD.o