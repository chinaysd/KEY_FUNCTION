#include "sys_config.h"



#define KEY1_PIN						P20
#define KEY2_PIN						P01
#define KEY3_PIN						P22
#define KEY4_PIN						P03
#define KEY5_PIN						P21
#define KEY6_PIN						P02
#define KEY7_PIN						P00

unsigned char Key_Port_Read(unsigned char num){
	if(num == 1){
		return KEY1_PIN;
	}else if(num == 2){
		return KEY2_PIN;
	}else if(num == 3){
		return KEY3_PIN;
	}else if(num == 4){
		return KEY4_PIN;
	}else if(num == 5){
		return KEY5_PIN;
	}else if(num == 6){
		return KEY6_PIN;
	}else if(num == 7){
		return KEY7_PIN;
	}else{
		return 0XFF;
	}
}

unsigned char Key_Port_Init(void){
	CLR_REG_CON(2, 0);
	SET_IO_PU(2, 0);
	
	CLR_REG_CON(0, 1);
	SET_IO_PU(0, 1);
	
	CLR_REG_CON(2, 2);
	SET_IO_PU(2, 2);
		
	CLR_REG_CON(0, 3);
	SET_IO_PU(0, 3);
	
	CLR_REG_CON(2, 1);
	SET_IO_PU(2, 1);
	
	CLR_REG_CON(0, 2);
	SET_IO_PU(0, 2);
	
	CLR_REG_CON(0, 0);
	SET_IO_PU(0, 0);
	
	return 1;
}
