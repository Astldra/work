#include "tim.h"
#include "MW_Control.h"
#include "bt_control.h"
#include "math.h"
#include "pid.h"
extern PID_Typedef pidA1,pidA2,pidB1,pidB2;
/*
麦轮小车左前轮与右后轮为A轮组
右前轮和左后轮为B轮组
*/

//void MW_Init(){
//	HAL_TIM_PWM_Start(MORTOR_A1,MORTOR_A1_IN1);
//	HAL_TIM_PWM_Start(MORTOR_A1,MORTOR_A1_IN2);
//	HAL_TIM_Base_Start(MORTOR_A1);
//	
//	HAL_TIM_PWM_Start(MORTOR_A2,MORTOR_A2_IN1);
//	HAL_TIM_PWM_Start(MORTOR_A2,MORTOR_A2_IN2);
//	HAL_TIM_Base_Start(MORTOR_A2);
//	
//	HAL_TIM_PWM_Start(MORTOR_B1,MORTOR_B1_IN1);
//	HAL_TIM_PWM_Start(MORTOR_B1,MORTOR_B1_IN2);
//	HAL_TIM_Base_Start(MORTOR_B1);

//	HAL_TIM_PWM_Start(MORTOR_B2,MORTOR_B2_IN1);
//	HAL_TIM_PWM_Start(MORTOR_B2,MORTOR_B2_IN2);
//	HAL_TIM_Base_Start(MORTOR_B2);
//}
//void MW_Control(Bt_Data_Typedef mw_data){
//	if(mw_data.turn == No){																//全向移动
//		int vA = (mw_data.y + mw_data.x) * 10;
//		int vB = (mw_data.y - mw_data.x) * 10;
//		if(vA >= 0){
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN1,vA);
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN2,0);

//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN1,vA);
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN2,0);
//		}else{
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN2,-vA);

//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN2,-vA);
//		}
//		if(vB >= 0){
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN1,vB);
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN2,0);

//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN1,vB);
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN2,0);
//		}else{
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN2,-vB);

//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN2,-vB);
//		}
//	}else{																								//原地旋转
//		if(mw_data.turn == LEFT){
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN2,MAX_SPEED*7/10);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN1,MAX_SPEED*7/10);
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN2,0);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN1,MAX_SPEED*7/10);
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN2,0);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN2,MAX_SPEED*7/10);
//		}
//		if(mw_data.turn == RIGHT){
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN1,MAX_SPEED*7/10);
//			__HAL_TIM_SET_COMPARE(MORTOR_A1,MORTOR_A1_IN2,0);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_A2,MORTOR_A2_IN2,MAX_SPEED*7/10);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN1,0);
//			__HAL_TIM_SET_COMPARE(MORTOR_B1,MORTOR_B1_IN2,MAX_SPEED*7/10);
//			
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN1,MAX_SPEED*7/10);
//			__HAL_TIM_SET_COMPARE(MORTOR_B2,MORTOR_B2_IN2,0);
//		}
//	}
//}

//#include "simpwm.h"
//extern PWM_Typedef motorA1,motorA2,motorB1,motorB2;
//void MW_Control(Bt_Data_Typedef mw_data){
//	if(mw_data.turn == No){																//全向移动
//		float x = mw_data.x;
//		float y = mw_data.y;
//		float d = sqrtf(powf(mw_data.x,2)+powf(mw_data.y,2));
//		if(d > 10.0f){
//			y = mw_data.y * 10.0f / d;
//			x = mw_data.x * 10.0f / d;
//		}
//		float vA = (y + x) * 90;
//		float vB = (y - x) * 90;
//		if(vA >= 0){
////			SIMPWM_SET_CRR(&motorA1,vA,0);
////			SIMPWM_SET_CRR(&motorA2,vA,0);
//			
//			SIMPWM_SET_CRR(&motorA1,1000,(1000 - vA) > 0 ? 1000 - vA : 1);
//			SIMPWM_SET_CRR(&motorA2,1000,(1000 - vA) > 0 ? 1000 - vA : 1);
//		}else{
//			SIMPWM_SET_CRR(&motorA1,(1000 + vA) > 0 ? 1000 + vA : 1,1000);
//			SIMPWM_SET_CRR(&motorA2,(1000 + vA) > 0 ? 1000 + vA : 1,1000);
//			
////			SIMPWM_SET_CRR(&motorA1,0,-vA);
////			SIMPWM_SET_CRR(&motorA2,0 ,-vA);
//		}
//		if(vB >= 0){
////			SIMPWM_SET_CRR(&motorB1,vB,0);
////			SIMPWM_SET_CRR(&motorB2,vB,0);
//			
//			SIMPWM_SET_CRR(&motorB1,1000,(1000 - vB) > 0 ? 1000 - vB : 1);
//			SIMPWM_SET_CRR(&motorB2,1000,(1000 - vB) > 0 ? 1000 - vB : 1);
//		}else{
////			SIMPWM_SET_CRR(&motorB1,0,-vB);
////			SIMPWM_SET_CRR(&motorB2,0,-vB);
//			
//			SIMPWM_SET_CRR(&motorB1,(1000 + vB) > 0 ? 1000 + vB : 1,1000);
//			SIMPWM_SET_CRR(&motorB2,(1000 + vB) > 0 ? 1000 + vB : 1,1000);
//		}
//	}else{																								//原地旋转
//		if(mw_data.turn == LEFT){
////			SIMPWM_SET_CRR(&motorA1,0,700);
////			SIMPWM_SET_CRR(&motorA2,700,0);
////			SIMPWM_SET_CRR(&motorB1,700,0);
////			SIMPWM_SET_CRR(&motorB2,0,700);
//			
//			SIMPWM_SET_CRR(&motorA1,300,1000);
//			SIMPWM_SET_CRR(&motorA2,1000,300);
//			SIMPWM_SET_CRR(&motorB1,1000,300);
//			SIMPWM_SET_CRR(&motorB2,300,1000);
//		}
//		if(mw_data.turn == RIGHT){
////			SIMPWM_SET_CRR(&motorA1,700,0);
////			SIMPWM_SET_CRR(&motorA2,0,700);
////			SIMPWM_SET_CRR(&motorB1,0,700);
////			SIMPWM_SET_CRR(&motorB2,700,0);
//			
//			SIMPWM_SET_CRR(&motorA1,1000,300);
//			SIMPWM_SET_CRR(&motorA2,300,1000);
//			SIMPWM_SET_CRR(&motorB1,300,1000);
//			SIMPWM_SET_CRR(&motorB2,1000,300);
//		}
//	}
//}

#include "simpwm.h"

extern PWM_Typedef motorA1,motorA2,motorB1,motorB2;
void MW_Control(Bt_Data_Typedef mw_data){
	if(mw_data.turn == No){																//全向移动
//		float x = mw_data.x;
//		float y = mw_data.y;
//		if(d > 10.0f){
//			y = mw_data.y * 10.0f / d;
//			x = mw_data.x * 10.0f / d;
//		}
		float vA = (mw_data.y + mw_data.x) * 14;
		float vB = (mw_data.y - mw_data.x) * 14;
		
		PID_Setpoint(&pidA1,vA);
		PID_Setpoint(&pidA2,vA);
		PID_Setpoint(&pidB1,vB);
		PID_Setpoint(&pidB2,vB);
	}else{																								//原地旋转
		if(mw_data.turn == LEFT){
//			SIMPWM_SET_CRR(&motorA1,0,700);
//			SIMPWM_SET_CRR(&motorA2,700,0);
//			SIMPWM_SET_CRR(&motorB1,700,0);
//			SIMPWM_SET_CRR(&motorB2,0,700);
			
			SIMPWM_SET_CRR(&motorA1,300,1000);
			SIMPWM_SET_CRR(&motorA2,1000,300);
			SIMPWM_SET_CRR(&motorB1,1000,300);
			SIMPWM_SET_CRR(&motorB2,300,1000);
		}
		if(mw_data.turn == RIGHT){
//			SIMPWM_SET_CRR(&motorA1,700,0);
//			SIMPWM_SET_CRR(&motorA2,0,700);
//			SIMPWM_SET_CRR(&motorB1,0,700);
//			SIMPWM_SET_CRR(&motorB2,700,0);
			
			SIMPWM_SET_CRR(&motorA1,1000,300);
			SIMPWM_SET_CRR(&motorA2,300,1000);
			SIMPWM_SET_CRR(&motorB1,300,1000);
			SIMPWM_SET_CRR(&motorB2,1000,300);
		}
	}
}