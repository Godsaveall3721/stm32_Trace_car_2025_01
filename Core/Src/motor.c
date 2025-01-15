#include <motor.h>
#include <stdint.h>


    /**
     * @brief 控制马达转动的函数
     * @param num (uint8_t) 马达编号顺时针(1~4号)
     * @param motorspeed (uint32_t) 马达速度(通过控制占空比)
     * @param direction (uint8_t) 马达方向(通过控制gpio口来控制,1是正方向2是反方向0是停止)
    */
    void motor_(uint8_t num, uint32_t motorspeed, uint8_t direction){
    uint8_t flag = 1;
    int A,B;

    if (direction == 0)
    {
        A = GPIO_PIN_RESET;
        B = GPIO_PIN_RESET;
    }else if (direction == 1) {
        A = GPIO_PIN_SET;
        B = GPIO_PIN_RESET;
    }else if (direction == 2) {
        A = GPIO_PIN_RESET;
        B = GPIO_PIN_SET;
    }else{
        OLED_ShowString(1,1,"error in Motor",16,0);
    }

    switch(num)
    {
        case 1:goto Right_front;
        case 2:goto Right_back;
        case 3:goto Left_back; 
        case 4:goto Left_front;
        default:
            flag = 0; 
            goto end;  
    }
    Right_front: // 1号轮
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,B);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,A);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motorspeed);
        goto end;
    Right_back: // 2号轮
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,A);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,B);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, motorspeed);
        goto end;
    Left_back: // 3号轮
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,B);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,A);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, motorspeed);
        goto end;
    Left_front: // 4号轮
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,A);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,B);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, motorspeed);
        goto end;

    end: 
    if (flag == 0) OLED_ShowString(1,1,"error in Motor",16,0);
    A = 0;
    B = 0;
    }


    void motor_control(Motor_pwm_t *opt, uint8_t num, uint32_t motorspeed, uint8_t direction)
    {
    opt -> motornum(num, motorspeed, direction); // 结构体指针
    }