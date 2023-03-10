/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;

//Define Registers
#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define LED1_MODER *((volatile uint32_t *) 0x42020400) //blue led
#define LED2_MODER *((volatile uint32_t *) 0x42020800) //green led
#define PUSHBUTTON_MODER *((volatile uint32_t *) 0x42020800)
#define LED1_ODR *((volatile uint32_t *) 0x42020414) //blue led
#define LED2_ODR *((volatile uint32_t *) 0x42020814) //green led
#define PUSHBUTTON_IDR *((volatile uint32_t *) 0x42020810)


void gpio_clock_enable(int gpioIndex){
	//A is 0, B is 1, C is 2, D is 3, E is 4, F is 5, G is 6, H is 7
	switch(gpioIndex){
	case 0:
		RCC_AHB2ENR |= 1;
		break;
	case 1:
		RCC_AHB2ENR |= 2;
		break;
	case 2:
		RCC_AHB2ENR |= 4;
		break;
	case 3:
		RCC_AHB2ENR |= 8;
		break;
	case 4:
		RCC_AHB2ENR |= 16;
		break;
	case 5:
		RCC_AHB2ENR |= 32;
		break;
	case 6:
		RCC_AHB2ENR |= 64;
		break;
	case 7:
		RCC_AHB2ENR |= 128;
		break;
	default:
		RCC_AHB2ENR |= 0;
	}
}

/*
void gpio_moder_pin_enable(int pinIndex, int portMode){
	int right = pinIndex * 2;
	int left = 0;
	switch(portMode){
	case 0:
		left = 3;
		break;
	case 1:
		right++;
		left = 1;
		break;
	case 2:
		left = 1;
		break;
	default:
		left = 0;
	}

	GPIO_MODER &= ~(left << right);
}

void gpio_odr_enable(int pinIndex){
	GPIO_ODR |= (1 << pinIndex);
}

void gpio_odr_disable(int pinIndex){
	GPIO_ODR &= ~(1 << pinIndex);
}
*/

int main(void) {
	//Enable Clock for GPIO
	gpio_clock_enable(1);
	gpio_clock_enable(2);


	//Configure Pin as General purpose output mode

	LED1_MODER &= ~(1 << 15);
	LED2_MODER &= ~(1 << 15);
	PUSHBUTTON_MODER &= ~(3 << 26);


	while(1) {

		//when not pressed
		LED1_ODR |= (1 << 7);
		LED2_ODR &= ~(1 << 7);

		while(!(PUSHBUTTON_IDR & 1 << 13)){}

		//when pressed
		LED2_ODR |= (1 << 7);
		LED1_ODR &= ~(1 << 7);

		while(PUSHBUTTON_IDR & 1 << 13){}
	}
}
