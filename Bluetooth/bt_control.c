#include "bt_control.h"
#include "stdlib.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

Bt_Data_Typedef data;
int bt_state = 0;
void BT_Init(){
	data.x = MIDDLE;
	data.y = MIDDLE;
	data.finalx = 0;
	data.finaly = 0;
	data.turn = No;
	bt_state = 0;
}
bool BT_Read(char msg , Bt_Data_Typedef *data_in){
	if(msg == 'M'){
		if(0 <= data.x && data.x <= 20) data_in->x = data.x - MIDDLE;
		if(0 <= data.y && data.y <= 20) data_in->y = -(data.y - MIDDLE);
		data_in->turn = data.turn;
		BT_Init();
		return true;
	}
	
	if(bt_state == 0){
		if(msg == 'L') bt_state = 1;
		else if(msg == 'R') bt_state = 4;
		return false;
	}
	
	if(bt_state == 1 && msg == 'X'){
		bt_state = 2;
		data.x = 0;
		return false;
	}
	
	if(bt_state == 2 && msg == 'Y'){
		bt_state = 3;
		data.y = 0;
		return false;
	}
	
	if(bt_state == 2){
		data.x = data.x * 10 + (msg - '0');
		return false;
	}
	if(bt_state == 3) {
		data.y = data.y * 10 + (msg - '0');
		return false;
	}
	
	if(bt_state == 4){
		if(msg == '1') data.turn = LEFT;
		else if(msg == '2') data.turn = RIGHT;
		return false;
	}
	return false;
}
void BT_Compute(Bt_Data_Typedef *data_in){
	if(data_in->x > 0 && data_in->y > 0){
		data_in->finalx = data_in->x * 10.0 / data_in->x + data_in->y;
		data_in->finaly = data_in->y * 10.0 / data_in->x + data_in->y;
	}
	if(data_in->x < 0 && data_in->y > 0){
		data_in->finalx = data_in->x * 10.0 / -data_in->x + data_in->y;
		data_in->finaly = data_in->y * 10.0 / -data_in->x + data_in->y;
	}
	if(data_in->x < 0 && data_in->y < 0){
		data_in->finalx = data_in->x * 10.0 / -(data_in->x + data_in->y);
		data_in->finaly = data_in->y * 10.0 / -(data_in->x + data_in->y);
	}
	if(data_in->x > 0 && data_in->y < 0){
		data_in->finalx = data_in->x * 10.0 / data_in->x - data_in->y;
		data_in->finaly = data_in->y * 10.0 / data_in->x - data_in->y;
	}
}