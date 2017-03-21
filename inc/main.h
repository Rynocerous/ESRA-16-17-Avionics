/*
 * main.h
 *
 *  Created on: Mar 10, 2017
 *      Author: Ryan
 */

#ifndef MAIN_H_
#define MAIN_H_

/* LED Definitions */
#define LED_GREEN		GPIO_Pin_3
#define LED_YELLOW 		GPIO_Pin_2
#define LED_RED 		GPIO_Pin_1
#define LED_USB 		GPIO_Pin_0
#define LED_PORT		GPIOC

/* Barometer Definitions */
#define BARO_NCS		GPIO_Pin_2
#define BARO_SCK		GPIO_Pin_10
#define BARO_MISO		GPIO_Pin_11
#define BARO_MOSI		GPIO_Pin_12

#define BARO_RESET 		0x1E
#define BARO_CONV_PRES	0x48
#define BARO_CONV_TEMP	0x58
#define BARO_READ		0x00
#define BARO_C1			(0xA0 + (1 << 1))
#define BARO_C2			(0xA0 + (2 << 1))
#define BARO_C3			(0xA0 + (3 << 1))
#define BARO_C4			(0xA0 + (4 << 1))
#define BARO_C5			(0xA0 + (5 << 1))
#define BARO_C6			(0xA0 + (6 << 1))

/* Barometer Variables */
uint16_t baroC1;
uint16_t baroC2;
uint16_t baroC3;
uint16_t baroC4;
uint16_t baroC5;
uint16_t baroC6;
uint32_t baroD1;
uint32_t baroD2;
int32_t baroDT;
int32_t baroTEMP;
int64_t baroOFF;
int64_t baroSENS;
int32_t baroP;

/* IMU Defintions */
#define IMU_NCS			GPIO_Pin_4
#define IMU_SCK			GPIO_Pin_5
#define IMU_MISO		GPIO_Pin_6
#define IMU_MOSI		GPIO_Pin_7

#define IMU_READ		0x80
#define IMU_WRITE		0x7F

#endif /* MAIN_H_ */
