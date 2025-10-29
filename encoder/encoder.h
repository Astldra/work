#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "tim.h"

#define ECD_A1 &htim1
#define ECD_A2 &htim4
#define ECD_B1 &htim3
#define ECD_B2 &htim2

typedef struct{
	TIM_HandleTypeDef *enc_tim;
	int encoder;
	float speed;
}ENC_Typedef;

void ENC_Init(ENC_Typedef *enc,TIM_HandleTypeDef *htim);
void ENC_Set(ENC_Typedef *enc,int cnt);
void ENC_clear(ENC_Typedef *enc);
void ENC_Get(ENC_Typedef *enc);
#endif