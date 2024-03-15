/*
 * APP.c
 *
 *  Created on: 14 Mar 2024
 *      Author: Ahmed Samy
 */

#include "STD_Types.h"
#include "BIT_Math.h"

#include "MRCC_interface.h"
#include "MGPIO_int.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "SPI_interface.h"
#include "SYSTICK_interface.h"
#include "Timer2_interface.h"
#include "Timer3_interface.h"

#include "APP.h"
#include "HTFT_int.h"
#include "R2RDAC_INTERFACE.h"
#include "STP_interface.h"
#include "Image.h"
#include "elevator.h"

/*Global Variables*/
volatile u8 u8StartFlag = 0;
volatile u32 u32FrameData[50] = {0};
volatile u8 u8EdgeCounter = 0;
volatile u8 u8Data = 0;
u8 ReachValue = 0;
u8 CurrentFloor = 0;
u8 OrderedFloor = 0;

void App_Init(void)
{
	MRCC_vInt();
	MRCC_vEnable(RCC_AHB1, AHB1_GPIOA);
	MRCC_vEnable(RCC_AHB1,AHB1_GPIOB);
	MRCC_vEnable(RCC_APB2, APB2_SPI1);
	MRCC_vEnable(RCC_APB2, APB2_SYSCFG);
	MRCC_vEnable(RCC_APB1,APB1_TIM2);
	MRCC_vEnable(RCC_APB1,APB1_TIM3);

	R2RDAC_Init();

	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_4, ALT_FUNCTION);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_5, ALT_FUNCTION);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_6, ALT_FUNCTION);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_7, ALT_FUNCTION);

	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_5,PUSH_PULL,LOW_SPEED);
	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_7,PUSH_PULL,LOW_SPEED);
	MGPIO_VOIDsetInputMode(PORT_A,GPIO_PIN_NUM_4,PULLUP);

	MGPIO_VOIDSetaltFun(PORT_A,GPIO_PIN_NUM_4,ALT_SPI1);
	MGPIO_VOIDSetaltFun(PORT_A,GPIO_PIN_NUM_5,ALT_SPI1);
	MGPIO_VOIDSetaltFun(PORT_A,GPIO_PIN_NUM_6,ALT_SPI1);
	MGPIO_VOIDSetaltFun(PORT_A,GPIO_PIN_NUM_7,ALT_SPI1);

	/* IO Pins Initialization */
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_1,OUTPUT);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_2,OUTPUT);
	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_3,OUTPUT);

	MGPIO_VOIDsetMode(PORT_A,GPIO_PIN_NUM_0,INPUT);
	MGPIO_VOIDsetInputMode(PORT_A,GPIO_PIN_NUM_0,PULLUP);

	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_1,PUSH_PULL,LOW_SPEED);
	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_2,PUSH_PULL,LOW_SPEED);
	MGPIO_VOIDsetOutputMode(PORT_A,GPIO_PIN_NUM_3,PUSH_PULL,LOW_SPEED);


	/* SysTick Init */
	MSYSYTICK_voidInit();

	/* SPI & TFT Init */
	SPI1_voidInit();
	HTFT_vInit();

	/* Timer2 & S2P Init */
	TIM2_voidInit();
	TIM3_voidInit();

	S2P_vInit();

	/* EXTI Initializtion */
	MEXTI_voidInerruptSetPort(EXTI_LineZero ,EXTI_PortA);
	MEXTI0_voidCallBack(voidGetFrame);
	MEXTI_voidInterruptEnableDisable(EXTI_LineZero,EXTI_Enable) ;
	MEXTI_voidInterruptTrigger(EXTI_LineZero,EXTI_Falling) ;

	NVIC_VoidSetInterruptGroupMode(Group16Sub0);
	NVIC_VoidSetInterruptPriority(6,0,0);
	NVIC_VoidSetInterruptPriority(29,1,0);
	NVIC_VoidSetInterruptPriority(30,1,0);
	NVIC_vEnable(28);
	NVIC_vEnable(29);
	NVIC_vEnable(30);
	/* Enable EXTI0 from NVIC */
	NVIC_vEnable(6);
	/* Enable Systick Interrupt */
	MSYSYTICK_voidCtrlIntState(SYSTICKEnable);
	CurrentFloor = 1;
	HTFT_vDisplay(u16Image_1);
}

void voidPlay(void)
{
	switch (u8Data)
	{
	case 12:
		OrderedFloor = 1;
		if(CurrentFloor > OrderedFloor)
		{
			ReachValue = 1;
			TIM3_voidSetIntervalPeriodic(40000, LEDMatrix_DOWN);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_HIGH);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			R2RDAC_SetData(elevator_raw,68174);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_1);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			CurrentFloor = 1;
		}
		else
		{
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_1);
			CurrentFloor = 1;
		}
		break;
	case 24:
		OrderedFloor = 2;
		if(CurrentFloor > OrderedFloor)
		{
			ReachValue = 1;
			TIM3_voidSetIntervalPeriodic(40000, LEDMatrix_DOWN);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_HIGH);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			R2RDAC_SetData(elevator_raw,68174);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_2);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			CurrentFloor = 2;
		}
		else if(CurrentFloor < OrderedFloor)
		{
			ReachValue = 1;
			TIM3_voidSetIntervalPeriodic(40000, LEDMatrix_UP);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_HIGH);
			R2RDAC_SetData(elevator_raw,68174);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_2);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			CurrentFloor = 2;
		}
		else
		{
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_2);
			CurrentFloor = 2;
		}
		break;
	case 94:
		OrderedFloor = 3;
		if(CurrentFloor < OrderedFloor)
		{
			ReachValue = 1;
			TIM3_voidSetIntervalPeriodic(40000, LEDMatrix_UP);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_HIGH);
			R2RDAC_SetData(elevator_raw,68174);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_3);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			CurrentFloor = 3;
		}
		else
		{
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_1,GPIO_LOW);
			MGPIO_VOIDWritePin(PORT_A,GPIO_PIN_NUM_2,GPIO_LOW);
			ReachValue = 2;
			HTFT_vDisplay(u16Image_3);
			CurrentFloor = 3;
		}
		break ;
	}
}

void voidTakeAction(void)
{
	/*
	if(u8EdgeCounter == 1 )
	{
		asm("NOP");
	}
	 */

	u8 i;
	u8Data = 0;

	if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 15000) )
	{
		for (i=0;i<8;i++)
		{
			if (  (u32FrameData[17+i] >= 2000) && (u32FrameData[17+i] <=2300) )
			{
				SET_BIT(u8Data,i);
			}

			else
			{
				CLR_BIT(u8Data,i);
			}
		}

		voidPlay();
	}

	else
	{
		/*	 Invalid Frame */
	}

	u8StartFlag     = 0;
	u32FrameData[0] = 0;
	u8EdgeCounter   = 0;
}

void voidGetFrame(void)
{
	if (u8StartFlag == 0)
	{
		/* Start Timer */
		MSTK_voidSetInterval_single(100000,voidTakeAction);
		u8StartFlag = 1;
	}

	else
	{
		u32FrameData[u8EdgeCounter] = ( MSTK_u32GetElapsedTime() / 2 );
		MSTK_voidSetInterval_single(100000,voidTakeAction);
		u8EdgeCounter++;
	}
	if(u8EdgeCounter == 50)
	{
		asm("NOP");
	}

}

void LEDMatrix_UP(void)
{
	//UP ARROW
	if(ReachValue == 1)
	{
		S2P_vSendData(0xFE08);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xFD04);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xFB06);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xF7FF);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xEFFF);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xDF06);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xBF04);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0x7F08);
		TIM2_voidSetBusyWait(1);
	}
	else if(ReachValue == 2)
	{
		S2P_vSendData(0x0000);
	}
}

void LEDMatrix_DOWN(void)
{
	//Down Arrow
	if(ReachValue == 1)
	{
		S2P_vSendData(0xFE10);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xFD20);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xFB60);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xF7FF);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xEFFF);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xDF60);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0xBF20);
		TIM2_voidSetBusyWait(1);
		S2P_vSendData(0x7F10);
		TIM2_voidSetBusyWait(1);
	}
	else if(ReachValue == 2)
	{
		S2P_vSendData(0x0000);
	}
}
