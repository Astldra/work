#ifndef _BT_CONTROL_H
#define _BT_CONTROL_H
#define MIDDLE 10

#include "stdbool.h"

#define BT_UART &huart3

typedef enum{
	No,
	LEFT,
	RIGHT
}Turn_Typedef;
typedef struct{
	int x;
	int y;
	float finalx;
	float finaly;
	Turn_Typedef turn;
}Bt_Data_Typedef;
void BT_Init();
bool BT_Read(char msg,Bt_Data_Typedef *data_in);
void BT_Compute(Bt_Data_Typedef *data_in);
#endif