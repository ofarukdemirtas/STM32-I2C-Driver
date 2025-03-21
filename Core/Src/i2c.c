#include "stm32f4xx.h"

#define I2C_TIMEOUT 10000

void I2C1_Init(void) {
    // Enable required clocks for I2C1
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;  // Enable I2C1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB clock

    // Configure GPIOB Pin 8 (SCL) and Pin 9 (SDA) for Alternate Function
    GPIOB->MODER &= ~((3 << (8 * 2)) | (3 << (9 * 2))); // Clear mode bits
    GPIOB->MODER |= (2 << (8 * 2)) | (2 << (9 * 2));    // Set alternate function mode

    GPIOB->OTYPER |= (1 << 8) | (1 << 9);               // Set open-drain configuration
    GPIOB->OSPEEDR |= (3 << (8 * 2)) | (3 << (9 * 2));  // Set high speed
    GPIOB->PUPDR |= (1 << (8 * 2)) | (1 << (9 * 2));    // Enable pull-up resistors
    GPIOB->AFR[1] |= (4 << (0 * 4)) | (4 << (1 * 4));   // Set AF4 (I2C1) for PB8 and PB9

    // I2C1 configuration
    I2C1->CR1 &= ~I2C_CR1_PE;             // Disable I2C before configuration
    I2C1->CR2 = (45 & I2C_CR2_FREQ_Msk);  // Set APB1 clock frequency (45 MHz)
    I2C1->CCR = 225;                      // Set clock control register for 100kHz in Standard mode
    I2C1->TRISE = 46;                     // Set maximum rise time
    I2C1->CR1 |= I2C_CR1_PE;              // Enable I2C peripheral
}

void I2C1_Start(uint8_t address, uint8_t direction) {
    I2C1->CR1 |= I2C_CR1_START;           // Generate start condition
    while (!(I2C1->SR1 & I2C_SR1_SB));    // Wait until start bit is set

    I2C1->DR = (address << 1) | direction; // Send slave address and direction bit R/W
    while (!(I2C1->SR1 & I2C_SR1_ADDR));   // Wait until address flag is set
    (void)I2C1->SR2;                       // Read SR2 to clear the address flag
}

void I2C1_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;            // Generate stop condition
}

void I2C1_Write(uint8_t data) {
    while (!(I2C1->SR1 & I2C_SR1_TXE));   // Wait until data register is empty
    I2C1->DR = data;                       // Write data to the data register
    while (!(I2C1->SR1 & I2C_SR1_BTF));    // Wait until byte transfer is finished
}

void I2C1_WriteMultiple(uint8_t *data, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        I2C1_Write(data[i]);               // Write each byte in the array
    }
}
