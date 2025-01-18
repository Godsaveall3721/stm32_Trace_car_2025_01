#ifndef __LOGIC_H__
#define __LOGIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "oled.h"
#include "motor.h"
#include "gpio.h"
#include "HCSR04.h"
#include <math.h>
#include <stdint.h>
#include <Servo.h>

#define PWM_Period_Motor 100

#define gray_1  GPIOB,GPIO_PIN_1
#define gray_2  GPIOB,GPIO_PIN_0
#define gray_3  GPIOA,GPIO_PIN_3
#define gray_4  GPIOC,GPIO_PIN_2
#define gray_5  GPIOC,GPIO_PIN_3
#define gray_6  GPIOA,GPIO_PIN_4
#define gray_7  GPIOC,GPIO_PIN_5
#define gray_8  GPIOB,GPIO_PIN_2

//定义pid结构体
struct PID
{
	float kp;
	float ki;
	float kd;
};
typedef struct PID _PID;

#define PWM_Period_Motor 100  // 



    /**
     * @brief 控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
     * @param rad_factor (uint8_t) 拐弯弧度因子
     * @param direction (uint8_t) 拐弯方向(1是右拐2是左拐)
    */
    void Turn_round(uint8_t base_speed,uint8_t rad_factor,uint8_t direction);
    int Gray_Offset_value(void);
    void Sandwich_function_01(uint8_t base_speed);
    void Sandwich_function_02(uint8_t base_speed);
    void Sandwich_function_03(uint8_t base_speed);



#ifdef __cplusplus
}
#endif

#endif /* __LOGIC_H__ */