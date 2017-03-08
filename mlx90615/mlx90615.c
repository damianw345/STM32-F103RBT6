#include <stdio.h>
#include <stm32f10x_gpio.h>
#include "mlx90615/smbus.h"
#include "mlx90615/mlx90615.h"

float MLX90615_ReadAmbientTemp(void)
{
	uint16_t tmp = 0;
	smbusRead(I2C2,MLX90615_ADDRESS,MLX_AMB_TEMP_CMD, &tmp);
	float res =  tmp * 0.02 -273.15;
	return res;
}

float MLX90615_ReadObjectTemp(void)
{
	uint16_t tmp = 0;
	smbusRead(I2C2,MLX90615_ADDRESS,MLX_OBJ_TEMP_CMD, &tmp);
	float res =  tmp * 0.02 -273.15;
	return res;
}

//float MLX90615_ReadInt(void)
//{
//	uint16_t tmp = 0;
////	smbusRead(I2C2,MLX90615_ADDRESS,MLX_OBJ_TEMP_CMD, &tmp);
//	float res =  data * 0.02 -273.15;
//	return res;
//}
