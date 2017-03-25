/*
 * radio.c
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */

#include "stm32f10x.h"
#include "stdlib.h"
#include "main.h"
#include "radio.h"

void initRadio() {
	/* USART2 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RADIO_PORT, &GPIO_InitStructure);

	/* Configure USART2 Tx as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin = RADIO_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(RADIO_PORT, &GPIO_InitStructure);

	/* USART2 configuration ------------------------------------------------------*/
	/* USART2 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART2 */
	USART_Init(RADIO_USART, &USART_InitStructure);

	/* Enable USART2 */
	USART_Cmd(RADIO_USART, ENABLE);
}

void printInt(uint32_t num) {
	char buffer[10];
	itoa(num, buffer, 10);

	uint8_t i = 0;
	while (i < 10) {
		if (buffer[i] > 47 && buffer[i] < 58) {
			USART_SendData(RADIO_USART, buffer[i]);
			delay(2400);
		}
		i++;
	}

	// Finish with \n
	USART_SendData(RADIO_USART, 0x0A);
	delay(2400);
	USART_SendData(RADIO_USART, 0x0D);
}
