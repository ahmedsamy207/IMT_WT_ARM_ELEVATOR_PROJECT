/*
 * STP_program.c
 *
 *  Created on: Jan 28, 2024
 *      Author: Ahmed Samy
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "STP_private.h"
#include "STP_config.h"
#include "STP_interface.h"
#include "MGPIO_int.h"
#include "Timer2_interface.h"
#include "SYSTICK_interface.h"

void S2P_vInit(void)
{
MGPIO_VOIDsetMode(HSTP_SERIAL_DATA,OUTPUT);
MGPIO_VOIDsetOutputMode(HSTP_SERIAL_DATA,PUSH_PULL,LOW_SPEED);

MGPIO_VOIDsetMode(HSTP_SHIFT_CLOCK,OUTPUT);
MGPIO_VOIDsetOutputMode(HSTP_SERIAL_DATA,PUSH_PULL,LOW_SPEED);

MGPIO_VOIDsetMode(HSTP_STORAGE_CLOCK,OUTPUT);
MGPIO_VOIDsetOutputMode(HSTP_SERIAL_DATA,PUSH_PULL,LOW_SPEED);
}

void S2P_vSendPulse(void)
{
MGPIO_VOIDWritePin(HSTP_SHIFT_CLOCK,GPIO_HIGH);
TIM2_voidSetBusyWait(2);
MGPIO_VOIDWritePin(HSTP_SHIFT_CLOCK,GPIO_LOW);
TIM2_voidSetBusyWait(2);

}

void S2P_vSendData(u16 Copy_u16Data)
{
	s8 Local_u8Iterator = 0 ;

	for(Local_u8Iterator = 15 ; Local_u8Iterator >= 0 ; Local_u8Iterator --  )
	{
		MGPIO_VOIDWritePin(HSTP_SERIAL_DATA, GET_BIT(Copy_u16Data,Local_u8Iterator));
		S2P_vSendPulse();
	}
	/* Send Pulse To Storage Pin */
	MGPIO_VOIDWritePin(HSTP_STORAGE_CLOCK,GPIO_HIGH);
	TIM2_voidSetBusyWait(2);
	MGPIO_VOIDWritePin(HSTP_STORAGE_CLOCK,GPIO_LOW);
	TIM2_voidSetBusyWait(2);
}
