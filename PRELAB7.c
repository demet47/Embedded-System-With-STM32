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

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
	volatile uint32_t BRR;
	uint32_t RESERVED;
	volatile uint32_t SECCFGR;
} GPIO_TypeDef;

typedef struct
{
	  volatile uint32_t CR1;
	  volatile uint32_t CR2;
	  volatile uint32_t SMCR;
	  volatile uint32_t DIER;
	  volatile uint32_t SR;
	  volatile uint32_t EGR;
	  volatile uint32_t CCMR1;
	  volatile uint32_t CCMR2;
	  volatile uint32_t CCER;
	  volatile uint32_t CNT;
	  volatile uint32_t PSC;
	  volatile uint32_t ARR;
	  volatile uint32_t RCR;
	  volatile uint32_t CCR1;
	  volatile uint32_t CCR2;
	  volatile uint32_t CCR3;
	  volatile uint32_t CCR4;
	  volatile uint32_t BDTR;
	  volatile uint32_t DCR;
	  volatile uint32_t DMAR;
	  volatile uint32_t OR1;
	  volatile uint32_t CCMR3;
	  volatile uint32_t CCR5;
	  volatile uint32_t CCR6;
	  volatile uint32_t OR2;
	  volatile uint32_t OR3;
} TIM_TypeDef;

// blue cable	PC8
// green cable	PC9
// orange cable	PC10
// red cable 	5V

//TIM4,5,6,7 -> APB1


// R+G+B, B+G , B+R , B, R+G, G, R , -
//G G - - G G - - (diff 0)
//R - R - R - R - (diff 0)
//B B B B - - - - (diff 0)

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021000 + 0x058)) //tim4,5,6,7 offset: 2,3,4,5  colors:red,green, blue, switching

#define TIM4 ((TIM_TypeDef *)	0x40000800)
#define TIM5 ((TIM_TypeDef *)	0x40000C00)
#define TIM6 ((TIM_TypeDef *)	0x40001000)
#define TIM7 ((TIM_TypeDef *)	0x40001400)

#define GPIOC ((GPIO_TypeDef *)	0x42020800)
#define ISER1 ((uint32_t *) 0xE000E104)
#define ISER2 ((uint32_t *) 0xE000E108)
#define ISER3 ((uint32_t *) 0xE000E10C)
#define ISER4 ((uint32_t *) 0xE000E110)


static uint32_t counter_blue = 0;
static uint32_t counter_red = 0;
static uint32_t counter_green = 0;

TIM_TypeDef* TIMER[4] = {TIM4,TIM5, TIM6, TIM7};


void swap(int pin){
	GPIOC->ODR ^= 1 << pin;

}

void turn_off(int led_code){
	GPIOC->ODR |= 1 << led_code;
}

void turn_on(int led_code){
	GPIOC->ODR &= ~(1 << led_code);
}


void TIM4_IRQHandler(void){ //red
	if((counter_red % 2 < 1))
		swap(10);
	else{
		turn_off(10);
	}

	TIM4->SR = 0;
}

void TIM5_IRQHandler(void){ //green
	if(counter_green % 4 < 2){
		swap(9);
	}else{
		turn_off(9);
	}
	TIM5->SR = 0;
}

void TIM6_IRQHandler(void){ //blue
	if(counter_blue % 8 < 4){
		swap(8);
	}else{
		turn_off(8);
	}
	TIM6->SR = 0;
}

void TIM7_IRQHandler(void){ //switching
	//open and immediately close the premask, then format the pending status for all interrupts
	counter_green++;
	counter_blue++;
	counter_red++;
	TIM7->SR = 0;
}



void init_timer(int timer){
	RCC_APB1ENR1 |= 1 << (timer-2);
	TIMER[timer-4]->PSC = 4000 - 1;
	TIMER[timer-4]->CR1 &= ~(1<<1);
	TIMER[timer-4]->DIER |= 1;
	TIMER[timer-4]->EGR |= 1;
	TIMER[timer-4]->CNT = 0;
	TIMER[timer-4]->SR = 0;
	TIMER[timer-4]->CR1 |= 1;
	*ISER1 |= (1 << (11+timer));
}


int main(void)
{

	RCC_AHB2ENR |= 1 << 2; //enable clock for GPIOC
	//RCC_APB1ENR1 |= 15 << 2; //enable clock for tim4,5,6,7


	GPIOC->PUPDR &= ~(0x03 << (9 * 2)); //green reset
	GPIOC->PUPDR |= (0x01 << (9 * 2)); //green output

	GPIOC->PUPDR &= ~(0x03 << (8 * 2)); //blue reset
	GPIOC->PUPDR |= (0x01 << (8 * 2)); //blue output

	GPIOC->PUPDR &= ~(0x03 << (10 * 2)); //orange reset
	GPIOC->PUPDR |= (0x01 << (10 * 2)); //orange output

	GPIOC->MODER &= ~(0x03 << (8 * 2)); //blue reset
	GPIOC->MODER |= (0x01 << (8 * 2)); //blue output

	GPIOC->MODER &= ~(0x03 << (9 * 2)); //green reset
	GPIOC->MODER |= (0x01 << (9 * 2)); //green output

	GPIOC->MODER &= ~(0x03 << (10 * 2)); //orange reset
	GPIOC->MODER |= (0x01 << (10 * 2)); //orange output



	TIM4->ARR = 9;
	TIM5->ARR = 4;
	TIM6->ARR = 2; //try 2 also
	TIM7->ARR = 999;



	init_timer(4);
	init_timer(5);
	init_timer(6);
	init_timer(7);


	__asm volatile(
			"mov r0, #0 \n\t"
			"msr primask, r0 \n\t"
		 );

	//turn on premask and start counters
	while(1){
		__asm volatile("wfi");
	};

}