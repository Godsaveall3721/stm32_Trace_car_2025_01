#include "logic.h"
#include "Servo.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>




    /**
     * @brief 控制小车拐弯的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
     * @param rad_factor (uint8_t) 拐弯弧度因子 
     * @param direction (uint8_t) 拐弯方向(1是右拐2是左拐,3直走,4倒车,5停车,6定点左拐弯,7定点右拐弯)
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
        case 6:goto Left_don;
		case 7:goto Right_don;

        case 8:goto Right_don_2;  //后轮部分太光滑
        case 9:goto Left_don_2;

        case 10:goto Right_don_3;  //前轮部分太光滑
        case 11:goto Left_don_3;
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

	Left_don:
	motor_control(&Motorlogic, 1, base_speed, 1); // 内圈
    motor_control(&Motorlogic, 2, num1, 1); // 外圈
    motor_control(&Motorlogic, 3, 0, 0);
    motor_control(&Motorlogic, 4,0, 0);
        goto end;

	Right_don:
	motor_control(&Motorlogic, 1, 0, 0);
    motor_control(&Motorlogic, 2, 0, 0);
    motor_control(&Motorlogic, 3, num1, 1); // 外圈
    motor_control(&Motorlogic, 4,base_speed, 1); // 内圈
        goto end;

	Right_don_2:
	motor_control(&Motorlogic, 1, base_speed, 2);
    motor_control(&Motorlogic, 2, 0, 0);
    motor_control(&Motorlogic, 3, num1, 1); // 外圈
    motor_control(&Motorlogic, 4,base_speed, 1); // 内圈
        goto end;

	Left_don_2:
	motor_control(&Motorlogic, 1, base_speed, 1); // 内圈
    motor_control(&Motorlogic, 2, num1, 1); // 外圈
    motor_control(&Motorlogic, 3, 0, 0);
    motor_control(&Motorlogic, 4,base_speed, 2);
        goto end;
		
    Right_don_3:
	motor_control(&Motorlogic, 1, 0, 0);
    motor_control(&Motorlogic, 2, base_speed, 2);
    motor_control(&Motorlogic, 3, num1, 1); // 外圈
    motor_control(&Motorlogic, 4,base_speed, 1); // 内圈
        goto end;

    Left_don_3:
	motor_control(&Motorlogic, 1, base_speed, 1); // 内圈
    motor_control(&Motorlogic, 2, num1, 1); // 外圈
    motor_control(&Motorlogic, 3, base_speed, 2);
    motor_control(&Motorlogic, 4,0, 0);

    error:
        OLED_ShowString(1,1,"error in Logic 001",16,0);
        goto end;

    end: ;
    }

    
    /**
     * @brief 以灰度中心建立直线坐标系函数,根据偏移程度返回偏偏移量的函数
    */
	uint8_t temp1 = 0;
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
        .kd = -0.2			//赋值微分值
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
    void Sandwich_function_01(uint8_t base_speed)
    {
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;

    static uint8_t flag;
    long temp = 0;
    temp = PID_P(Gray_Offset_value()); // 取的偏移值

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



    /**
     * @brief 通过灰度控制小车拐弯的逻辑函数(删除三条线指定停判断逻辑)
     * @param base_speed (uint8_t) 小车基本速度
    */
    void Sandwich_function_02_der(uint8_t base_speed){
    Motor_pwm_t Motorlogic;
    Motorlogic.motornum = motor_;

    uint8_t flag;
    long temp = 0;
    temp = PID_P(Gray_Offset_value()); // 取的偏移值

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
        OLED_ShowString(1,1,"error in Logic 003",16,0);
    }
    Turn_round(base_speed, temp, flag); 

    }


    /**
     * @brief 通过灰度/超声波控制小车运动的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
    */
    void Sandwich_function_02(uint8_t base_speed){

    uint8_t flag_roun = 0;
    int counter=0;
   OLED_Showdecimal(1, 5,HCSR04_GetValue() , 4, 2, 16, 1); 

    if(HCSR04_GetValue()<80)  // 进入田字格转弯
    { 
        Turn_round(19, 3, 7);  // 开始转弯
        flag_roun = 0x1 & ~HAL_GPIO_ReadPin(gray_6);    // 读取待测灰度
        if (flag_roun == 1) {                          //如果已经被占,等待解除
        while (1) { 
            flag_roun = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if(flag_roun == 0 ) break;}
        }
        while (1) {                                        // 转弯完成时,跳出等待         
            flag_roun = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if (flag_roun==1)
            {
                break;
            }
        } 
        Turn_round(0, 0, 5);  // 转弯完成
    }

    HAL_Delay(1200);
    flag_roun = 0; // 清零flag给下个阶段使用

    long i = 0; // 为了不让过度转弯,让以下代码毫无用处,故添加i,模拟Delay
    while (1) {    // 沿边沿走到(Ⅲ)
            Sandwich_function_02_der(20); // 不能因为Delay而影响灰度扫描
            i++;
            if(i > 200){
                flag_roun = 1-HAL_GPIO_ReadPin(gray_2);
                if (flag_roun == 1 )
                {
                    flag_roun = 0; // 清零flag给下个阶段使用
                    while (1)
                    {
                        flag_roun = 1 - HAL_GPIO_ReadPin(gray_1);
                        if (flag_roun == 1 )
                        {
                            i = 0;
                            goto endwa;     
                        }  
                        
                    }   
                }  
            }
    }
    endwa:
    Turn_round(0, 0, 5);  // 走到(Ⅲ)完成


    flag_roun = 0; // 清零flag给下个阶段使用
    HAL_Delay(200);
 

    Turn_round(20, 30, 2); // 开始转弯由0号走到1号
    while (1) { // 判定拐弯是否完成
            flag_roun = (1 - HAL_GPIO_ReadPin(gray_8));
            if (flag_roun == 1)
            {
                break;
            }
        } 
    Turn_round(0, 0, 5); 
    
    flag_roun = 0; // 清零flag给下个阶段使用
    uint8_t flag_roun2 = 0;
    while(1) {  // 走到2号
            Sandwich_function_02_der(20);
            if(HAL_GPIO_ReadPin(gray_1) == 0) flag_roun = 1; // 进入黑色带,等待走出去
            if(flag_roun == 1){
                while (1){
                Sandwich_function_02_der(20);
                if(HAL_GPIO_ReadPin(gray_1) == 1) {  // 等待走出黑色区域
                        flag_roun = 0;
                        flag_roun2++;
                        break;
                    }
                }
            }
            if (flag_roun2 == 2) goto end02;
    }
    end02:
    Turn_round(0, 0, 5); 
    // 三明治2正式结束
}



    /**
     * @brief 通过灰度/超声波控制小车运动的逻辑函数
     * @param base_speed (uint8_t) 小车基本速度
    */
    int flag=0;
    void Sandwich_function_03(uint8_t base_speed){
        Servo_straight();
        if(HCSR04_GetValue()<80)
        {
            Turn_round(20, 0, 3); 
            HAL_Delay(400);
            Turn_round(0, 0, 5); 
            while(1)
            {
             Sandwich_function_02_der(base_speed); 
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                  HAL_Delay(10);
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                break;
               }
            }
            }
                   Turn_round(20, 0, 3); 
                   HAL_Delay(400);
                   Turn_round(0, 0, 5); 
                HAL_GPIO_WritePin(LED_ON_GPIO_Port,LED_ON_Pin,1);
                Servo_straight();
                }else if(HCSR04_GetValue()>80)//第一个角没有障碍物,开始左拐,向下一个十字路口准备
        {
       Turn_round(18, 10,11);  // 开始转弯
        flag = 0x1 & ~HAL_GPIO_ReadPin(gray_3);    // 读取待测灰度
        if (flag == 1) {                          //如果已经被占,等待解除
        while (1) { 
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_3);
            if(flag == 0 ) break;}
        }
        while (1) {                                        // 转弯完成时,跳出等待         
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_3);
            if (flag==1)
            {
                break;
            }
        }
        Turn_round(0, 0, 5);  // 转弯完成

    HAL_Delay(1200);
    flag = 0; // 清零flag给下个阶段使用
            while(1)                                                         //走到下一个十字路口
            {
            Sandwich_function_02_der(20);
            if(HAL_GPIO_ReadPin(gray_1) == 0)
            {
                break;
            }
            }
            Turn_round(0, 0, 5);  // 转弯完成

    HAL_Delay(1200);
    flag = 0; // 清零flag给下个阶段使用
                                                                            //走到了



        Servo_left(); 
        HAL_Delay(500);                                            //旋转舵机开始检测障碍物
        if(HCSR04_GetValue()<80)                                  //如果有障碍物
        {
             Turn_round(20, 0, 3); 
            HAL_Delay(100);
            Turn_round(0, 0, 5); 
        Turn_round(20, 20, 8);  // 开始转弯
        flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);    // 读取待测灰度
        if (flag == 1) {                          //如果已经被占,等待解除
        while (1) { 
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if(flag == 0 ) break;}
        }
        while (1) {                                        // 转弯完成时,跳出等待         
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if (flag==1)
            {
                break;
            }
        }
        Turn_round(0, 0, 5);  // 转弯完成

    HAL_Delay(1200);
    flag = 0; // 清零flag给下个阶段使用
    
    while(1)
            {
             Sandwich_function_02_der(base_speed); 
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                  HAL_Delay(10);
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                break;
               }
            }
            }
                   Turn_round(20, 0, 3); 
                   HAL_Delay(400);
                   Turn_round(0, 0, 5); 
                HAL_GPIO_WritePin(LED_ON_GPIO_Port,LED_ON_Pin,1);//走到终点
                Servo_straight();
        }else if(HCSR04_GetValue()>80)
        {
            Turn_round(20, 0, 3); 
            HAL_Delay(400);
            while(1)
            {
             Sandwich_function_02_der(base_speed); 
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                  HAL_Delay(10);
               if (HAL_GPIO_ReadPin(gray_1) == 0){
                break;
               }
            }
            }
            Turn_round(0, 0, 5);  // 转弯完成

    HAL_Delay(1200);
    flag = 0; // 清零flag给下个阶段使用


            if(HCSR04_GetValue()<80)
            {
                Turn_round(20, 20, 8);  // 开始转弯
        flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);    // 读取待测灰度
        if (flag == 1) {                          //如果已经被占,等待解除
        while (1) { 
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if(flag == 0 ) break;}
        }
        while (1) {                                        // 转弯完成时,跳出等待         
            flag = 0x1 & ~HAL_GPIO_ReadPin(gray_6);
            if (flag==1)
            {
                break;
            }
        }
        Turn_round(0, 0, 5);  // 转弯完成

    HAL_Delay(1200);
    flag = 0; // 清零flag给下个阶段使用
    
    while(1)
            {
             Sandwich_function_02_der(base_speed); 
               if (HAL_GPIO_ReadPin(gray_8) == 0){
                  HAL_Delay(10);
               if (HAL_GPIO_ReadPin(gray_8) == 0){
                break;
               }
            }
            }
                Turn_round(20, 0, 3); 
                   HAL_Delay(400);
                   Turn_round(0, 0, 5); 
                HAL_GPIO_WritePin(LED_ON_GPIO_Port,LED_ON_Pin,1);//走到终点
                Servo_straight();
        }
            }
        }
         }
