/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdlib.h"
#include "main.h"
#include "led.h"
#include "radio.h"
#include "baro.h"
#include "imu.h"

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

	while (1)
	{
		/* Blink LED for every loop */
		toggleLED(LED_RED);
		delay(1000000);
		toggleLED(LED_RED);

//		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET) {
//			mode = USART_ReceiveData(USART2);
//		}
//		delay(100000);

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

		/* BAROMETER */
//		getBaroPres();
//		getBaroTemp();
//		calcPressure();
//		printInt(baroP);

		/* XYZ ACCELERATIONS */
		USART_SendData(USART2, 0x58);
		delay(2400);
		USART_SendData(USART2, 0x3A);
		delay(2400);
		USART_SendData(USART2, 0x20);
		delay(2400);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 59 | 0x80);
		data = (SPI_Transaction(IMU_SPI, 0x00) << 8);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 60 | 0x80);
		data |= SPI_Transaction(IMU_SPI, 0x00);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		printInt(data);

		USART_SendData(USART2, 0x59);
		delay(2400);
		USART_SendData(USART2, 0x3A);
		delay(2400);
		USART_SendData(USART2, 0x20);
		delay(2400);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 61 | 0x80);
		data = (SPI_Transaction(IMU_SPI, 0x00) << 8);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 62 | 0x80);
		data |= SPI_Transaction(IMU_SPI, 0x00);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		printInt(data);

		USART_SendData(USART2, 0x5A);
		delay(2400);
		USART_SendData(USART2, 0x3A);
		delay(2400);
		USART_SendData(USART2, 0x20);
		delay(2400);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 63 | 0x80);
		data = (SPI_Transaction(IMU_SPI, 0x00) << 8);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		GPIOA->BRR |= IMU_NCS;
		SPI_Transaction(IMU_SPI, 64 | 0x80);
		data |= SPI_Transaction(IMU_SPI, 0x00);
		GPIOA->BSRR |= IMU_NCS;
		delay(100);

		printInt(data);

		USART_SendData(USART2, 0x0A);
		delay(2400);
		USART_SendData(USART2, 0x0D);


//		/* CS TEAM INTEGRATION TEST */
//		/* 0x09 -> \t
//		 * 0x53 -> 'S'
//		 * 0x4E -> 'N'
//		 * 0x50 -> 'P'
//		 * 0x0A -> \0
//		 * 0x30 -> '0'
//		 */
//
//		// Free run
//		if (mode == 'f') {
//			// Start new packet
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x53);
//			delay(2400);
//			USART_SendData(USART2, 0x4E);
//			delay(2400);
//			USART_SendData(USART2, 0x50);
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//
//			// MPU-9250
//			// Accelerometer
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			// Gyroscope
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			// Magnetometer
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//
//			// H3LIS-200DL
//			// Accelerometer
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			// Gyroscope
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			// Magnetometer
//			USART_SendData(USART2, 0x30); // X
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Y
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Z
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//
//			// MS5611
//			// Altitude
//			printInt(baroP);
//			delay(2400);
//	//		USART_SendData(USART2, 0x30);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//
//			// MAX-M8
//			// GPS
//			USART_SendData(USART2, 0x30); // Lat
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Lon
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Alt
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//			USART_SendData(USART2, 0x30); // Time
//			delay(2400);
//			USART_SendData(USART2, 0x09);
//			delay(2400);
//
//			USART_SendData(USART2, 0x0A);
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
