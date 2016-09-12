/*
	This is a library for global top, GPS Fox1 module, works on Galileo Gen2
*/
#ifndef GPS_FOX1_H
#define GPS_FOX1_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <SoftwareSerial.h>

// #ifndef
// #define SOFTWARESERIAL_H
// #endif

#define GPS_BAUDRATE 9600	//default baud rate
#define GPS_RX_PIN  //galileo UART Serial1, rx pin 0 on board
#define GPS_MSG_END 10 	//end of msg, <CR> <LF>
#define GPS_INFO_MAX 100
#define GPS_TITLE_LENGTH 6
#define GPS_INIT_VALUE -1
#define GPS_INIT_DIRECTION 'X'
#define GPS_RX 8
#define GPS_TX 9
#define GPS_TRY_TIMES 300

class GPS_FOX1{
public:
	void getGPGGA_GPRMC();
	GPS_FOX1();
	void begin(int baudrate = GPS_BAUDRATE);
	//time & date in UTC

	int readYear();
	int readMonth();
	int readDay();
	int readHour();
	int readMinute();
	int readSecond();
	double readLatitude();
	double readLongitude();
	double readAltitude();
	char readNS();
	char readWE();
	void readRMCraw(char *getrmc);
	void readGGAraw(char *getgga);

	//location
	
	//mean-sea-level
	
private:
	SoftwareSerial *_gps;
	char GPGGA_info[GPS_INFO_MAX];
	char GPRMC_info[GPS_INFO_MAX];
	char *GPGGA_NAME;
	char *GPRMC_NAME;
	int _year;
	int _month;
	int _day;
	int _hour;
	int _min;
	int _second;
	double _latitude;
	char _NS;
	double _longitude;
	char _WE;
	int _satelliteNum;
	double _altitude;
	boolean DEBUG_MODE;
	
	void parseGPSInfo();
	// void getGPRMC();
	double getDoubleNumber(const char *s);
	double getIntNumber(const char *s);
	unsigned char getComma(unsigned char num,const char *str);

};

#endif 
