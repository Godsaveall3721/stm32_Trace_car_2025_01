#ifndef __SERVO_H__
#define __SERVO_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "tim.h"	

//舵机180度来回旋转
void Servo_start(void);

//舵机上的超声波转向正中央
void Servo_straight(void);
	
//舵机上的超声波转向左方
void Servo_left(void);

//舵机上的超声波转向右方
void Servo_right(void);

	#ifdef __cplusplus
}
#endif


#endif /* __SERVO_H__ */

