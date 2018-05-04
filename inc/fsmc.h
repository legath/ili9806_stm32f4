//
// Created by legath on 26.04.18.
//

#ifndef _FSMC_H
#define _FSMC_H

#include "stdint.h"
#include "stm32f4xx_hal.h"

#define ADDR_CMD        *(uint8_t*)0x60000000

#define ADDR_DATA        *(uint8_t*)0x60010000


void FSMC_Init(void);
void LCD_Init();
void LCD_ReadId();
// Определяем адреса
// для записи данных
#define LCD_DATA 0x60020000
// для записи команд
#define LCD_REG 0x60000000

void Lcd_Write_Cmd(uint16_t index);
void Lcd_Write_Data(uint16_t data);
uint16_t Lcd_Read_Data();
uint16_t Lcd_Read_Reg(uint16_t reg_addr);
void Lcd_Write_Reg(uint16_t reg,uint16_t value);
#endif //_FSMC_H
