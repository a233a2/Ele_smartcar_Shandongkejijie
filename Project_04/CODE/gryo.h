#ifndef _gyro_h
#define _gyro_h

extern float gx, gy, gz;
extern float ax, ay, az;

extern float gx_zero, gy_zero, gz_zero;

extern float angle_pitch, angle_yaw, angle_roll;

extern int pitch_flag, yaw_flag, roll_flag; //开始积分标志




extern float Target_Z_angle;

extern float ang_err;

extern uint8 Angle_CNT_Flag;   ////目标角度改变标志位  达到目标角度进行下一步操作或者退出操作




void angle_get(void);

void angle_filter(void);

#endif
