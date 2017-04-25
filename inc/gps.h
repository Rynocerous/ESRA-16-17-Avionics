/*
 * gps.h
 *
 *  Created on: Apr 18, 2017
 *      Author: Ryan Domres
 */

#ifndef GPS_H_
#define GPS_H_

/* Pin Definitions */
#define GPS_TX			GPIO_Pin_6
#define GPS_RX			GPIO_Pin_7
#define GPS_PORT		GPIOB
#define GPS_USART		USART1

/* Settings Array */
//Settings Array contains the following settings:
//[0]NavMode
//[1]DataRate1
//[2]DataRate2
//[3]PortRateByte1
//[4]PortRateByte2
//[5]PortRateByte3,
//[6]NMEA GLL Sentence
//[7]NMEA GSA Sentence
//[8]NMEA GSV Sentence
//[9]NMEA RMC Sentence
//[10]NMEA VTG Sentence
//
//NavMode:
//Pedestrian Mode    = 0x03
//Automotive Mode    = 0x04
//Sea Mode           = 0x05
//Airborne < 1G Mode = 0x06
//
//DataRate:
//1Hz     = 0xE8 0x03
//2Hz     = 0xF4 0x01
//3.33Hz  = 0x2C 0x01
//4Hz     = 0xFA 0x00
//
//PortRate:
//4800   = C0 12 00
//9600   = 80 25 00
//19200  = 00 4B 00
//38400  = 00 96 00
//57600  = 00 E1 00
//115200 = 00 C2 01
//230400 = 00 84 03
//
//NMEA Messages:
//OFF = 0x00
//ON  = 0x01
//
uint8_t settingsArray[] = {0x03, 0xFA, 0x00, 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* Public Variables */
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
uint8_t gpsStatus[] = {0, 0, 0, 0, 0, 0, 0};
unsigned long start;

/* Function Prototypes */
void initGPS();
void configureGPS();
void getGPS();
void sendUBX(uint8_t *, uint8_t);
void calcChecksum(uint8_t *, uint8_t);

#endif /* GPS_H_ */
