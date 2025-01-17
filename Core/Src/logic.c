#include "logic.h"




    /**
     * @brief 控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
     * @param rad_factor (uint8_t) 拐弯弧度因子 
     * @param direction (uint8_t) 拐弯方向(1是右拐2是左拐,3直走,4倒车)
    */
    void Turn_round(uint8_t base_speed,uint8_t rad_factor,uint8_t direction){
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;
    uint8_t num1;

    num1 = base_speed + rad_factor;

    if (num1 > PWM_Period_Motor) goto error;

    switch(direction)
    {
        case 1:goto Right_;
        case 2:goto Left_;
        case 3:goto Nullgo_;
        case 4:goto Nullback_;
		case 5:goto Park_;
        default:
            goto error;  
    }
    Right_:
    motor_control(&Motorlogic, 1, num1, 2); // 外圈
    motor_control(&Motorlogic, 2, base_speed, 2); // 内圈
    motor_control(&Motorlogic, 3, base_speed, 1); // 内圈
    motor_control(&Motorlogic, 4, num1, 1); // 外圈
        goto end;
    
    Left_:
    motor_control(&Motorlogic, 1, num1, 1);
    motor_control(&Motorlogic, 2, base_speed, 1);
    motor_control(&Motorlogic, 3, base_speed, 2);
    motor_control(&Motorlogic, 4, num1, 2);
        goto end;

    Nullgo_:
    motor_control(&Motorlogic, 1, base_speed, 1);
    motor_control(&Motorlogic, 2, base_speed, 1);
    motor_control(&Motorlogic, 3, base_speed, 1);
    motor_control(&Motorlogic, 4, base_speed, 1);
        goto end;

    Nullback_:
    motor_control(&Motorlogic, 1, base_speed, 2);
    motor_control(&Motorlogic, 2, base_speed, 2);
    motor_control(&Motorlogic, 3, base_speed, 2);
    motor_control(&Motorlogic, 4, base_speed, 2);
        goto end;

	Park_:
	motor_control(&Motorlogic, 1, base_speed, 1);
    motor_control(&Motorlogic, 2, base_speed, 1);
    motor_control(&Motorlogic, 3, base_speed, 1);
    motor_control(&Motorlogic, 4, base_speed, 1);
        goto end;
		
    error:
        OLED_ShowString(1,1,"error in Logic 001",16,0);
        goto end;

    end: ;
    }

    
    /**
     * @brief 以灰度中心建立直线坐标系函数,根据偏移程度返回偏偏移量的函数
    */
	uint8_t temp1;
    int Gray_Offset_value(void){
    int value_ = 0;
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
    value_ += -3 * ( (temp1 & 0x1) & ((temp1 >> 1) & 0x1) ); // 1
    value_ += -2 * ( ((temp1 >> 2) & 0x1) & ((temp1 >> 1) & 0x1) ); // 2
    value_ += -1 * ( ((temp1 >> 2) & 0x1) & ((temp1 >> 3) & 0x1) ); // 3
    value_ +=  0 * ( ((temp1 >> 4) & 0x1) & ((temp1 >> 3) & 0x1) ); // 4
    value_ +=  1 * ( ((temp1 >> 4) & 0x1) & ((temp1 >> 5) & 0x1) ); // 5
    value_ +=  2 * ( ((temp1 >> 6) & 0x1) & ((temp1 >> 5) & 0x1) ); // 6
    value_ +=  3 * ( ((temp1 >> 6) & 0x1) & ((temp1 >> 7) & 0x1) ); // 7
    return value_;
    }
    
    
    //定义转向pid参数结构体
    _PID pid_=
    {
        .kp = 1,			//赋值比例值
        .ki = 0,			//赋值积分值(用不到)
        .kd = -0.6			//赋值微分值
    };		

    /**
     * @brief 传入灰度偏移量,函数
    */
    int PID_P(int value_)
    {
    int value_old = 0;
    value_old = value_;
    value_ = value_ * pid_.kp; // 赋值比例值
    int temp2 = 0;

    // 处理 value 导出 new value
    if (value_ < 0){
        temp2 = -value_;
            while (temp2 >= 6) {//18
                 value_ += 2;
                 temp2 = -value_;
            }
        if(temp2 < 2) value_ = 0;
    }else
    {
        temp2 = value_;
            while (temp2 >= 6) {//18
                    value_ -= 2;
                    temp2 = value_;
            }
        if(temp2 < 2) value_ = 0;
    }
    int value_new = value_;
    return (int)(value_new + pid_.kd * (value_new - value_old));
    }


    /**
     * @brief 通过灰度控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
    */
	int count=0;
    void Sandwich_function_01(uint8_t base_speed)
    {
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;

    uint8_t flag;
    long temp = 0;
    temp = PID_P(Gray_Offset_value()); // 取的偏移值
	if(temp1==0)		
	{
		count++;
		if(count<=4)
		{
		Turn_round(20, 0, 3);
		HAL_Delay(400);	
	    flag = 5; //停车
		Turn_round(0, 0, 5);
		HAL_GPIO_WritePin(LED_ON_GPIO_Port,LED_ON_Pin,1);
		HAL_Delay(3000);
		HAL_GPIO_WritePin(LED_ON_GPIO_Port,LED_ON_Pin,0);
		goto end;
		}
	}
    if (temp == 0) // 判断拐弯方向 
    {
        flag = 3; // 直走
    }else if (temp < 0) // 判断拐弯方向 
    {
        flag = 1; // 左拐
        temp = -temp; // 负值反转
    }else if (temp > 0) // 判断拐弯方向 
    {
        flag = 2; // 右拐
    }else{
        OLED_ShowString(1,1,"error in Logic 002",16,0);
    }
    Turn_round(base_speed, temp, flag); 
	end: ;
    }

