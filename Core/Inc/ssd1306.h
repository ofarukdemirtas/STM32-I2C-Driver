#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>

// OLED I2C Address
#define OLED_ADDRESS 0x3C

// Function Declarations

void OLED_Init(void);

void OLED_WriteCommand(uint8_t command);


void OLED_WriteData(uint8_t data);


void OLED_Clear(void);


void OLED_SetCursor(uint8_t x, uint8_t y);

void OLED_WriteChar(char c);


void OLED_DisplayOn(void);

void OLED_DisplayOff(void);

#endif // OLED_SSD1306_H
