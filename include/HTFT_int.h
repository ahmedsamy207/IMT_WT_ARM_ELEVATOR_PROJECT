/*
 * HTFT_int.h
 *
 *  Created on: 5 Feb 2024
 *      Author: Ahmed Samy
 */

#ifndef HTFT_INT_H_
#define HTFT_INT_H_

void HTFT_vInit(void);
void HTFT_vWriteData(u8 Cpy_u8Data);
void HTFT_vWriteCmd(u8 Cpy_u8Cmd);
void HTFT_vDisplay(const u16 *Cpy_u16Image);

#endif /* HTFT_INT_H_ */
