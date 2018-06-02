//
// Created by legath on 26.04.18.
//

#include "fsmc.h"
/* FSMC initialization function */
SRAM_HandleTypeDef hsram1;
void FSMC_Init(void)
{
    __HAL_RCC_FSMC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);



    FSMC_NORSRAM_TimingTypeDef Timing;

    /** Perform the SRAM1 memory initialization sequence
    */
    hsram1.Instance = FSMC_NORSRAM_DEVICE;
    hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    /* hsram1.Init */
    hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
    hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
    hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
    hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
    hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
    hsram1.Init.PageSize = FSMC_PAGE_SIZE_NONE;
    /* Timing */
    Timing.AddressSetupTime = 10;
    Timing.AddressHoldTime = 1;
    Timing.DataSetupTime = 15;
    Timing.BusTurnAroundDuration = 0;
    Timing.CLKDivision = 0;
    Timing.DataLatency = 0;
    Timing.AccessMode = FSMC_ACCESS_MODE_B;
    /* ExtTiming */

    if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }

}
void Lcd_Write_Cmd(uint16_t index)
{
    *(uint16_t *) (LCD_REG) = index;
}
////////////////////////
void Lcd_Write_Data(uint16_t data)
{
    *(uint16_t *) (LCD_DATA)= data;
}
///////////////////
uint16_t Lcd_Read_Data()
{
    uint16_t data = * (uint16_t *)(LCD_DATA);
    return data;
}
////////////////////////
uint16_t Lcd_Read_Reg(uint16_t reg_addr)
{
    volatile uint16_t data = 0;
    Lcd_Write_Cmd(reg_addr);
    data = Lcd_Read_Data();
    return data;
}
///////////////////////
void Lcd_Write_Reg(uint16_t reg,uint16_t value)
{
    *(uint16_t *) (LCD_REG) = reg;
    *(uint16_t *) (LCD_DATA) = value;
}

void LCD_ReadId(){
    uint16_t  test[4];
    Lcd_Write_Cmd(0xD3);
    test[0]=Lcd_Read_Data();
    test[1]=Lcd_Read_Data();
    test[2]=Lcd_Read_Data();
    test[3]=Lcd_Read_Data();
    asm("nop");
}
void LCD_ReadId1(){
    uint16_t  test[5];
    Lcd_Write_Cmd(0xC7);
    test[0]=Lcd_Read_Data();
    test[1]=Lcd_Read_Data();
    test[2]=Lcd_Read_Data();
    test[3]=Lcd_Read_Data();
    test[4]=Lcd_Read_Data();
    asm("nop");
}
void LCD_Init()
{

    Lcd_Write_Cmd(0xFF); // EXTC Command Set enable register
    Lcd_Write_Data(0xFF);
    Lcd_Write_Data(0x98);
    Lcd_Write_Data(0x06);

    Lcd_Write_Cmd(0xBA); // SPI Interface Setting
    Lcd_Write_Data(0xE0);

    Lcd_Write_Cmd(0xBC); // GIP 1
    Lcd_Write_Data(0x03);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0x63);
    Lcd_Write_Data(0x69);
    Lcd_Write_Data(0x01);
    Lcd_Write_Data(0x01);
    Lcd_Write_Data(0x1B);
    Lcd_Write_Data(0x11);
    Lcd_Write_Data(0x70);
    Lcd_Write_Data(0x73);
    Lcd_Write_Data(0xFF);
    Lcd_Write_Data(0xFF);
    Lcd_Write_Data(0x08);
    Lcd_Write_Data(0x09);
    Lcd_Write_Data(0x05);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0xEE);
    Lcd_Write_Data(0xE2);
    Lcd_Write_Data(0x01);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0xC1);

    Lcd_Write_Cmd(0xBD); // GIP 2
    Lcd_Write_Data(0x01);
    Lcd_Write_Data(0x23);
    Lcd_Write_Data(0x45);
    Lcd_Write_Data(0x67);
    Lcd_Write_Data(0x01);
    Lcd_Write_Data(0x23);
    Lcd_Write_Data(0x45);
    Lcd_Write_Data(0x67);

    Lcd_Write_Cmd(0xBE); // GIP 3
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x22);
    Lcd_Write_Data(0x27);
    Lcd_Write_Data(0x6A);
    Lcd_Write_Data(0xBC);
    Lcd_Write_Data(0xD8);
    Lcd_Write_Data(0x92);
    Lcd_Write_Data(0x22);
    Lcd_Write_Data(0x22);

    Lcd_Write_Cmd(0xC7); // Vcom
    Lcd_Write_Data(0x1E);

    Lcd_Write_Cmd(0xED); // EN_volt_reg
    Lcd_Write_Data(0x7F);
    Lcd_Write_Data(0x0F);
    Lcd_Write_Data(0x00);

    Lcd_Write_Cmd(0xC0); // Power Control 1
    Lcd_Write_Data(0xE3);
    Lcd_Write_Data(0x0B);
    Lcd_Write_Data(0x00);

    Lcd_Write_Cmd(0xFC);
    Lcd_Write_Data(0x08);

    Lcd_Write_Cmd(0xDF); // Engineering Setting
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x02);

    Lcd_Write_Cmd(0xF3); // DVDD Voltage Setting
    Lcd_Write_Data(0x74);

    Lcd_Write_Cmd(0xB4); // Display Inversion Control
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);

    Lcd_Write_Cmd(0xF7); // 480x854
    Lcd_Write_Data(0x81);

    Lcd_Write_Cmd(0xB1); // Frame Rate
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x10);
    Lcd_Write_Data(0x14);

    Lcd_Write_Cmd(0xF1); // Panel Timing Control
    Lcd_Write_Data(0x29);
    Lcd_Write_Data(0x8A);
    Lcd_Write_Data(0x07);

    Lcd_Write_Cmd(0xF2); //Panel Timing Control
    Lcd_Write_Data(0x40);
    Lcd_Write_Data(0xD2);
    Lcd_Write_Data(0x50);
    Lcd_Write_Data(0x28);

    Lcd_Write_Cmd(0xC1); // Power Control 2
    Lcd_Write_Data(0x17);
    Lcd_Write_Data(0X85);
    Lcd_Write_Data(0x85);
    Lcd_Write_Data(0x20);

    Lcd_Write_Cmd(0xE0);
    Lcd_Write_Data(0x00); //P1
    Lcd_Write_Data(0x0C); //P2
    Lcd_Write_Data(0x15); //P3
    Lcd_Write_Data(0x0D); //P4
    Lcd_Write_Data(0x0F); //P5
    Lcd_Write_Data(0x0C); //P6
    Lcd_Write_Data(0x07); //P7
    Lcd_Write_Data(0x05); //P8
    Lcd_Write_Data(0x07); //P9
    Lcd_Write_Data(0x0B); //P10
    Lcd_Write_Data(0x10); //P11
    Lcd_Write_Data(0x10); //P12
    Lcd_Write_Data(0x0D); //P13
    Lcd_Write_Data(0x17); //P14
    Lcd_Write_Data(0x0F); //P15
    Lcd_Write_Data(0x00); //P16

    Lcd_Write_Cmd(0xE1);
    Lcd_Write_Data(0x00); //P1
    Lcd_Write_Data(0x0D); //P2
    Lcd_Write_Data(0x15); //P3
    Lcd_Write_Data(0x0E); //P4
    Lcd_Write_Data(0x10); //P5
    Lcd_Write_Data(0x0D); //P6
    Lcd_Write_Data(0x08); //P7
    Lcd_Write_Data(0x06); //P8
    Lcd_Write_Data(0x07); //P9
    Lcd_Write_Data(0x0C); //P10
    Lcd_Write_Data(0x11); //P11
    Lcd_Write_Data(0x11); //P12
    Lcd_Write_Data(0x0E); //P13
    Lcd_Write_Data(0x17); //P14
    Lcd_Write_Data(0x0F); //P15
    Lcd_Write_Data(0x00); //P16

    Lcd_Write_Cmd(0x35); //Tearing Effect ON
    Lcd_Write_Data(0x00);

    Lcd_Write_Cmd(0x36);
    Lcd_Write_Data(0x60);

    Lcd_Write_Cmd(0x3A);
    Lcd_Write_Data(0x55);

    Lcd_Write_Cmd(0x11); //Exit Sleep
    HAL_Delay(120);
    Lcd_Write_Cmd(0x29); // Display On
    HAL_Delay(10);

    Lcd_Write_Cmd(0x3A);
    Lcd_Write_Data(0x55);
    Lcd_Write_Cmd(0x36);
    Lcd_Write_Data(0x0); // portrait, RGB


}
void writeData16(uint16_t d, uint32_t num)
{
    while (num > 0)
    {
        Lcd_Write_Data(d);
        num--;
    }
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{

    setWindowAddress(x, y, x + w - 1, y + h - 1);
    writeData16(color, w * h);

}
void fillPixel(int16_t x, int16_t y,  uint16_t color)
{

    setWindowAddress(x, y, x , y );
    Lcd_Write_Data(color);

}

void setWindowAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    Lcd_Write_Cmd(CASET);  // Column addr set
    Lcd_Write_Data(x0 >> 8);
    Lcd_Write_Data(x0 & 0xFF); // XSTART
    Lcd_Write_Data(x1 >> 8);
    Lcd_Write_Data(x1 & 0xFF); // XEND
    Lcd_Write_Cmd(PASET);  // Row addr set
    Lcd_Write_Data(y0 >> 8);
    Lcd_Write_Data(y0);        // YSTART
    Lcd_Write_Data(y1 >> 8);
    Lcd_Write_Data(y1);        // YEND
    Lcd_Write_Cmd(RAMWR);  // write to RAM
}

void setRotation(uint8_t r)
{

    Lcd_Write_Cmd(MADCTL);
    switch (r & 3)
    {
        case 0:
            Lcd_Write_Data(0);
            break;
        case 1:
            Lcd_Write_Data(MADCTL_MX | MADCTL_MV);
            break;
        case 2:
            Lcd_Write_Data(MADCTL_MX | MADCTL_MY);
            break;
        case 3:
            Lcd_Write_Data(MADCTL_MY | MADCTL_MV);
            break;
    }

}
//reportRegister(0xD3, 4, "Device Code ILI9806");
//reportRegister(0x04, 4, "Manufacturer ID");
//reportRegister(0x09, 5, "Status Register");
//reportRegister(0x0A, 2, "Power Mode");
//reportRegister(0x0B, 2, "MADCTL");
//reportRegister(0x0C, 2, "Pixel Format");
//reportRegister(0x54, 2, "Display CTRL");
//reportRegister(0x54, 2, "Display CABC");