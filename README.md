# Micro Air Pollution Sensing
##Use LinkIt Smart 7688 Duo

![Image of appearance](https://github.com/jack77121/MAPS---LinkIt-Smart-7688-Duo/blob/master/MAPS_7688duo_RP1135C.png)

MAPS v5.1 appearance

## Story
**M**icro **A**ir **P**ollution **S**ensing - MAPS

Air pollution is a hot topic in recent years, especially - **Particulate Matter**. Traditional sensing method, we can only depend on professional sensors/devices, with large volume, heave weight and insanity price.
Thanks to the technology, now we could build our own air pollution sensing station, with micro volume, light weight and the price is affordable :). With MAPS, you can sense air pollution any where, any time by yourself, you can also give it a battery module to increase its mobility!

For more air pollution sensing project, you can visit [LASS facebook](https://www.facebook.com/groups/1607718702812067/) and [LASS github](https://github.com/LinkItONEDevGroup/LASS), we are makers who sense anything in our environment!

## Hardware & Sensors
Module     			 |	Description
---------------------|--------------
LinkIt Smart 7688 Duo|Mainboard
G5 (pms5003)			 |Particalute matter (PM)
BME280       			 |Temperature, humidity & Air pressure
SHT25					 |Temperature & humidity (optional)

p.s SHT25 is for device temperature, humidity monitoring and future calibration usage, MAPS is be still full functional without it.

## PCB layout & dimensions
![Image of pcb layout](https://github.com/jack77121/MAPS---LinkIt-Smart-7688-Duo/blob/master/PCB_layout.png)

(unit: mm)

##Installing
###Instrution
MAPS use both MT7688AN (MPU) and ATmega32U4 (MCU) onboard to complete its jobs. They communicate through UART (in this project). 

ATmega32U4 is reponsible for sensors data collection.( and data boardcasting through LPWAN, if you use LoRa.)

There is an OpenWrt Linux OS running on 7688 duo, so MT7688AN is capable for multiple jobs, its main task is data publishing through MQTT to the backend server, others like time sync, program update OTA and user preference setting (wifi, manual GPS) are its routine.

Installation will have two parts, first part is about the MCU program (arduino), and second part are the scripts for MPU.

p.s scripts for MPU are still in progress, will be update ASAP.
 

Below is the installing instruction about 
###MCU program (arduino)
1. You can download Arduino IDE [here](https://www.arduino.cc/en/Main/Software).
2. Put all folders in `library` into your arduino `libraries` folder. [Tutorial](https://www.arduino.cc/en/Guide/Libraries#toc5)
3. Use Arduino IDE to upload the code: `linkit_7688_duo_lora.ino`. [Tutorial](https://www.arduino.cc/en/Guide/HowtoUpload)

p.s `linkit_7688_duo_lora.ino` need to be in a same name folder, in this project, called `linkit_7688_duo_lora`. If you don't do let, the Arduino app will still ask you to make one. 

###MPU scripts (python + ash)
(Continue updating...)

