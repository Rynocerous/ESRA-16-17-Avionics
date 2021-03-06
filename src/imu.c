/*
 * imu.c
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */

#include "stm32f10x.h"
#include "main.h"
#include "imu.h"

void initIMU() {
	/* PCLK2 = HCLK/2 */
	RCC_PCLK2Config(RCC_HCLK_Div2);

	/* GPIOA and SPI1 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
	/* Configure SCK and MOSI pins as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Pin = IMU_SCK | IMU_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(IMU_PORT, &GPIO_InitStructure);
	/* Configure NCS pin as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Pin = IMU_NCS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(IMU_PORT, &GPIO_InitStructure);
	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Pin = IMU_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(IMU_PORT, &GPIO_InitStructure);

	/* Set SPI1 NCS */
	IMU_PORT->BSRR |= (IMU_NCS);

	/* SPI1 configuration ------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(IMU_SPI, &SPI_InitStructure);

	/* Enable SPI1 */
	SPI_Cmd(IMU_SPI, ENABLE);

	// Wait 20ms after power up
	// Datasheet lists 11ms as minimum
	delay(20000);

	// Reset device registers
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, PWR_MGMT_1);
	SPI_Transaction(IMU_SPI, 0x80);
	IMU_PORT->BSRR |= IMU_NCS;

	delay(1000);

	// Reset signal paths, disable FIFO, enable I2C master
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, USER_CTRL);
	SPI_Transaction(IMU_SPI, 0x37);
	IMU_PORT->BSRR |= IMU_NCS;

	// Select PLL
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, PWR_MGMT_1);
	SPI_Transaction(IMU_SPI, 0x01);
	IMU_PORT->BSRR |= IMU_NCS;

	// Set gyro DLPF to ~100Hz bandwidth
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, CONFIG);
	SPI_Transaction(IMU_SPI, 0x02);
	IMU_PORT->BSRR |= IMU_NCS;

	// Set gyro full scale to +/- 2000 DPS
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_CONFIG);
	SPI_Transaction(IMU_SPI, 0x18);
	IMU_PORT->BSRR |= IMU_NCS;

	// Set accelerometer full scale to +/- 16g
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_CONFIG);
	SPI_Transaction(IMU_SPI, 0x18);
	IMU_PORT->BSRR |= IMU_NCS;

	// Set accelerometer DLPF to ~100Hz bandwidth
	IMU_PORT->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_CONFIG2);
	SPI_Transaction(IMU_SPI, 0x02);
	IMU_PORT->BSRR |= IMU_NCS;
}

void getIMU() {
	// Get X-axis acceleration
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_XOUT_H | 0x80);
	accelX = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_XOUT_L | 0x80);
	accelX |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	// Get Y-axis acceleration
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_YOUT_H | 0x80);
	accelY = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_YOUT_L | 0x80);
	accelY |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	// Get Z-axis acceleration
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_ZOUT_H | 0x80);
	accelZ = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, ACCEL_ZOUT_L | 0x80);
	accelZ |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	// Get X-axis rotation
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_XOUT_H | 0x80);
	gyroX = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_XOUT_L | 0x80);
	gyroX |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	// Get Y-axis rotation
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_YOUT_H | 0x80);
	gyroY = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_YOUT_L | 0x80);
	gyroY |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	// Get Z-axis rotation
	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_ZOUT_H | 0x80);
	gyroZ = (SPI_Transaction(IMU_SPI, 0x00) << 8);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);

	GPIOA->BRR |= IMU_NCS;
	SPI_Transaction(IMU_SPI, GYRO_ZOUT_L | 0x80);
	gyroZ |= SPI_Transaction(IMU_SPI, 0x00);
	GPIOA->BSRR |= IMU_NCS;
	delay(100);
}
