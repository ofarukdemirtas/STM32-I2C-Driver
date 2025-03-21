/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000 // 180 Mhz
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000 // 8MHz
  *            PLL_M                          = 4
  *            PLL_N                          = 180
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************

	1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set

	********************************************************/

#include "stm32f4xx.h"                  // Device header
#include "stm32f446xx.h"


void SysClockConfig (void)
{
	
	#define PLL_M 	4
	#define PLL_N 	180
	#define PLL_P 	0  /* PLLP = 2
												00: PLLP = 2
												01: PLLP = 4
												10: PLLP = 6
												11: PLLP = 8*/
	

		// 1. ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= 1<<16;                       	//RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & (1<<17)));							//while(!(RCC->CR &	RCC_CR_HSERDY));
	
		// 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR		
	
	RCC->APB1ENR |= 1<<28;                    //RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= 3<<14;                        //PWR->CR |= PWR_CR_VOS;
	
		// 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = (1<<8) | (1<<9)| (1<<10)| (5<<0); //Instruction Cache, Prefetch Buffer, and the Data Cache all are enabled. Also the Flash Latency is 5WS
				//	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	// 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	// AHB PR
	RCC->CFGR &= ~(1<<4);
// APB1 PR
	RCC->CFGR |= (5<<10);
// APB2 PR
	RCC->CFGR |= (4<<13);
	
		// 5. Configure the MAIN PLL
	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (1<<22);
	
		// 6. Enable the PLL and wait for it to become ready
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));
	
	// 7. Select the Clock Source and wait for it to be set
	RCC->CFGR |= (2<<0);
	while (!(RCC->CFGR & (2<<2)));
}
void SysTick_Init(void)
{
    SysTick->LOAD = 180000 - 1; // 180 MHz / 1000 = 1 ms
    SysTick->VAL = 0;
    SysTick->CTRL = (1 << 0) | (1 << 2); // Enable SysTick, clock source = processor clock
}

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        while (!(SysTick->CTRL & (1 << 16))); // Count flag'ı bekle
    }
}
