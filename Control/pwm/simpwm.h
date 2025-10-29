#ifndef _SIMPWM_H_
#define _SIMPWM_H_

#include "tim.h"
#include "gpio.h"
#define PWM_TIM &htim6

typedef struct{
	uint16_t ccr1;
	uint16_t ccr2;
	GPIO_TypeDef *GPIOx1;
	uint16_t GPIO_Pin1;
	GPIO_TypeDef *GPIOx2;
	uint16_t GPIO_Pin2;
}PWM_Typedef;

void SIMPWM_Init(
	PWM_Typedef *motor,
	uint16_t ccr1,
	uint16_t ccr2,
	GPIO_TypeDef *GPIOx1,
	uint16_t GPIO_Pin1,
	GPIO_TypeDef *GPIOx2,
	uint16_t GPIO_Pin2
	);
void SIMPWM_SET_CRR(PWM_Typedef *motor,uint16_t ccr1,uint16_t ccr2);
void SIMPWM_Run(PWM_Typedef *motor,uint16_t cnt);
#endif