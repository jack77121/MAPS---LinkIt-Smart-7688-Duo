/* * * * * *
 * SENSE_TH: whether temperature/humidity sensor is used
 * 0: none
 * 1: Boshi BME280				(I2C)(Default onboard) 
 * * * * * */ 
#define SENSE_TH	1

/* * * * * *
 * SENSE_BAROMETER: whether barometer sensor is used.
 * 0: none
 * 1: Boshi BME280				(I2C)(Default onboard)
 * * * * * */ 
#define SENSE_BAROMETER	1

/* * * * * *
 * SENSE_PM: whether particulate matter sensor is used, SoftwareSerial; rx:11, tx:12
 * 0: none
 * 1: PMS3003					(G3 sensor)
 * 2: PMS5003					(G5 sensor)
 * * * * * */ 
#define SENSE_PM	2

/* * * * * *
 * OUTPUT_LED: whether LED is used
 * 0: none
 * 1: Grove - OLED 1.12"		(I2C)
 * * * * * */
#define OUTPUT_LED	0

/* * * * * *
 * DEV_TH: sense temperature & humidity beneath linkit smart duo; for future calibration usage
 * 0: none
 * 1: SHT25						(I2C)(Default onboard)(Default onboard)
 * * * * * */
#define DEV_TH	1

/* * * * * *
 * GPS_USE: use GPS module
 * 0: no GPS usage
 * 1: use GPS
 * * * * * */
#define GPS_USE	0

/* * * * * *
 * LORA_USE: use LoRa module
 * 0: no LoRa usage
 * 1: use Gemtek LoRa
 * * * * * */
#define LORA_USE	1
