#ifndef __ENCODER_H__
#define __ENCODER_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <oled.h>

typedef struct
{
    /**
     * @brief 获取编码器相对计数值和速度值函数
     * @param htimx (TIM_HandleTypeDef) 结构体指针
     * @param Enc_Count (uint32_t *) 数据指针
     * @param speed (uint8_t *) 数据指针
    */
    void (*getinfo)(TIM_HandleTypeDef htimx, uint32_t *Enc_Count, int *speed);

    /**
     * @brief 打印编码器相对计数值和速度值函数
     * @param Enc_Count (uint32_t *) 数据指针
     * @param speed (uint8_t *) 数据指针
    */
    void (*pritinfo)(uint32_t *Enc_Count, int *speed);
}Encoder_information_t;


void get_Encoder_info(TIM_HandleTypeDef htimx, uint32_t *Enc_Count, int *speed);
void pri_Encoder_inf(uint32_t *Enc_Count, int *speed);
void get_Encoder_information_printf(Encoder_information_t *opt, TIM_HandleTypeDef htimx, uint32_t *Enc_Count, int *speed);

#ifdef __cplusplus
}
#endif


#endif /* __ENCODER_H__ */