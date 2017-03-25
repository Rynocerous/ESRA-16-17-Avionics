/*
 * baro.h
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */

#ifndef BARO_H_
#define BARO_H_

/* Pin Definitions */
#define BARO_NCS		GPIO_Pin_2
#define BARO_SCK		GPIO_Pin_10
#define BARO_MISO		GPIO_Pin_11
#define BARO_MOSI		GPIO_Pin_12
#define BARO_PORT		GPIOC
#define BARO_NCS_PORT	GPIOD
#define BARO_SPI		SPI3

/* MS5611 Registers */
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

/* Public Variables */
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;
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

/* Function Prototypes */
void initBaro();
void getBaroPres();
void getBaroTemp();
void calcPressure();

#endif /* BARO_H_ */
