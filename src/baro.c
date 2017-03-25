/*
 * baro.c
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */
#include "stm32f10x.h"
#include "main.h"
#include "baro.h"

void initBaro() {
	/* PCLK2 = HCLK/2 */
	RCC_PCLK2Config(RCC_HCLK_Div2);

	/* GPIOD, GPIOC, and SPI3 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure SPI3 pins: SCK, MISO and MOSI ---------------------------------*/
	/* Enable the SPI3 Pin's Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
	/* Configure SCK and MOSI pins as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Pin = BARO_SCK | BARO_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Configure NCS pin as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Pin = BARO_NCS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Pin = BARO_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Set SPI3 NCS */
	GPIOD->BSRR = (BARO_NCS);

	/* SPI3 configuration ------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(BARO_SPI, &SPI_InitStructure);

	/* Enable SPI3 */
	SPI_Cmd(BARO_SPI, ENABLE);

	/* Clear SPI3 NCS */
	GPIOD->BRR = (BARO_NCS);
	/* Send MS5611 reset command */
	while (SPI_I2S_GetFlagStatus(BARO_SPI, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(BARO_SPI, BARO_RESET);
	delay(2800);
	/* Set SPI3 NCS */
	GPIOD->BSRR = (BARO_NCS);

	/* Read MS5611 EEPROM */
	/* C1 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C1);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC1 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC1 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C2 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C2);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC2 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC2 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C3 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C3);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC3 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC3 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C4 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C4);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC4 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC4 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C5 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C5);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC5 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC5 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C6 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_C6);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroC6 = (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroC6 |= SPI_Transaction(BARO_SPI, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);
}

void getBaroPres() {
	/* Send conversion command to barometer */
	GPIOD->BRR |= (BARO_NCS);
	SPI_Transaction(BARO_SPI, BARO_CONV_PRES);
	delay(9040);
	GPIOD->BSRR |= (BARO_NCS);

	delay(1000);

	/* Read raw ADC conversion back */
	GPIOD->BRR |= (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_READ);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroD1 = (SPI_Transaction(BARO_SPI, BARO_READ) << 16);
	baroD1 |= (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroD1 |= SPI_Transaction(BARO_SPI, BARO_READ);

	delay(500);
	GPIOD->BSRR |= (BARO_NCS);
}

void getBaroTemp() {
	/* Send conversion command to barometer */
	GPIOD->BRR |= (BARO_NCS);
	SPI_Transaction(BARO_SPI, BARO_CONV_TEMP);
	delay(9040);
	GPIOD->BSRR |= (BARO_NCS);

	delay(1000);

	/* Read raw ADC conversion back */
	GPIOD->BRR |= (BARO_NCS);

	SPI_Transaction(BARO_SPI, BARO_READ);
	SPI_Transaction(BARO_SPI, BARO_READ);
	baroD2 = (SPI_Transaction(BARO_SPI, BARO_READ) << 16);
	baroD2 |= (SPI_Transaction(BARO_SPI, BARO_READ) << 8);
	baroD2 |= SPI_Transaction(BARO_SPI, BARO_READ);

	delay(500);
	GPIOD->BSRR |= (BARO_NCS);
}

void calcPressure() {
	/* Calculate temperature */
	baroDT = baroD2 - baroC5 * 256;
	baroTEMP = 2000 + baroDT * baroC6 / 8388608;

	/* Calculate temperature compensated pressure */
	baroOFF = (int64_t) (baroC2 * 65536 + baroC4 * baroDT / 128);
	baroSENS = (int64_t) (baroC1 * 32768 + baroC3 * baroDT / 256);
	baroP = (baroD1 * baroSENS / 2097152 - baroOFF) / 32768;

	/* Typecasting issues cause negative assignment */
	baroP &= 0x1FFFF;
}
