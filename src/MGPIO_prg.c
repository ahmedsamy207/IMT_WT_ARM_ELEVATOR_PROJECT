/*
 * MGPIO_prg.c
 *
 *  Created on: 16 Jan 2024
 *      Author: Ahmed Samy
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "MGPIO_prv.h"
#include "MGPIO_cfg.h"
#include "MGPIO_int.h"



void MGPIO_VOIDsetMode(u8 Port, u8 Pin, u8 Mode)
{
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch (Port) {
		case PORT_A:
			GPIO_A->MODER &=~(MODDER_MUSK<<Pin*2);
			GPIO_A->MODER |=(Mode<<Pin*2);
			break;
		case PORT_B:
			GPIO_B->MODER &=~(MODDER_MUSK<<Pin*2);
			GPIO_B->MODER |=(Mode<<Pin*2);
			break;
		case PORT_C:
			GPIO_C->MODER &=~(MODDER_MUSK<<Pin*2);
			GPIO_C->MODER |=(Mode<<Pin*2);
			break;
		default:
			break;
		}
	}
}
void MGPIO_VOIDsetOutputMode(u8 Port, u8 Pin, u8 OutputMode, u8 Speed)
{
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch (Port) {
		case PORT_A:
			CLR_BIT(GPIO_A->OTYPER, Pin);
			GPIO_A->OTYPER |=(OutputMode<<Pin);
			GPIO_A->OSPEEDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_A->OSPEEDR |=(Speed<<Pin*2);
			break;
		case PORT_B:
			CLR_BIT(GPIO_B->OTYPER, Pin);
			GPIO_B->OTYPER |=(OutputMode<<Pin);
			GPIO_B->OSPEEDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_B->OSPEEDR |=(Speed<<Pin*2);
			break;
		case PORT_C:
			CLR_BIT(GPIO_C->OTYPER, Pin);
			GPIO_C->OTYPER |=(OutputMode<<Pin);
			GPIO_C->OSPEEDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_C->OSPEEDR |=(Speed<<Pin*2);
			break;
		default:
			break;
		}
	}
}
void MGPIO_VOIDsetInputMode(u8 Port, u8 Pin, u8 PullMode)
{
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch (Port) {
		case PORT_A:
			GPIO_A->PUPDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_A->PUPDR |=(PullMode<<Pin*2);
			break;
		case PORT_B:
			GPIO_B->PUPDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_B->PUPDR |=(PullMode<<Pin*2);
			break;
		case PORT_C:
			GPIO_C->PUPDR &=~(MODDER_MUSK<<Pin*2);
			GPIO_C->PUPDR |=(PullMode<<Pin*2);
			break;
		default:
			break;
		}
	}
}
u8 MGPIO_U8ReadPin(u8 Port, u8 Pin)
{
	u8 Data=0;
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch(Port)
		{
		case PORT_A :
			Data= GET_BIT(GPIO_A->IDR,Pin);
			break;
		case PORT_B :
			Data= GET_BIT(GPIO_B->IDR,Pin);
			break;
		case PORT_C :
			Data= GET_BIT(GPIO_C->IDR,Pin);
			break;
		default:
			break;
		}
	}
	return Data;
}


void MGPIO_VOIDWritePin(u8 Port, u8 Pin, u8 PinValue)
{
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch(Port)
		{
		case PORT_A :
			if (PinValue==GPIO_HIGH)
			{
				SET_BIT(GPIO_A->ODR,Pin);
			}
			else if (PinValue==GPIO_LOW)
			{
				CLR_BIT(GPIO_A->ODR,Pin);
			}
			break;
		case PORT_B :
			if (PinValue==GPIO_HIGH)
			{
				SET_BIT(GPIO_B->ODR,Pin);
			}
			else if (PinValue==GPIO_LOW)
			{
				CLR_BIT(GPIO_B->ODR,Pin);
			}
			break;

		case PORT_C :
			if (PinValue==GPIO_HIGH)
			{
				SET_BIT(GPIO_C->ODR,Pin);
			}
			else if (PinValue==GPIO_LOW)
			{
				CLR_BIT(GPIO_C->ODR,Pin);
			}
			break;
		default:
			break;
		}
	}
}

void MGPIO_VOIDSetaltFun(u8 Port, u8 Pin, u8 Prepheral)
{
	if((Port == PORT_A) && (Pin == GPIO_PIN_NUM_13 || Pin == GPIO_PIN_NUM_14 || Pin == GPIO_PIN_NUM_15))
	{

	}
	else if((Port == PORT_B) && (Pin == GPIO_PIN_NUM_2 || Pin == GPIO_PIN_NUM_3 || Pin == GPIO_PIN_NUM_4))
	{

	}
	else
	{
		switch(Port)
		{
		case PORT_A :
			if (Pin>=0 && Pin<=7)
			{
				GPIO_A->AFRL &=~(ALT_MUSK<<Pin*4);
				GPIO_A->AFRL |=(Prepheral<<Pin*4);
			}
			else if (Pin>=8 && Pin<=15)
			{
				Pin= Pin-8;
				GPIO_A->AFRH &=~(ALT_MUSK<<(Pin)*4);
				GPIO_A->AFRH |=(Prepheral<<Pin*4);
			}
			break;
		case PORT_B :
			if (Pin>=0 && Pin<=7)
			{
				GPIO_B->AFRL &=~(ALT_MUSK<<Pin*4);
				GPIO_B->AFRL |=(Prepheral<<Pin*4);
			}
			else if (Pin>=8 && Pin<=15)
			{
				Pin= Pin-8;
				GPIO_B->AFRH &=~(ALT_MUSK<<(Pin)*4);
				GPIO_B->AFRH |=(Prepheral<<Pin*4);
			}
			break;
		case PORT_C :
			if (Pin>=0 && Pin<=7)
			{
				GPIO_C->AFRL &=~(ALT_MUSK<<Pin*4);
				GPIO_C->AFRL |=(Prepheral<<Pin*4);
			}
			else if (Pin>=8 && Pin<=15)
			{
				Pin= Pin-8;
				GPIO_C->AFRH &=~(ALT_MUSK<<(Pin)*4);
				GPIO_C->AFRH |=(Prepheral<<Pin*4);
			}
			break;
		default:
			break;
		}
	}
}

