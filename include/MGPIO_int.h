/*
 * MGPIO_int.h
 *
 *  Created on: 16 Jan 2024
 *      Author: Ahmed Samy
 */

#ifndef MGPIO_INT_H_
#define MGPIO_INT_H_

/*MODER*/
#define		INPUT			0
#define 	OUTPUT			1
#define 	ALT_FUNCTION	2
#define 	ANALOG			3
/******************************************/

/*INPUT MODE*/
#define   	NO_UP_NO_DOWN   0
#define		PULLUP			1
#define   	PULLDOWN 		2
/*****************************************/

/*OUTPUT MODE*/
#define   	PUSH_PULL   	0
#define		OPEN_DRAIN		1
/*****************************************/

/*OUTPUT VALUE*/
#define  GPIO_HIGH    		1
#define  GPIO_LOW    		0
/*****************************************/

/*OSPEEDR*/
#define		LOW_SPEED		0
#define 	MID_SPEED		1
#define 	HIGH_SPEED		2
#define 	VERY_HIGH_SPEED	3
/******************************************/
/*ALT FUN*/
#define		ALT_UART1			7
#define		ALT_SPI1			5

/******************************************/

/*PORT*/
#define  PORT_A   0
#define  PORT_B   1
#define  PORT_C   2
/*****************************************/

/* PIN NUMBER */
#define GPIO_PIN_NUM_0      0
#define GPIO_PIN_NUM_1      1
#define GPIO_PIN_NUM_2      2
#define GPIO_PIN_NUM_3      3
#define GPIO_PIN_NUM_4      4
#define GPIO_PIN_NUM_5      5
#define GPIO_PIN_NUM_6      6
#define GPIO_PIN_NUM_7      7
#define GPIO_PIN_NUM_8      8
#define GPIO_PIN_NUM_9      9
#define GPIO_PIN_NUM_10     10
#define GPIO_PIN_NUM_11     11
#define GPIO_PIN_NUM_12     12
#define GPIO_PIN_NUM_13     13
#define GPIO_PIN_NUM_14     14
#define GPIO_PIN_NUM_15     15
/*****************************************/




void MGPIO_VOIDsetMode(u8 Port, u8 Pin, u8 Mode);
void MGPIO_VOIDsetOutputMode(u8 Port, u8 Pin, u8 OutputMode, u8 Speed);
void MGPIO_VOIDsetInputMode(u8 Port, u8 Pin, u8 PullMode);
u8 MGPIO_U8ReadPin(u8 Port, u8 Pin);
void MGPIO_VOIDWritePin(u8 Port, u8 Pin, u8 PinValue);
void MGPIO_VOIDSetaltFun(u8 Port, u8 Pin, u8 Prepheral);

#endif /* MGPIO_INT_H_ */
