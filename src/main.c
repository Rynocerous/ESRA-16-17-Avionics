/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdlib.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;
uint32_t x;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void delay(uint32_t nCount) {
	while (nCount > 0) {
			nCount--;
	}
}

void printInt(uint32_t num) {
	char buffer[20];
	itoa(num, buffer, 10);

	uint8_t i = 0;
	while (i < 20) {
		if (buffer[i] > 47 && buffer[i] < 58) {
			USART_SendData(USART2, buffer[i]);
			delay(200);
		}
		i++;
	}

	// Finish with \n
	USART_SendData(USART2, 0x0A);
	delay(200);
	USART_SendData(USART2, 0x0D);
}

uint8_t SPI_Transaction(SPI_TypeDef* SPIx, uint8_t write) {
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPIx, write);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPIx);
}

void initGPIO() {
	/* GPIOC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure LEDs in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = LED_GREEN | LED_YELLOW | LED_RED | LED_USB;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void initXBee() {
	/* USART2 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Tx as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART2 configuration ------------------------------------------------------*/
	/* USART2 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART2 */
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}

void initBaro() {
	/* PCLK2 = HCLK/2 */
	RCC_PCLK2Config(RCC_HCLK_Div2);

	/* GPIOD, GPIOC, and SPI3 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure SPI3 pins: SCK, MISO and MOSI ---------------------------------*/
	/* Enable the SPI3 Pins Software Remapping */
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
	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable SPI3 */
	SPI_Cmd(SPI3, ENABLE);

	/* Clear SPI3 NCS */
	GPIOD->BRR = (BARO_NCS);
	/* Send MS5611 reset command */
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI3, BARO_RESET);
	delay(2800);
	/* Set SPI3 NCS */
	GPIOD->BSRR = (BARO_NCS);

	/* Read MS5611 EEPROM */
	/* C1 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C1);
	SPI_Transaction(SPI3, BARO_READ);
	baroC1 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC1 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C2 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C2);
	SPI_Transaction(SPI3, BARO_READ);
	baroC2 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC2 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C3 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C3);
	SPI_Transaction(SPI3, BARO_READ);
	baroC3 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC3 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C4 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C4);
	SPI_Transaction(SPI3, BARO_READ);
	baroC4 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC4 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C5 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C5);
	SPI_Transaction(SPI3, BARO_READ);
	baroC5 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC5 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);

	/* C6 */
	GPIOD->BRR = (BARO_NCS);

	SPI_Transaction(SPI3, BARO_C6);
	SPI_Transaction(SPI3, BARO_READ);
	baroC6 = (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroC6 |= SPI_Transaction(SPI3, BARO_READ);

	GPIOD->BSRR = (BARO_NCS);
	delay(100);
}

void getBaro() {
	/* Send conversion command to barometer */
	GPIOD->BRR |= (BARO_NCS);
	SPI_Transaction(SPI3, BARO_CONV_PRES);
	delay(9040);
	GPIOD->BSRR |= (BARO_NCS);

	delay(1000);

	/* Read raw ADC conversion back */
	GPIOD->BRR |= (BARO_NCS);

	SPI_Transaction(SPI3, BARO_READ);
	SPI_Transaction(SPI3, BARO_READ);
	baroD1 = (SPI_Transaction(SPI3, BARO_READ) << 16);
	baroD1 |= (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroD1 |= SPI_Transaction(SPI3, BARO_READ);

	delay(500);
	GPIOD->BSRR |= (BARO_NCS);
}

void getBaroTemp() {
	/* Send conversion command to barometer */
	GPIOD->BRR |= (BARO_NCS);
	SPI_Transaction(SPI3, BARO_CONV_TEMP);
	delay(9040);
	GPIOD->BSRR |= (BARO_NCS);

	delay(1000);

	/* Read raw ADC conversion back */
	GPIOD->BRR |= (BARO_NCS);

	SPI_Transaction(SPI3, BARO_READ);
	SPI_Transaction(SPI3, BARO_READ);
	baroD2 = (SPI_Transaction(SPI3, BARO_READ) << 16);
	baroD2 |= (SPI_Transaction(SPI3, BARO_READ) << 8);
	baroD2 |= SPI_Transaction(SPI3, BARO_READ);

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
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Configure NCS pin as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Pin = IMU_NCS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Pin = IMU_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Set SPI1 NCS */
	GPIOD->BSRR = (IMU_NCS);

	/* SPI1 configuration ------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);

	/* Enable SPI1 */
	SPI_Cmd(SPI1, ENABLE);
}

int main(void)
{

	initGPIO();

	initXBee();

	initBaro();

	while (1)
	{
		/* Set PC0 and PC2 */
		GPIOC->BSRR = LED_GREEN;
		GPIOC->BRR  = LED_RED;
		delay(100000);
		/* Set PC1 and PC3 */
		GPIOC->BSRR = LED_RED;
		GPIOC->BRR  = LED_GREEN;
		//delay(500000);

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


		getBaro();
		getBaroTemp();
		calcPressure();
		printInt(baroP);
	}
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
