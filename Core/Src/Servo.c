#include "Servo.h"
#include "tim.h"


//舵机180度来回旋转
void Servo_start(void)
{
	uint16_t i,k;
  if(k==0)
{
	while(i<2500)
	{
		i+=100;
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,i);	
	HAL_Delay(300);
	}
   k=1;
}
	else if(k==1)
	{
		while(i>500)
		{
		i-=100;
		 __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);
			HAL_Delay(300);
		}
	   k=0;
	}   
}

//舵机上的超声波转向正中央
void Servo_straight(void)
{
    __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,1500);	
}  

//舵机上的超声波转向左方
void Servo_left(void)
{
 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,500);	
}

//舵机上的超声波转向右方
void Servo_right(void)
{
 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,2500);	
}  

