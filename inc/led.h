/*
 * led.h
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */

#ifndef LED_H_
#define LED_H_

/* Pin Definitions */
#define LED_GREEN		GPIO_Pin_3
#define LED_YELLOW 		GPIO_Pin_2
#define LED_RED 		GPIO_Pin_1
#define LED_USB 		GPIO_Pin_0
#define LED_PORT		GPIOC

/* Private Variables */
GPIO_InitTypeDef GPIO_InitStructure;

/* Function Prototypes */
void initLED();
void setLED(uint8_t);
void clearLED(uint8_t);
void toggleLED(uint8_t);
void batLED(uint8_t);

#endif /* LED_H_ */
