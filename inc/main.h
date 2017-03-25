/*
 * main.h
 *
 *  Created on: Mar 10, 2017
 *      Author: Ryan Domres
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Peripheral Init Structures */
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;

/* Function Prototypes */
void delay(uint32_t);
void printInt(uint32_t);
uint8_t SPI_Transaction(SPI_TypeDef*, uint8_t);

#endif /* MAIN_H_ */
