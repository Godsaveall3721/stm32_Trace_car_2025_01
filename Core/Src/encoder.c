#include <encoder.h>

void get_Encoder_info(TIM_HandleTypeDef htimx, uint32_t *Enc_Count, int *speed)
{
  uint32_t temp1,temp2;
  int temp3;
  //判定正反转,取得coun值和speed值
  if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htimx) != 0) //判断单个马达正反转,不妨令count升高事件为正方向
  {   //1时反转temp1 > temp2
    temp1 = __HAL_TIM_GET_COUNTER(&htimx);
    *Enc_Count = temp1*1./20; //旋转圈数  count*马达-编码器转圈数比
    HAL_Delay(100);
    temp2 =  __HAL_TIM_GET_COUNTER(&htimx);
    temp3 = (int)((temp1 - temp2)); //不妨在100ms内做差表速度
    if (temp3 >= 0) //为了保证在Delay100ms内发生count被重置而导致的计数偏差的事件不会影响结国,要进行大小验证
    {
    *speed = temp3; //虽然是小概率事件,但是要严格保证速度的正确性
    }
  }else
  {  //0时正转temp2 > temp1
    temp1 = __HAL_TIM_GET_COUNTER(&htimx);
    *Enc_Count = temp1*1./20;
    HAL_Delay(100);
    temp2 =  __HAL_TIM_GET_COUNTER(&htimx);
    temp3 = (int)((temp2 - temp1));
    if (temp3 >= 0)
    {
    *speed = temp3;
    }
  }
}



void pri_Encoder_inf(uint32_t *Enc_Count, int *speed)
{
  OLED_ShowNum(1,3,*Enc_Count,6,16, 1);
  OLED_ShowNum(1,5,*speed,6,16, 1);
}

void get_Encoder_information_printf(Encoder_information_t *opt, TIM_HandleTypeDef htimx, uint32_t *Enc_Count, int *speed)
{
opt -> getinfo(htimx, Enc_Count, speed); // 指定特定编码器
opt -> pritinfo(Enc_Count, speed); // 打印特定编码器
}
