/*
 * led.c
 *
 *  Created on: Mar 25, 2017
 *      Author: Ryan Domres
 */
#include "stm32f10x.h"
#include "led.h"

void initLED() {
	/* GPIOC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure LEDs in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = LED_GREEN | LED_YELLOW | LED_RED | LED_USB;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void setLED(uint8_t color) {
	LED_PORT->BSRR |= color;
}

void clearLED(uint8_t color) {
	LED_PORT->BRR |= color;
}

void toggleLED(uint8_t color) {
	if (LED_PORT->ODR & color) {LED_PORT->BRR |= color;}
	else {LED_PORT->BSRR |= color;}
}

void batLED(uint8_t level) {
	clearLED(LED_GREEN);
	clearLED(LED_YELLOW);
	clearLED(LED_RED);
	if (level--) {
		setLED(LED_RED);
		if (level--) {
			setLED(LED_YELLOW);
			if (level) {setLED(LED_GREEN);}
		}
	}
}
