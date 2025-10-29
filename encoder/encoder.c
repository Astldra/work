#include "encoder.h"

void ENC_Init(ENC_Typedef *enc,TIM_HandleTypeDef *htim){
	enc->enc_tim = htim;
	HAL_TIM_Encoder_Start(enc->enc_tim,TIM_CHANNEL_ALL);
	ENC_clear(enc);
}

void ENC_Get(ENC_Typedef *enc){
	enc->encoder = __HAL_TIM_GET_COUNTER(enc->enc_tim);
}

void ENC_Set(ENC_Typedef *enc,int cnt){
	enc->encoder = cnt;
}

void ENC_clear(ENC_Typedef *enc){
	enc->encoder = 0;
	enc->speed = 0;
}

