/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"

uint32_t a = 0;
uint32_t b = 1000000000;
uint32_t c = 2000000000;
uint32_t d = 3000000000;

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	for(;;)
		{
		GPIOC->BSRR = 0x00000001;
		Delay(50000);
		GPIOC->BRR  = 0x00000001;
		Delay(50000);
		GPIOC->BSRR = 0x00000002;
				Delay(50000);
				GPIOC->BRR  = 0x00000002;
				Delay(50000);
				GPIOC->BSRR = 0x00000004;
						Delay(50000);
						GPIOC->BRR  = 0x00000004;
						Delay(50000);
						GPIOC->BSRR = 0x00000008;
								Delay(50000);
								GPIOC->BRR  = 0x00000008;
								Delay(50000);

		}
}
