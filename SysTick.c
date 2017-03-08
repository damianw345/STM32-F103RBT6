/*
 * Description
 *
 *To use delay function choose TIME_BASE and
 *Initialize_SysTick()
 */

#include "SysTick.h"

//extern volatile uint16_t RPS_A ;
//extern volatile uint16_t RPS_B ;				//NIE USUWAC
//
//extern volatile uint8_t i ;
//extern volatile uint16_t tmpA1 ;
//extern volatile uint16_t tmpA2 ;
//extern volatile uint16_t tmpB1 ;
//extern volatile uint16_t tmpB2 ;

void Initialize_SysTick()
{
#ifdef TIME_BASE_ms
	//interrupt every 1ms
	SysTick_Config(SystemCoreClock / 1000);
#endif

#ifdef TIME_BASE_us
	//interrupt every 1us
	SysTick_Config(SystemCoreClock / 1000000);
#endif

#ifdef TIME_BASE_10ms
	//interrupt every 10ms
	SysTick_Config(SystemCoreClock / 100);
#endif
}

/*Initialize_SysTick() and uncomment to use delay function*/
//void SysTick_Handler()
//{
//	if (timer)
//		timer--;
//}
//
void delay(uint32_t time)
{
	timer = time;
while (timer);
}
