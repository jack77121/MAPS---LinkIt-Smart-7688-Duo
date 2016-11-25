//include library what we need
#include "setting.h"
#include <SoftwareSerial.h>
#define ERROR_VALUE -1

/* * * * * *
 * global variable
 * for sensing target, device temperature & humidity
 * * * * * */	
float g_dev_temperature = 0;
float g_dev_humidity = 0;

/* * * * * *
 * global variable
 * for sensing target, embient temperature, humidity & pressure
 * * * * * */
float g_env_temperature = 0;
float g_env_humidity = 0;
float g_env_baro = 0;

/* * * * * *
 * global variable
 * app id - 
 * 1:
 * 2:
 * 3:
 * 4:
 * 5: for using LinkIt Smart 7688 Duo
 * * * * * */
byte g_app_id = 5;

/* * * * * *
 * global variable
 * for sensing target, PM1, 2.5 & 10
 * * * * * */
int g_pm10 = ERROR_VALUE;	//PM1
int g_pm25 = ERROR_VALUE;	//PM2.5
int g_pm100 = ERROR_VALUE;	//PM10

/* * * * * *
 * global variable
 * GPS value: latitude, longitude & GPS fix #
 * value 15 means fake GPS, change this value to 0 if you using real GPS module
 * * * * * */
char g_GPS_LAT[] = "25.0111";  	// device's gps latitude, IIS NRL, Academia Sinica in DMS format, DD format: 25.041114, DMS format: 25.0228
char g_GPS_LON[] = "121.3256"; 	// device's gps longitude, IIS NRL, Academia Sinica in DMS format, DD format: 121.614444, DMS format: 121.3652
int g_fix_num = 15;				//15 means fake GPS

/* * * * * *
 * global variable
 * Smart 7688 Duo ID
 * * * * * */
String g_dev_id = "0007"; 

#if DEV_TH > 0
	#if DEV_TH == 1
		#include <SHT2x.h>	
	#endif
	float get_Dev_Temperature(){
		#if DEV_TH == 1
			return SHT2x.GetTemperature();
		#endif
	}
	float get_Dev_Humidity(){
		#if DEV_TH == 1
			return SHT2x.GetHumidity();
		#endif
	}
#endif

#if SENSE_BAROMETER > 0 or SENSE_TH > 0
	#if SENSE_BAROMETER == 1 or SENSE_TH == 1
		#include <Adafruit_BME280.h>	//our bme280, using i2c//our bme280, using i2c
		#define SEALEVELPRESSURE_HPA (1013.25)	//define sea level embient pressure//define sea level embient pressure
		Adafruit_BME280 bme;
	#endif
	void init_Sensor_Baro(){
		#if SENSE_BAROMETER == 1
			bme.begin();
		#endif
	}
	void init_Sensor_TH(){
		#if SENSE_TH == 1
			bme.begin();
		#endif	
	}
	float get_Env_Pressure(){
		#if SENSE_BAROMETER ==1
			return bme.readPressure() / 100.0F;
		#endif
	}
	float get_Env_Temperature(){
		#if SENSE_TH ==1
			return bme.readTemperature();
		#endif
	}
	float get_Env_Humidity(){
		#if SENSE_TH ==1
			return bme.readHumidity();
		#endif
	}
	

	
#endif


#if SENSE_PM > 0
	#if SENSE_PM == 1 or SENSE_PM == 2
		#define PM_SENSOR_RX 11
		#define PM_SENSOR_TX 12
		#define CHAR_PRELIM	0x42
		#define PM10_BYTE		10
	    #define PM25_BYTE		12
	    #define PM100_BYTE		14
	    SoftwareSerial mySerial(PM_SENSOR_RX, PM_SENSOR_TX); // RX, TX

		
	    
	#endif 
	#if SENSE_PM == 1
		//our g5 sensor, using software serial
		#define NUM_INCOME_BYTE 24	//fix data length 24 bytes
		#define NUM_DATA_BYTE	22
		#define CHECK_BYTE      22
	#endif
	#if SENSE_PM == 2
		//our g5 sensor, using software serial
		#define NUM_INCOME_BYTE 32	//fix data length 32 bytes
		#define NUM_DATA_BYTE   29
	    #define CHECK_BYTE		30

		#define pmsDataLen 32	//fix data length 32 bytes
		uint8_t serialBuf[pmsDataLen];
	    
	#endif
	void init_Sensor_PM(){
	    #if SENSE_PM == 1
	      // do something you want to do
	    #elif SENSE_PM == 2
	      // do something you want to do 
//			mySerial.begin(9600);
			pinMode(10, INPUT);
			pinMode(13, INPUT);	
	    #elif SENSE_PM == 3
	      // do something you want to do 
	    #elif SENSE_PM == 4
	      // do something you want to do 
	    #elif SENSE_PMPM == 5
	      // do something you want to do
	    #elif SENSE_PM == 6
	      // do something you want to do
	    #endif
	    return;
	  }
	void get_Env_PM(int *PM10 = 0, int *PM25 = 0, int *PM100 = 0){

//		g_pm10 = -1;	//PM1
//		g_pm25 = -1;	//PM2.5
//		g_pm100 = -1;//PM10
//		while(true){
//			mySerial.listen();
//		
//			uint8_t c = 0;
//			int idx = 0;
//			unsigned int calcsum = 0;
//			unsigned int exptsum;
//			
//			memset(serialBuf, 0, pmsDataLen);
//			
//			while (true) {
//				while (c != 0x42) {
//					while (!mySerial.available());
//					c = mySerial.read();
//				}
//				while (!mySerial.available());
//				c = mySerial.read();
//				if (c == 0x4d) {
//					// now we got a correct header)
//					serialBuf[idx++] = 0x42;
//					serialBuf[idx++] = 0x4d;
//					break;
//				}
//			}
//		
//			while (idx != pmsDataLen) {
//				while(!mySerial.available());
//				serialBuf[idx++] = mySerial.read();
//			}
//		
//			for(int i = 0; i < pmsDataLen-2; i++) {
//				calcsum += (unsigned int)serialBuf[i];
//		    }
//		    exptsum = ((unsigned int)serialBuf[30] << 8) + (unsigned int)serialBuf[31];
//			if(calcsum == exptsum){
//				g_pm10 = ( serialBuf[10] << 8 ) | serialBuf[11];
//				g_pm25 = ( serialBuf[12] << 8 ) | serialBuf[13];
//				g_pm100 = ( serialBuf[14] << 8 ) | serialBuf[15];
//				break;
//			}	
//		
//		}
		
		unsigned long timeout = millis();
	    int count = 0;
	    byte incomeByte[NUM_INCOME_BYTE];
	    boolean startcount = false;
	    byte data;
	    mySerial.begin(9600);
	    while (1){
	      if((millis() - timeout) > 3000) {    
	        Serial.println("[SENSOR-ERROR-TIMEOUT]");
	        break;
	      }
	      if(mySerial.available()){
	        data=mySerial.read();
	        if(data==CHAR_PRELIM && !startcount){
	          startcount = true;
	          count++;
	          incomeByte[0]=data;
	        } else if (startcount){
	          count++;
	          incomeByte[count-1]=data;
	          if(count>=NUM_INCOME_BYTE) {break;}
	        }
	      }
	    }
	    mySerial.end();
	    mySerial.flush();
	    unsigned int calcsum = 0; // BM
	    unsigned int exptsum;
	    for(int i = 0; i < 30; i++) {
	      calcsum += (unsigned int)incomeByte[i];
	    }
	  
	    exptsum = ((unsigned int)incomeByte[CHECK_BYTE] << 8) + (unsigned int)incomeByte[CHECK_BYTE+1];
	    if(calcsum == exptsum) {
	      *PM10 = ((unsigned int)incomeByte[PM10_BYTE] << 8) + (unsigned int)incomeByte[PM10_BYTE+1];
	      *PM25 = ((unsigned int)incomeByte[PM25_BYTE] << 8) + (unsigned int)incomeByte[PM25_BYTE+1];
	      *PM100 = ((unsigned int)incomeByte[PM100_BYTE] << 8) + (unsigned int)incomeByte[PM100_BYTE+1];
	    } else {
	      Serial.println("#[exception] PM2.5 Sensor CHECKSUM ERROR!");
	      *PM10 = ERROR_VALUE;
	      *PM25 = ERROR_VALUE;
	      *PM100 = ERROR_VALUE;
	    }	
	}
#endif
#if OUTPUT_LED > 0
	#if OUTPUT_LED == 1
		#include <SeeedOLED.h>
	#endif
	void init_OLED(){
		#if OUTPUT_LED == 1
			//SeeedOled setting
			SeeedOled.init();  //initialze SEEED OLED display
			DDRB|=0x21;        //digital pin 8, LED glow indicates Film properly Connected .
			PORTB |= 0x21;
			SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
			SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
			SeeedOled.setPageMode();           //Set addressing mode to Page Mode
			delay(100); 
		#endif
	}
	void ShowOLED(){
		#if OUTPUT_LED == 1
			SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("Temp: "); //Print the String
			SeeedOled.putFloat(g_dev_temperature); 
			SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("Humi: "); //Print the String
			SeeedOled.putFloat(g_dev_humidity);
			SeeedOled.setTextXY(2,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("=====BME====="); //Print the String
			SeeedOled.setTextXY(3,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("Temp: "); //Print the String
			SeeedOled.putFloat(g_env_temperature); 
			SeeedOled.setTextXY(4,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("Humi: "); //Print the String
			SeeedOled.putFloat(g_env_humidity);
			SeeedOled.setTextXY(5,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("Baro: "); //Print the String
			SeeedOled.putFloat(g_env_baro);
			SeeedOled.setTextXY(6,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("PM2.5: "); //Print the String
			SeeedOled.putNumber(g_pm25);
			SeeedOled.putString("ug/m3"); //Print the String
			SeeedOled.setTextXY(7,0);          //Set the cursor to Xth Page, Yth Column
			SeeedOled.putString("PM10: "); //Print the String
			SeeedOled.putNumber(g_pm100);
			SeeedOled.putString("ug/m3"); //Print the String
		#endif	
	}
#endif

#if GPS_USE > 0
	#if GPS_USE == 1
		#include <GPS_FOX1.h>
		GPS_FOX1 gps;
		#define GPS_RX 8
		#define GPS_TX 9
		SoftwareSerial gps(GPS_RX, GPS_TX); //RX, TX
	#endif
	void init_GPS(){
		#if GPS_USE == 1
			gps.begin(9600);	//GPS
		#endif
	}
	void get_GPS(){
		// this function is not completed yet.	
		
		#if GPS_USE == 1
			gps.getGPGGA_GPRMC()
		#endif
	}
	
#endif


#if LORA_USE > 0
	#if LORA_USE == 1
		//our LoRa module, using software serial
		#define LORA_RX 5
		#define LORA_TX 6
		#define LORA_DATA_BYTE_NUM 11
		SoftwareSerial lora(LORA_RX, LORA_TX);	// RX, TX
		byte lora_trans[LORA_DATA_BYTE_NUM];	//lora buffer
		
	#endif
	void init_LoRa(){
		#if LORA_USE == 1
//			lora.begin(9600);	//LoRa
		#endif		
	}
	void LoRaBitMap(byte &app_id, float &temperature, float &humidity, int &pm25, int &pm100, int &fix_num){
		#if LORA_USE == 1
			lora.begin(9600);
			word temperatureLora = (int)((temperature+20)*10);
			word humiditylora = (int)(humidity*10);
			word pm25lora = pm25;
			byte pm100Offset = pm100 - pm25;
			float GPS_LAT_f = (float)atof(g_GPS_LAT);
			float GPS_LON_f = (float)atof(g_GPS_LON);
		//	Serial.println("=====================");
		//	Serial.println(g_GPS_LAT);
		//	Serial.println(g_GPS_LON);
		//	Serial.println(GPS_LAT_f,4);
		//	Serial.println(GPS_LON_f,4);
			
			
			GPS_LAT_f += 90;
			GPS_LON_f += 180;
		//	Serial.println(GPS_LAT_f);
		//	Serial.println(GPS_LON_f);
			unsigned long GPS_LAT_i = GPS_LAT_f*10000;
			unsigned long GPS_LON_i = GPS_LON_f*10000;	
		//	Serial.println(GPS_LAT_i);
		//	Serial.println(GPS_LON_i);
			
			byte lat_D = (int) GPS_LAT_f;
			float temp_lat_M = (GPS_LAT_f - lat_D)*100;
			byte lat_M = (int) temp_lat_M;
			byte lat_S = GPS_LAT_i%100;
			
			
			word lon_D = (int) GPS_LON_f;
			float temp_lon_M = (GPS_LON_f - lon_D)*100;
			byte lon_M = (int) temp_lon_M;
			byte lon_S = GPS_LON_i%100;
			
			byte gps_fix = fix_num;
		
		
			
			lora_trans[0] = (app_id << 4) | (temperatureLora >> 6);	
			lora_trans[1] = (temperatureLora << 2) | (humiditylora >> 8);
			lora_trans[2] = humiditylora;
		
		//	Serial.print(lora_trans[0],HEX);
		//	Serial.print("\t");
		//	Serial.print(lora_trans[1],HEX);
		//	Serial.print("\t");
		//	Serial.print(lora_trans[2],HEX);
		//	Serial.print("\t");
			// END FOR THE APP_ID, TEMPERATURE AND HUMIDITY
		
			
		
			lora_trans[3] =  pm25lora >> 3;
			lora_trans[4] = (pm25lora << 5)|(pm100Offset >> 3);
			
			if(lora_trans[3] < 16){
		//		Serial.print('0');
			}
		//	Serial.print(lora_trans[3],HEX);
		//	Serial.print("\t");
			if(lora_trans[4] < 16){
		//		Serial.print('0');
			}
		//	Serial.print(lora_trans[4],HEX);
		//	Serial.print("\t");
			//END FOR PM2.5 AND PM10	
			
			lora_trans[5] = (pm100Offset <<5) | (lat_D >> 3);
			lora_trans[6] = (lat_D << 5) | (lat_M >> 1);
			lora_trans[7] = (lat_M << 7) | (lat_S << 1) | (lon_D >> 8);
			lora_trans[8] = (byte)lon_D;
			if(lora_trans[5] < 16){
		//		Serial.print('0');
			}
		//	Serial.print(lora_trans[5],HEX);
		//	Serial.print("\t");
		//	Serial.print(lora_trans[6],HEX);
		//	Serial.print("\t");
		//	Serial.print(lora_trans[7],HEX);
		//	Serial.print("\t");
		//	Serial.print(lora_trans[8],HEX);
		//	Serial.print("\t");
		
			lora_trans[9] = (lon_M << 2) | (lon_S >> 4);
			lora_trans[10] = (lon_S << 4) | gps_fix;
		
		//	Serial.print(lora_trans[9],HEX);
		//	Serial.print("\t");
		//	Serial.println(lora_trans[10],HEX);
		
			char buff[33];
			
			sprintf(buff, "AT+DTX=22,%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\r\n", lora_trans[0], lora_trans[1], \
			lora_trans[2], lora_trans[3], lora_trans[4], lora_trans[5], lora_trans[6], lora_trans[7], lora_trans[8],  \
			lora_trans[9], lora_trans[10]);
			Serial.println(buff);
			
			lora.print(buff);
			lora.end();
			lora.flush();
		//	Serial1.write(buff,33);
		#endif
	}
	
#endif






void setup()
{	
	
	Serial.begin(9600);	//debug serial
	Serial1.begin(57600);	//connect to MT7688

	#if SENSE_TH > 0
		init_Sensor_TH();
	#endif
	
	#if SENSE_BAROMETER > 0
		init_Sensor_Baro();		
	#endif
	
	#if SENSE_PM > 0
		init_Sensor_PM();
		 
	#endif
	
	#if LORA_USE > 0
		init_LoRa();
	#endif

	#if GPS_USE > 0
		init_GPS();
	#endif
	
	#if OUTPUT_LED > 0
		init_OLED();
	#endif
}

void loop()
{ 	
	unsigned long time;
	time = millis();
	Serial.println(time);
	//get sensor value

	#if DEV_TH > 0
		g_dev_temperature = get_Dev_Temperature();
		g_dev_humidity = get_Dev_Humidity();
	#endif

	#if SENSE_TH > 0
		g_env_temperature = get_Env_Temperature();
		g_env_humidity = get_Env_Humidity();
	#endif

	#if SENSE_BAROMETER > 0
		g_env_baro = get_Env_Pressure();
	#endif

	#if SENSE_PM > 0
		get_Env_PM(&g_pm10, &g_pm25, &g_pm100);
	#endif
	#if GPS_USE > 0
		get_GPS(g_GPS_LAT, g_GPS_LON, &g_fix_num);
	#endif

	#if OUTPUT_LED == 1
		ShowOLED();
	#endif

	#if LORA_USE == 1
		LoRaBitMap(g_app_id, g_env_temperature, g_env_humidity, g_pm25, g_pm100, g_fix_num);
	#endif
	
	
	SerialMonitor();

	GetDataToMT7688();
	delay(60650);
}




void SerialMonitor(){
	Serial.print("BME Temperature:\t");
	Serial.println(g_env_temperature);

	Serial.print("BME Humidity:\t\t");
	Serial.println(g_env_humidity);

	Serial.print("BME Barometer:\t\t");
	Serial.println(g_env_baro);

	Serial.print("SHT25 Temperature:\t");
	Serial.println(g_dev_temperature);

	Serial.print("SHT25 Humidity:\t\t");
	Serial.println(g_dev_humidity);

	Serial.print("G5 PM2.5:\t\t");
	Serial.println(g_pm25);

	Serial.print("G5 PM10:\t\t");
	Serial.println(g_pm100);
}
	
void GetDataToMT7688(){
	String temperature_str = String(g_env_temperature, 2);
	String humidity_str = String(g_env_humidity, 2);
	String baro_str = String(g_env_baro, 2);
	String pm10_str = String(g_pm10);
	String pm25_str = String(g_pm25);
	String pm100_str = String(g_pm100);
	String dev_temperature_str = String(g_dev_temperature, 2);
	String dev_humidity_str = String(g_dev_humidity, 2);
	String data_str = String(g_dev_id + "|" + temperature_str + "|" + humidity_str + "|" + baro_str + "|" + pm10_str + "|" + pm25_str + "|" + pm100_str + "|" + dev_temperature_str + "|" + dev_humidity_str);
	Serial.println("My string to MT7688:");
	Serial.println(data_str);
	Serial1.print(data_str);
}
