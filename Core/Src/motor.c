#include <motor.h>

void motor_(uint8_t num, uint32_t motorspeed, uint8_t direction){
uint8_t flag = 1;
switch(num)
{
case 1:goto Right_front; break;
case 2:goto Right_back; break;
case 3:goto Left_back; break;
case 4:goto Left_front; break;
default:
    flag = 0; break;  
}
if (flag == 0) OLED_ShowString(1,1,"error in Motor",16,0); goto end;
Right_front:
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motorspeed);
Right_back:
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, motorspeed);
Left_back:
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, motorspeed);
Left_front:
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, motorspeed);
end: ;
}