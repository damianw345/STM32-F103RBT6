/*
 * mlx90615.h
 *
 *  Created on: 8 gru 2016
 *      Author: samsung
 */

#ifndef MLX90615_H_
#define MLX90615_H_

#define MLX90615_ADDRESS    	0x5B
#define MLX_AMB_TEMP_CMD		0x26
#define MLX_OBJ_TEMP_CMD		0x27

float MLX90615_ReadAmbientTemp(void);
float MLX90615_ReadObjectTemp(void);
//float MLX90615_ReadInt(void);

#endif /* MLX90615_H_ */
