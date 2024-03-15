/*
 * MGPIO_prv.h
 *
 *  Created on: 16 Jan 2024
 *      Author: Ahmed Samy
 */

#ifndef MGPIO_PRV_H_
#define MGPIO_PRV_H_

#define GPIO_A_BASE_ADDRESS		0x40020000
#define GPIO_B_BASE_ADDRESS		0x40020400
#define GPIO_C_BASE_ADDRESS		0x40020800

typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_t;





#define GPIO_A ((volatile GPIO_t*)(GPIO_A_BASE_ADDRESS))
#define GPIO_B ((volatile GPIO_t*)(GPIO_B_BASE_ADDRESS))
#define GPIO_C ((volatile GPIO_t*)(GPIO_C_BASE_ADDRESS))

#define MODDER_MUSK		3
#define ALT_MUSK		15
#endif /* MGPIO_PRV_H_ */
