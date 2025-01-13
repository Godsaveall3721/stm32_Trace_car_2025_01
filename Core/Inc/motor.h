#ifndef __MOTOR_H__
#define __MOTOR_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <oled.h>

typedef struct
{
    /**
     * @brief 控制马达转动的函数
     * @param num (uint8_t) 马达编号顺时针(1~4号)
     * @param motorspeed (uint32_t) 马达速度(通过控制占空比)
     * @param direction (uint8_t) 马达方向(通过控制gpio口来控制,1是正方向2是反方向0是停止)
    */
    void (*motornum)(uint8_t num, uint32_t motorspeed, uint8_t direction);
  
}Motor_pwm_t;


#ifdef __cplusplus
}
#endif


#endif /* __MOTOR_H__ */