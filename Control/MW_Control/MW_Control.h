#ifndef _MW_CONTROL_H
#define _MW_CONTROL_H

#include "bt_control.h"

#define MAX_SPEED 100

#define MORTOR_A1 &htim15
#define MORTOR_A1_IN1 TIM_CHANNEL_1
#define MORTOR_A1_IN2 TIM_CHANNEL_2

#define MORTOR_A2 &htim4
#define MORTOR_A2_IN1 TIM_CHANNEL_3
#define MORTOR_A2_IN2 TIM_CHANNEL_4

#define MORTOR_B1 &htim3
#define MORTOR_B1_IN1 TIM_CHANNEL_3
#define MORTOR_B1_IN2 TIM_CHANNEL_4

#define MORTOR_B2 &htim2
#define MORTOR_B2_IN1 TIM_CHANNEL_3
#define MORTOR_B2_IN2 TIM_CHANNEL_4

void MW_Init();
void MW_Control(Bt_Data_Typedef mw_data);

#endif