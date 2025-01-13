#ifndef __HCSR04_H__
#define __HCSR04_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "OLED.h"	
#include "tim.h"
#include "gpio.h"
#include "i2c.h"
	
	
//OLED初始化
void OLED_Start(void);

//us延迟函数
void delay_us(uint32_t us);

//超声波发送
void HCSR04_Start(void);


//超声波距离
float  HCSR04_GetValue(void);

	
	

	#ifdef __cplusplus
}
#endif


#endif /* __SERVO_H__ */

