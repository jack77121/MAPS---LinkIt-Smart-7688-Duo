#include "GPS_FOX1.h"
#include "Arduino.h"


GPS_FOX1::GPS_FOX1(){
	GPGGA_NAME = 	  "GPGGA";
	GPRMC_NAME = 	  "GPRMC";
	_year = 		  GPS_INIT_VALUE;
	_month = 		  GPS_INIT_VALUE;
	_day = 			  GPS_INIT_VALUE;
	_hour = 		  GPS_INIT_VALUE;
	_min = 			  GPS_INIT_VALUE;
	_second = 		  GPS_INIT_VALUE;
	_latitude = 	  GPS_INIT_VALUE;
	_NS = 			  GPS_INIT_DIRECTION;
	_longitude = 	  GPS_INIT_VALUE;
	_WE = 			  GPS_INIT_DIRECTION;
	_satelliteNum =   GPS_INIT_VALUE;
	_altitude = 	  GPS_INIT_VALUE;
	DEBUG_MODE = 	  true;
	_gps = 	  		  new SoftwareSerial(GPS_RX, GPS_TX);
}


void GPS_FOX1::begin(int baudrate){
  	_gps->begin(GPS_BAUDRATE);
}

int GPS_FOX1::readYear(){
	return _year;
}

int GPS_FOX1::readMonth(){
	return _month;
}

int GPS_FOX1::readDay(){
	return _day;
}

int GPS_FOX1::readHour(){
	return _hour;
}

int GPS_FOX1::readMinute(){
	return _min;
}

int GPS_FOX1::readSecond(){
	return _second;
}

double GPS_FOX1::readLatitude(){
	return _latitude;
}

double GPS_FOX1::readLongitude(){
	return _longitude;
}

double GPS_FOX1::readAltitude(){
	return _altitude;
}

char GPS_FOX1::readNS(){
	return _NS;
}

char GPS_FOX1::readWE(){
	return _WE;
}
void GPS_FOX1::readRMCraw(char *getrmc){
	int i;
	for(i = 0;i < GPS_INFO_MAX;i++){
		getrmc[i] = GPRMC_info[i];
	}
}
void GPS_FOX1::readGGAraw(char *getgga){
	int i;
	for(i = 0;i < GPS_INFO_MAX;i++){
		getgga[i] = GPGGA_info[i];
	}
}
void GPS_FOX1::getGPGGA_GPRMC(){
	_gps->listen();
	boolean getGPGGA = false;
	boolean getGPRMC = false;
	GPGGA_info[0] = '\0';
	GPRMC_info[0] = '\0';
	char temp[GPS_TITLE_LENGTH];
	int byteGPS = -1;	//initial value
	int searchCounter = 0;
	//keep matching GPGGA & GPRMC until we get them
	while(!getGPGGA || !getGPRMC){
		while(!_gps->available()){
			// wait for available data
		}
		byteGPS = _gps->read();
		// See if the port is empty yet
		if (byteGPS == -1) {
	    	// if we have't get GPS lock, then try it 300 times, you can change w/ GPS_TRY_TIMES
	    	delay(100); 
	    	searchCounter+=1;
	    	if(searchCounter >= GPS_TRY_TIMES){
	    		break;
	    	}
	   	} 
	   	//try match "$GPGGA" or "$GPRMC"
	   	else if(byteGPS == '$'){
	   		for(int i = 0;i < GPS_TITLE_LENGTH-1;i++){	
	   			while(!_gps->available()){
					// wait for available data
				}
	   			temp[i] = _gps->read();
	   		}
	   		temp[GPS_TITLE_LENGTH-1] = '\0';
	   		//if we got $GPGGA, then save the rest of the sentence
	   		if(strcmp(GPGGA_NAME, temp) == 0 && getGPGGA == false){	
	   			int i = 0;
	   			for(i = 0;byteGPS != GPS_MSG_END && i < GPS_INFO_MAX;i++){
	   				while(!_gps->available()){
						// wait for available data
					}
	   				byteGPS = _gps->read();
	   				GPGGA_info[i] = byteGPS;
	   			}
	   			//change get flag to "true", we found it, and put \0 at the end of the array
	   			if(i != GPS_INFO_MAX){
	   				getGPGGA = true;
	   				GPGGA_info[i] = '\0';
	   			}	
	   			else{
	   				//i shouldn't be GPS_INFO_MAX, rematch.
	   			}
	   		}
	   		//if we got $GPRMC, then save the rest of the sentence
	   		if(strcmp(GPRMC_NAME, temp) == 0 && getGPRMC == false){	
	   			int i = 0;
	   			for(i = 0;byteGPS != GPS_MSG_END && i < GPS_INFO_MAX;i++){
	   				while(!_gps->available()){
						// wait for available data
					}
	   				byteGPS = _gps->read();
	   				GPRMC_info[i] = byteGPS;
	   			}
	   			//change get flag to "true", we found it, and put \0 at the end of the array
	   			if(i != GPS_INFO_MAX){
	   				getGPRMC = true;
	   				GPRMC_info[i] = '\0';
	   			}	
	   			else{
	   				//i shouldn't be GPS_INFO_MAX, rematch.
	   			}			
	   		}
	   		else{
	   			//continue searching
	   		}
	   	}
	   	else{
	   		//continue searching
	   	}

	}
	parseGPSInfo();
	if(DEBUG_MODE == true){
		Serial.print("GPGGA Info : ");
		Serial.println(GPGGA_info);
		Serial.print("GPRMC Info : ");
		Serial.println(GPRMC_info);
		
		Serial.print("year:");
		Serial.println(_year);
		Serial.print("month:");
		Serial.println(_month);
		Serial.print("second:");
		Serial.println(_day);
		Serial.print("hr:");
		Serial.println(_hour);
		Serial.print("min:");
		Serial.println(_min);
		Serial.print("sec:");
		Serial.println(_second);
		Serial.print("latitude:");
		Serial.println(_latitude,4);
		Serial.print("NS:");
		Serial.println(_NS);
		Serial.print("longitude:");
		Serial.println(_longitude,3);
		Serial.print("WE:");
		Serial.println(_WE);
		Serial.print("Satellites:");
		Serial.println(_satelliteNum);
		Serial.print("height:");
		Serial.println(_altitude);
	}	
	
}

void GPS_FOX1::parseGPSInfo(){
	/*
	$GPGGA,080740.00,2502.44844,N,12136.89192,E,2,11,1.22,38.2,M,17.2,M,,0000*69
	$GPRMC,080817.00,A,2502.44840,N,12136.89408,E,0.203,,070916,,,D*78
	*/
	int temp;
	temp = getComma(7,GPGGA_info);
	_satelliteNum = getIntNumber(&GPGGA_info[temp]);
	if(_satelliteNum >=1){
		_hour = (GPGGA_info[1]-'0')*10 + (GPGGA_info[2]-'0');
		_min = (GPGGA_info[3]-'0')*10 + (GPGGA_info[4]-'0');
		_second = (GPGGA_info[5]-'0')*10 + (GPGGA_info[6]-'0');

		temp = getComma(2,GPGGA_info);
		_latitude = getDoubleNumber(&GPGGA_info[temp]);
		_latitude/=100;
		temp = getComma(3,GPGGA_info);
		_NS = GPGGA_info[temp];
		temp = getComma(4,GPGGA_info);
		_longitude = getDoubleNumber(&GPGGA_info[temp]);
		_longitude /= 100;
		temp = getComma(5,GPGGA_info);
		_WE = GPGGA_info[temp];
		
		temp = getComma(9,GPGGA_info);
		_altitude = getDoubleNumber(&GPGGA_info[temp]);

	}
	else{
		// use initial value
	}
	


	temp = getComma(2,GPRMC_info);
	if(GPRMC_info[temp] == 'A'){
		temp = getComma(9,GPRMC_info);
		_day = (GPRMC_info[temp + 0] - '0') * 10 + (GPRMC_info[temp + 1] - '0');
	    _month = (GPRMC_info[temp + 2] - '0') * 10 + (GPRMC_info[temp + 3] - '0');
	    _year = (GPRMC_info[temp + 4] - '0') * 10 + (GPRMC_info[temp + 5] - '0')+2000;
	}
	else{
		// use initial value
	}

	

}

double GPS_FOX1::getDoubleNumber(const char *s){
  char buf[15];
  unsigned char i;
  double rev;
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atof(buf);
  return rev; 
}


double GPS_FOX1::getIntNumber(const char *s){
  char buf[10];
  unsigned char i;
  double rev;
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atoi(buf);
  return rev; 
}

unsigned char GPS_FOX1::getComma(unsigned char num,const char *str){
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++){
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}
