/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdlib.h"
#include "main.h"
#include "led.h"
#include "radio.h"
#include "baro.h"
#include "imu.h"
#include "gps.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint32_t x;
uint16_t data;
uint8_t mode = 'f';

int main(void)
{

	initLED();
	initRadio();
	initBaro();
	initIMU();
	initGPS();

	while (1)
	{
		/* Blink LED for every loop */
		toggleLED(LED_RED);
		delay(100000);
		toggleLED(LED_RED);
//		delay(100000);

		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET) {
			mode = USART_ReceiveData(USART2);
		}
		delay(100000);

		/* Loop until the USART2 Receive Data Register is not empty */
		//while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){}
		//x = USART_ReceiveData(USART2);

		/* Send received data back out on USART2 */
		//USART_SendData(USART2, x);
//		x++;
//		printInt(x);
//		USART_SendData(USART2, 0x0A);
//		delay(200);
//		USART_SendData(USART2, 0x0D);

		/* GPS */
		getGPS();
//		delay(2400);
//		printInt(gpsTime);
//		delay(2400);
//		printInt(gpsLat);
//		delay(2400);
//		printInt(gpsLong);
//		delay(2400);
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
//			USART_SendData(USART2, USART_ReceiveData(USART1));
//		}

		/* BAROMETER */
		getBaroPres();
		getBaroTemp();
		calcPressure();
//		printInt(baroP);

		/* XYZ ACCELERATIONS */
		getIMU();
//		USART_SendData(USART2, 0x58);
//		delay(2400);
//		USART_SendData(USART2, 0x3A);
//		delay(2400);
//		USART_SendData(USART2, 0x20);
//		delay(2400);
//
//		printInt(accelX);
//
//		USART_SendData(USART2, 0x59);
//		delay(2400);
//		USART_SendData(USART2, 0x3A);
//		delay(2400);
//		USART_SendData(USART2, 0x20);
//		delay(2400);
//
//		printInt(accelY);
//
//		USART_SendData(USART2, 0x5A);
//		delay(2400);
//		USART_SendData(USART2, 0x3A);
//		delay(2400);
//		USART_SendData(USART2, 0x20);
//		delay(2400);
//
//		printInt(accelZ);
//
//		USART_SendData(USART2, 0x0A);
//		delay(2400);
//		USART_SendData(USART2, 0x0D);


		updateRadio();
//		/* CS TEAM INTEGRATION TEST */
//		/* 0x09 -> \t
//		 * 0x53 -> 'S'
//		 * 0x4E -> 'N'
//		 * 0x50 -> 'P'
//		 * 0x0A -> \0
//		 * 0x30 -> '0'
//		 * 0x20 -> ' '
//		 */
//
//		// Free run
//		if (mode == 'f') {
//			// Start new packet
//			USART_SendData(USART2, 0x53);
//			delay(2400);
//			USART_SendData(USART2, 0x4E);
//			delay(2400);
//			USART_SendData(USART2, 0x50);
//			delay(2400);
//			USART_SendData(USART2, 0x20);
//			delay(2400);
//
//			// MPU-9250
//			// Accelerometer
//			printInt(accelX);
//			delay(2400);
//			printInt(accelY);
//			delay(2400);
//			printInt(accelZ);
//			delay(2400);
//			USART_SendData(USART2, (accelX >> 8) & 0xFF); // X
//			delay(2400);
//			USART_SendData(USART2, accelX & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (accelY >> 8) & 0xFF); // Y
//			delay(2400);
//			USART_SendData(USART2, accelY & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (accelZ >> 8) & 0xFF); // Z
//			delay(2400);
//			USART_SendData(USART2, accelZ & 0xFF);
//			delay(2400);
//			// Gyroscope
//			printInt(gyroX);
//			delay(2400);
//			printInt(gyroY);
//			delay(2400);
//			printInt(gyroZ);
//			delay(2400);
//			USART_SendData(USART2, (gyroX >> 8) & 0xFF); // X
//			delay(2400);
//			USART_SendData(USART2, gyroX & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gyroY >> 8) & 0xFF); // Y
//			delay(2400);
//			USART_SendData(USART2, gyroY & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gyroZ >> 8) & 0xFF); // Z
//			delay(2400);
//			USART_SendData(USART2, gyroZ & 0xFF);
//			delay(2400);
//			// Magnetometer
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			USART_SendData(USART2, 0x00); // X
//			delay(2400);
//			USART_SendData(USART2, 0x01);
//			delay(2400);
//			USART_SendData(USART2, 0x00); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x02);
//			delay(2400);
//			USART_SendData(USART2, 0x00); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x04);
//			delay(2400);
//
//			// H3LIS-200DL
//			// Accelerometer
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			USART_SendData(USART2, 0x08); // X
//			delay(2400);
//			USART_SendData(USART2, 0x10); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x20); // Z
//			delay(2400);
//
//			// MS5611
//			// Barometric Pressure
//			printInt(baroP);
//			delay(2400);
//			USART_SendData(USART2, 0x00); // Padding byte for 32 bits
//			delay(2400);
//			USART_SendData(USART2, (baroP >> 16) & 0xFF );
//			delay(2400);
//			USART_SendData(USART2, (baroP >> 8) & 0xFF );
//			delay(2400);
//			USART_SendData(USART2, baroP & 0xFF);
//			delay(2400);
//
//			// MAX-M8
//			// GPS
//			printInt(gpsLat);
//			delay(2400);
//			printInt(gpsLong);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			printInt(gpsTime);
//			delay(2400);
//			USART_SendData(USART2, (gpsLat >> 24) & 0xFF); // Lat
//			delay(2400);
//			USART_SendData(USART2, (gpsLat >> 16) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gpsLat >> 8) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, gpsLat & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gpsLong >> 24) & 0xFF); // Long
//			delay(2400);
//			USART_SendData(USART2, (gpsLong >> 16) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gpsLong >> 8) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, gpsLong & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, 0x00); // Alt
//			delay(2400);
//			USART_SendData(USART2, 0x00);
//			delay(2400);
//			USART_SendData(USART2, 0x00);
//			delay(2400);
//			USART_SendData(USART2, 0x00);
//			delay(2400);
//			USART_SendData(USART2, (gpsTime >> 24) & 0xFF); // Time
//			delay(2400);
//			USART_SendData(USART2, (gpsTime >> 16) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gpsTime >> 8) & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, gpsTime & 0xFF);
//			delay(2400);
//		}
//
//		// Altitude
//		if (mode == 'a') {
//			printInt(baroP);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//		}
//
//		// IMU
//		if (mode == 'i') {
//			printInt(accelX);
//			delay(2400);
//			printInt(accelY);
//			delay(2400);
//			printInt(accelZ);
//			delay(2400);
//			USART_SendData(USART2, (accelX >> 8) & 0xFF); // X
//			delay(2400);
//			USART_SendData(USART2, accelX & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (accelY >> 8) & 0xFF); // Y
//			delay(2400);
//			USART_SendData(USART2, accelY & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (accelZ >> 8) & 0xFF); // Z
//			delay(2400);
//			USART_SendData(USART2, accelZ & 0xFF);
//			delay(2400);
//			// Gyroscope
//			printInt(gyroX);
//			delay(2400);
//			printInt(gyroY);
//			delay(2400);
//			printInt(gyroZ);
//			delay(2400);
//			USART_SendData(USART2, (gyroX >> 8) & 0xFF); // X
//			delay(2400);
//			USART_SendData(USART2, gyroX & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gyroY >> 8) & 0xFF); // Y
//			delay(2400);
//			USART_SendData(USART2, gyroY & 0xFF);
//			delay(2400);
//			USART_SendData(USART2, (gyroZ >> 8) & 0xFF); // Z
//			delay(2400);
//			USART_SendData(USART2, gyroZ & 0xFF);
//			delay(2400);
//			// Magnetometer
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//		}
//
//		// GPS
//		if (mode == 'g') {
//			printInt(gpsLat);
//			delay(2400);
//			printInt(gpsLong);
//			delay(2400);
//			printInt(0);
//			delay(2400);
//			printInt(gpsTime);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x30);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//			USART_SendData(USART2, 0x0A);
//			delay(2400);
//		}
		// Finish with \n
//		USART_SendData(RADIO_USART, 0x0A);
//		delay(2400);
//		USART_SendData(RADIO_USART, 0x0D);
	}
}

void delay(uint32_t nCount) {
	while (nCount > 0) {
			nCount--;
	}
}

uint8_t SPI_Transaction(SPI_TypeDef* SPIx, uint8_t write) {
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPIx, write);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	return (uint8_t) SPI_I2S_ReceiveData(SPIx);
}

void updateRadio() {
	// Send "SNP"
	USART_SendData(USART2, 0x53);
	delay(2400);
	USART_SendData(USART2, 0x4E);
	delay(2400);
	USART_SendData(USART2, 0x50);
	delay(2400);

	// MPU-9250
	// Accelerometer
	USART_SendData(USART2, (accelX >> 8) & 0xFF); // X
	delay(2400);
	USART_SendData(USART2, accelX & 0xFF);
	delay(2400);
	USART_SendData(USART2, (accelY >> 8) & 0xFF); // Y
	delay(2400);
	USART_SendData(USART2, accelY & 0xFF);
	delay(2400);
	USART_SendData(USART2, (accelZ >> 8) & 0xFF); // Z
	delay(2400);
	USART_SendData(USART2, accelZ & 0xFF);
	delay(2400);
	// Gyroscope
	USART_SendData(USART2, (gyroX >> 8) & 0xFF); // X
	delay(2400);
	USART_SendData(USART2, gyroX & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gyroY >> 8) & 0xFF); // Y
	delay(2400);
	USART_SendData(USART2, gyroY & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gyroZ >> 8) & 0xFF); // Z
	delay(2400);
	USART_SendData(USART2, gyroZ & 0xFF);
	delay(2400);
	// Magnetometer
	USART_SendData(USART2, 0x00); // X
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);
	USART_SendData(USART2, 0x00); // Y
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);
	USART_SendData(USART2, 0x00); // Z
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);

	// H3LIS-200DL
	// Accelerometer
	USART_SendData(USART2, 0x00); // X
	delay(2400);
	USART_SendData(USART2, 0x00); // Y
	delay(2400);
	USART_SendData(USART2, 0x00); // Z
	delay(2400);

	// MS5611
	// Barometric Pressure
	USART_SendData(USART2, 0x00); // Padding byte for 32 bits
	delay(2400);
	USART_SendData(USART2, (baroP >> 16) & 0xFF );
	delay(2400);
	USART_SendData(USART2, (baroP >> 8) & 0xFF );
	delay(2400);
	USART_SendData(USART2, baroP & 0xFF);
	delay(2400);

	// MAX-M8
	// GPS
	USART_SendData(USART2, (gpsLat >> 24) & 0xFF); // Lat
	delay(2400);
	USART_SendData(USART2, (gpsLat >> 16) & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gpsLat >> 8) & 0xFF);
	delay(2400);
	USART_SendData(USART2, gpsLat & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gpsLong >> 24) & 0xFF); // Long
	delay(2400);
	USART_SendData(USART2, (gpsLong >> 16) & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gpsLong >> 8) & 0xFF);
	delay(2400);
	USART_SendData(USART2, gpsLong & 0xFF);
	delay(2400);
	USART_SendData(USART2, 0x00); // Alt
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);
	USART_SendData(USART2, 0x00);
	delay(2400);
	USART_SendData(USART2, (gpsTime >> 24) & 0xFF); // Time
	delay(2400);
	USART_SendData(USART2, (gpsTime >> 16) & 0xFF);
	delay(2400);
	USART_SendData(USART2, (gpsTime >> 8) & 0xFF);
	delay(2400);
	USART_SendData(USART2, gpsTime & 0xFF);
	delay(2400);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif
