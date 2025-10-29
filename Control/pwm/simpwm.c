#include "simpwm.h"

void SIMPWM_Init(
	PWM_Typedef *motor,
	uint16_t ccr1,
	uint16_t ccr2,
	GPIO_TypeDef *GPIOx1,
	uint16_t GPIO_Pin1,
	GPIO_TypeDef *GPIOx2,
	uint16_t GPIO_Pin2
	){
	HAL_TIM_Base_Start(PWM_TIM);
	motor->ccr1 = ccr1;
	motor->ccr2 = ccr2;
	motor->GPIOx1 = GPIOx1;
	motor->GPIO_Pin1 = GPIO_Pin1;
	motor->GPIOx2 = GPIOx2;
	motor->GPIO_Pin2 = GPIO_Pin2;
}
void SIMPWM_SET_CRR(PWM_Typedef *motor,uint16_t ccr1,uint16_t ccr2){
	motor->ccr1 = ccr1;
	motor->ccr2 = ccr2;
}
void SIMPWM_Run(PWM_Typedef *motor,uint16_t cnt){
	if(motor->ccr1 > cnt){
		HAL_GPIO_WritePin(motor->GPIOx1,motor->GPIO_Pin1,GPIO_PIN_SET);
	}else if(motor->ccr1 <= cnt){
		HAL_GPIO_WritePin(motor->GPIOx1,motor->GPIO_Pin1,GPIO_PIN_RESET);
	}
	if(motor->ccr2 > cnt){
		HAL_GPIO_WritePin(motor->GPIOx2,motor->GPIO_Pin2,GPIO_PIN_SET);
	}else if(motor->ccr2 <= cnt){
		HAL_GPIO_WritePin(motor->GPIOx2,motor->GPIO_Pin2,GPIO_PIN_RESET);
	}
}