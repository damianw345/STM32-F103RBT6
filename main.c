/********************************************PROGRAM G£ÓWNY****************************************/
#include "main.h"

/*extern variables*/
extern uint16_t distance[4];
extern volatile uint16_t RPS_A;
extern volatile uint16_t RPS_B;
extern uint16_t adc_value[3];

float temp_amb =0;
float temp_object=0;

int main(void)
{
	/*Initialize necessary STM32 modules*/
	Initialize_GPIO_RCC();
	Initialize_AFIO_RCC();
	Initialize_NVIC();//interrupts' priorities
	Initialize_ADC();//for CNY70
	Initialize_DMA();//for CNY70

	/*Initialize utils*/
	Initialize_UART();//for MAESTRO SERVO CONTROLLER and BLE
	Initialize_LED();

	/*Initialize peripherals*/
	Initialize_SMBus();//for MLX90615
	Initialize_HCSR04();
	Initialize_HBridge();
	Initialize_Encoders();

	while(1)
	{
		temp_amb = MLX90615_ReadAmbientTemp();
		temp_object = MLX90615_ReadObjectTemp();
		HCSR04_CalculateDist();

		BLE_executeIfTransferIsComplete();
	}
}
