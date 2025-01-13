#include "HCSR04.h"
#include "OLED.h"
#include "tim.h"
#include "gpio.h"
#include "i2c.h"

extern uint16_t counteo;
//OLED初始化
void OLED_Start(void)
{
    OLED_Init();                           //OLED初始
	OLED_Clear();                         //清屏
	OLED_ShowString(1,1, "distance:",16,0);
	OLED_ShowString(1,4, "cm",16,0);
}
//us延迟函数
void delay_us(uint32_t us)
{
    // 计算需要的计数值，根据 TIM6 的计数周期
    // 计数频率为 1MHz，所以 1 个计数周期为 1μs
    uint32_t ticks = us;

    // 启动 TIM6 定时器
    HAL_TIM_Base_Start(&htim6);

    // 保存当前计数器的值
    uint32_t start_tick = __HAL_TIM_GET_COUNTER(&htim6);
    // 等待计数值达到所需的微秒数
    while ((__HAL_TIM_GET_COUNTER(&htim6) - start_tick) < ticks)
    {
        // 防止编译器优化掉这个等待循环
        __NOP(); 
    }

    // 停止 TIM6 定时器
    HAL_TIM_Base_Stop(&htim6);
}
//超声波发送
void HCSR04_Start(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,1);
	delay_us(15);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,0);
}


//超声波距离
float  HCSR04_GetValue(void)
{
	HCSR04_Start();
	HAL_Delay(100);
	if(counteo>23323 )
	{
	return 400;
	}
	else if(counteo<120)
	{
	return 2;
	}	
	else
	{
	return (float)(((float)(counteo*0.000001)*34300)/2);
	}
}
