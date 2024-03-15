/*
 * R2RDAC_PROGRAM.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Ahmed Samy
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "R2RDAC_INTERFACE.h"
#include "R2RDAC_CONFIG.h"
#include "R2RDAC_PRIVATE.h"
#include "MGPIO_int.h"
#include "SYSTICK_interface.h"

void R2RDAC_Init(void)
{
for(u8 i =0 ;i<8;i++)
{
	MGPIO_VOIDsetMode(PORT_B,i,OUTPUT);
	MGPIO_VOIDsetOutputMode(PORT_B,i,PUSH_PULL,MID_SPEED);
}

}

void R2RDAC_SetData(const u8 *arr,u32 arrsize)
{
	u32 counter;
	for(counter=0;counter<arrsize;counter++)
	{
		for(u8 i =0 ;i<8;i++)
		{
			MGPIO_VOIDWritePin(PORT_B,i,GET_BIT(arr[counter],i));

		}
		MSYSYTICK_voidDelayUs(125);
	}
	MSYSYTICK_voidCtrlIntState(SYSTICKEnable);
}


