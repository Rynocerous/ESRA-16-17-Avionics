/*
 * radio.h
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */

#ifndef RADIO_H_
#define RADIO_H_

/* Pin Definitions */
#define RADIO_TX		GPIO_Pin_2
#define RADIO_RX		GPIO_Pin_3
#define RADIO_PORT		GPIOA
#define RADIO_USART		USART2

/* Public Variables */
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

/* Function Prototypes */
void initRadio();
void printInt(uint32_t);

#endif /* RADIO_H_ */
