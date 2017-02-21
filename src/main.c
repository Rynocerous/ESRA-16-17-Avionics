/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
uint8_t x;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void delay(uint32_t nCount) {
	while (nCount > 0) {
			nCount--;
	}
}

void initGPIO() {
	/* GPIOC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure LEDs in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
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
		- BaudRate = 230400 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- Even parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 230400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART2 */
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}

int main(void)
{

	initGPIO();

	initXBee();

	while (1)
	{
		/* Set PC0 and PC2 */
		GPIOC->BSRR = 0x00000001;
		GPIOC->BRR  = 0x00000004;
		delay(100000);
		/* Set PC1 and PC3 */
		GPIOC->BSRR = 0x00000004;
		GPIOC->BRR  = 0x00000001;
		//delay(500000);

		/* Loop until the USART2 Receive Data Register is not empty */
		while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){}
		x = USART_ReceiveData(USART2);
		/* Send received data back out on USART2 */
		USART_SendData(USART2, x);
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
