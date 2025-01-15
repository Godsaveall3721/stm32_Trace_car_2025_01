#include "logic.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>




    /**
     * @brief 控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
     * @param rad_factor (uint8_t) 拐弯弧度因子
     * @param direction (uint8_t) 拐弯方向(1是右拐2是左拐)
    */
    void Turn_round(uint8_t base_speed,uint8_t rad_factor,uint8_t direction){
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;

    uint8_t num1, num2, flag;
    num1 = base_speed + rad_factor;
    if (num1 > PWM_Period_Motor) goto error;
    if (base_speed >= rad_factor){
    num2 = base_speed - rad_factor;
    flag = 1;
    }else{
    num2 = rad_factor - base_speed;
    flag = 2;
    }

    switch(direction)
    {
        case 1:goto Right_;
        case 2:goto Left_;
        default:
            goto error;  
    }
    Right_:
    motor_control(&Motorlogic, 1, base_speed, 1);
    motor_control(&Motorlogic, 2, num2, flag);
    motor_control(&Motorlogic, 3, base_speed, 1);
    motor_control(&Motorlogic, 4, num1, 1);
        goto end;
    
    Left_:
    motor_control(&Motorlogic, 1, num1, 1);
    motor_control(&Motorlogic, 2, base_speed, 1);
    motor_control(&Motorlogic, 3, num2, flag);
    motor_control(&Motorlogic, 4, base_speed, 1);
        goto end;

    error:
        OLED_ShowString(1,1,"error in Logic",16,0);
        goto end;

    end: ;
    }

    


    /**
     * @brief 以灰度中心建立直线坐标系函数,根据偏移程度返回偏偏移量的函数
    */
    long value_ = 0;
    long Gray_Offset_value(void){
    uint8_t temp1;
    temp1 = 
    0xFF & ( 
    (HAL_GPIO_ReadPin(gray_1) << 0) | 
    (HAL_GPIO_ReadPin(gray_2) << 1) | 
    (HAL_GPIO_ReadPin(gray_3) << 2) | 
    (HAL_GPIO_ReadPin(gray_4) << 3) | 
    (HAL_GPIO_ReadPin(gray_5) << 4) | 
    (HAL_GPIO_ReadPin(gray_6) << 5) | 
    (HAL_GPIO_ReadPin(gray_7) << 6) | 
    (HAL_GPIO_ReadPin(gray_8) << 7) ); 


    value_ += -7 * (temp1 & 0x1);
    value_ += 6 * ((temp1 & 0x1) & ((temp1 >> 1) & 0x1)); // 中值
    value_ += -5 * ((temp1 >> 1) & 0x1);
    value_ += 4 * (((temp1 >> 1) & 0x1) & ((temp1 >> 2) & 0x1)); // 中值
    value_ += -3 * ((temp1 >> 2) & 0x1);
    value_ += 2 * (((temp1 >> 2) & 0x1) & ((temp1 >> 3) & 0x1)); // 中值
    value_ += -1 * ((temp1 >> 3) & 0x1);
    //value_ += 0; // 中值
    value_ += 1 * ((temp1 >> 4) & 0x1);
    value_ += -2 * (((temp1 >> 4) & 0x1) & ((temp1 >> 5) & 0x1)); // 中值
    value_ += 3 * ((temp1 >> 5) & 0x1);
    value_ += -4 * (((temp1 >> 5) & 0x1) & ((temp1 >> 6) & 0x1)); // 中值
    value_ += 5 * ((temp1 >> 6) & 0x1);
    value_ += -6 * (((temp1 >> 6) & 0x1) & ((temp1 >> 7) & 0x1)); // 中值
    value_ += 7 * ((temp1 >> 7) & 0x1);
    return value_;
    }



    /**
     * @brief 通过灰度控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
    */
    void Sandwich_function_01(uint8_t base_speed)
    {
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;
    uint8_t flag;
    long temp,i=0;
    temp = Gray_Offset_value(); // 取的偏移值
    if (temp < 0) // 判断拐弯方向 
    {
        flag = 2; // 左拐
        temp = -temp; // 负值反转
    }else{
        flag = 1; // 右拐
    }
    Turn_round(base_speed, temp, flag); 
    do {
    temp = Gray_Offset_value();
    if (temp < 0) temp = -temp;
    if(temp < 5) break;
    i++;                   // 防止卡循环
    if(i > 2500) break;
    } while(1);
    motor_control(&Motorlogic, 1, base_speed, 1);
    motor_control(&Motorlogic, 2, base_speed, 1);
    motor_control(&Motorlogic, 3, base_speed, 1);
    motor_control(&Motorlogic, 4, base_speed, 1);
    }

