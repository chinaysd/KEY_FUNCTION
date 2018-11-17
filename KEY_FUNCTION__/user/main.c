#include "sc92f732x_c.h"
#include "key.h"
#include "TimeOut.h"

typedef struct
{
    unsigned char Send_Key,Get_Key;
}
APP_PARA_T;

APP_PARA_T App_Para;
/*****************************************************************************
 * Function	  : bsp_Timer0Init
 * Description   : tim0设置为1ms中断
 * Input           : void  
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180414
 *   Author       : marco
 *   Modification: Created function

*****************************************************************************/
void Bsp_Timer0Init(void){ 
	TMCON = 0x00;		
	TMOD = 0x11;    
	TL0 = (65536 - 124)%256;    
	TH0 = (65536 - 124)/256;
	TR0 = 0;
	ET0 = 1;//定时器0允许
	TR0 = 1;//打开定时器0
}

void Key_Handle(unsigned char key)
{
    App_Para.Get_Key = key;
    if(App_Para.Get_Key == MSG_KEY2_LONGPRESS)
    {
        App_Para.Send_Key = 0x01;
    }
    else if(App_Para.Get_Key == MSG_KEY2_SHORT_PRESS)
    {
        App_Para.Send_Key = 0x02;
    }
    else if(App_Para.Get_Key == MSG_KEY3_SHORT_PRESS)
    {
        App_Para.Send_Key = 0x04;
    }
    else if(App_Para.Get_Key == MSG_KEY4_SHORT_PRESS)
    {
        App_Para.Send_Key = 0x08;
    }
    else if(App_Para.Get_Key == MSG_KEY5_SHORT_PRESS)
    {
        App_Para.Send_Key = 0x10;
    }
    else if(App_Para.Get_Key == MSG_KEY6_SHORT_PRESS)
    {
        App_Para.Send_Key = 0x20;
    }
    else if(App_Para.Get_Key == MSG_KEY7_SHORT_PRESS) 
    {
        App_Para.Send_Key = 0x40;
    }
    else if(App_Para.Get_Key == MSG_KEY_NONE)
    {
        App_Para.Send_Key = 0x00;
    }
}



void main(void)
{
    P1CON |= 0XFF;
    P1PH  &= ~0XFF;
    TimeOutDet_Init();
    Bsp_Timer0Init();
    Key_Init();
    Key_Register(Key_Handle);
    WDTCON |= 0X10;
    EA = 1;
    while(1)
    {
        WDTCON |= 0X10;
        P1 &= ~0XFF;
        Key_Poll();
        if(App_Para.Send_Key == 0x01)
        {
            P1 |= 0XFF;
        }
    } 
}

/*****************************************************************************
 * Function	  : Timer0IqrHandle
 * Description   : tim0 中断处理
 * Input		  : None
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180425
 *   Author       : marco
 *   Modification: Created function

*****************************************************************************/
void Timer0IqrHandle() interrupt 1{
	//static unsigned int base_time = 0;
	TL0 = (65536 - 120)%256;   
	TH0 = (65536 - 120)/256;

	TimeOutDet_DecHandle();
    #if 0
	if(base_time ++ >= 8000){
		base_time = 0;
		if(App_Para.LightAutoClsFlag){
			if(App_Para.LightAutoClsCnt ++ > LIGHT_AUTO_CLOSE_TIME){
				App_Para.LightAutoClsFlag = False;
			}
		}
		if(App_Para.HeatAutoClsFlag){
			if(App_Para.HeatAutoClsCnt ++ > HEAT_AUTO_CLOSE_TIME){
				App_Para.HeatAutoClsFlag = False;
			}
		}
	}
    #endif
}
