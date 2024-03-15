/*
 * HTFT_prg.c
 *
 *  Created on: 5 Feb 2024
 *      Author: Ahmed Samy
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "MGPIO_int.h"
#include "SPI_interface.h"
#include "SYSTICK_interface.h"
#include "HTFT_int.h"


void HTFT_vInit(void)
{
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_12,OUTPUT);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_11,OUTPUT);
	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_11,PUSH_PULL,LOW_SPEED);
	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_12,PUSH_PULL,LOW_SPEED);
/* RESET CONFIG */
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_12, GPIO_HIGH);
	MSYSYTICK_voidDelayUs(100);
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_12, GPIO_LOW);
	MSYSYTICK_voidDelayUs(3);
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_12, GPIO_HIGH);
	MSYSYTICK_voidDelayUs(100);
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_12, GPIO_LOW);
	MSYSYTICK_voidDelayUs(100);
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_12, GPIO_HIGH);
	MSYSYTICK_voidDelayms(120);
/**********************************************************/
/* Sleep out */
	HTFT_vWriteCmd(0x11);
	MSYSYTICK_voidDelayms(10);
/* Color mode (have parameter) */
	HTFT_vWriteCmd(0x3A);
	HTFT_vWriteData(0x05);
/* Display On */
	HTFT_vWriteCmd(0x29);
/**********************************************************/
}

void HTFT_vWriteData(u8 Cpy_u8Data)
{
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_11, GPIO_HIGH);
	SPI1_u16Transceive(Cpy_u8Data);
}

void HTFT_vWriteCmd(u8 Cpy_u8Cmd)
{
	MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_11, GPIO_LOW);
	SPI1_u16Transceive(Cpy_u8Cmd);
}

void HTFT_vDisplay(const u16 *Cpy_u16Image)
{
	u32 Counter = 0;
/* Set X axis (have parameter) */
	HTFT_vWriteCmd(0x2A);

	HTFT_vWriteData(0);
	HTFT_vWriteData(0);

	HTFT_vWriteData(0);
	HTFT_vWriteData(127);

/* Set Y axis (have parameter) */
	HTFT_vWriteCmd(0x2B);

	HTFT_vWriteData(0);
	HTFT_vWriteData(0);

	HTFT_vWriteData(0);
	HTFT_vWriteData(159);

/* Write on RAM */
	HTFT_vWriteCmd(0x2C);

/* Display Data */
	for(Counter = 0; Counter<20480; Counter++)
	{
		u8 High_Pixel = (u8)(~Cpy_u16Image[Counter]>>8);
		u8 Low_Pixel = (u8)(~Cpy_u16Image[Counter]);

		HTFT_vWriteData(High_Pixel);
		HTFT_vWriteData(Low_Pixel);
	}
}
