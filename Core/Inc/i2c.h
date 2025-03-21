#ifndef STM32_I2C_H
#define STM32_I2C_H

#include "stm32f4xx.h"
#include <stdint.h>

#define I2C_TIMEOUT 10000

void I2C1_Init(void);
void I2C1_Start(uint8_t address, uint8_t direction);
void I2C1_Stop(void);
void I2C1_Write(uint8_t data);
void I2C1_WriteMultiple(uint8_t *data, uint16_t size);

#endif // STM32_I2C_H

