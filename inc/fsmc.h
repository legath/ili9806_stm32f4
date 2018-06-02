//
// Created by legath on 26.04.18.
//

#ifndef _FSMC_H
#define _FSMC_H

#include "stdint.h"
#include "stm32f4xx_hal.h"


// Color definitions
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK 0xF81F

#define ADDR_CMD        *(uint8_t*)0x60000000

#define ADDR_DATA        *(uint8_t*)0x60010000

#define CASET 0x2A
#define PASET 0x2B
#define RAMWR 0x2C
#define RAMRD 0x2E
#define MADCTL 0x36
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_SS  0x02
#define MADCTL_GS 0x01


void FSMC_Init(void);
void LCD_Init();
void LCD_ReadId();
void LCD_ReadId1();
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
void setWindowAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void setRotation(uint8_t r);
#endif //_FSMC_H
