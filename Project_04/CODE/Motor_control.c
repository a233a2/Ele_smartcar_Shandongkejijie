#include "headfile.h"

//BTN7960
#define MOTOR1_P          ATOM1_CH5_P21_7   //ATOM0_CH2_P21_4
#define MOTOR1_N          ATOM0_CH2_P21_4

#define MOTOR2_P          ATOM0_CH1_P21_3   //ATOM0_CH3_P21_5
#define MOTOR2_N          ATOM0_CH3_P21_5

//#define MOTOR1_P          ATOM0_CH4_P02_4   //ATOM0_CH2_P21_4
//#define MOTOR1_N          ATOM0_CH5_P02_5
//
//#define MOTOR2_P          ATOM0_CH6_P02_6   //ATOM0_CH3_P21_5
//#define MOTOR2_N          ATOM0_CH7_P02_7




////DRV8701E
//#define MOTOR1_P          ATOM2_CH2_P33_6   //PWM
//#define MOTOR1_N          ATOM2_CH3_P33_7   //01
//#define MOTOR2_P          ATOM2_CH4_P33_8   //PWM
//#define MOTOR2_N          ATOM0_CH1_P33_9   //01

#define MOTOR_FREQUENCY          12.5*1000

#define SERVO_FREQUENCY 50   //舵机频率100Hz

#define SERVO_PIN ATOM2_CH5_P15_2 //舵机引脚

#define Servo_zuo_Max 730+90   //=820  左转max820
#define Servo_you_Min 730-90  //=640  右转max640

uint16 Servo_Mid=730;








void MotorInit (void)
{
    gpio_init(P21_7, GPO, 0, PUSHPULL);
    gpio_init(P21_4, GPO, 0, PUSHPULL);
    gpio_init(P21_3, GPO, 0, PUSHPULL);
    gpio_init(P21_5, GPO, 0, PUSHPULL);

    gtm_pwm_init(MOTOR1_P, MOTOR_FREQUENCY, 0);  //电机的PWM使用17K这样可以尽量避免PWM干扰到电磁采集。
    gtm_pwm_init(MOTOR1_N, MOTOR_FREQUENCY, 0);
    gtm_pwm_init(MOTOR2_P, MOTOR_FREQUENCY, 0);
    gtm_pwm_init(MOTOR2_N, MOTOR_FREQUENCY, 0);
}


void Loss_line_Protect(void)
{
    if(L1<=100&& L2<=100 && L3<=100 && R1<=100 && R2<=100&& R3<=100)
    {
        stop_flag=1;
    }

    if(stop_flag==1)  //上位机停车命令
    {
        Zuo_duty=You_duty=0;
        Target_speed=0;
    }
}





//舵机初始化
void ServoInit (void)
{
    gpio_init(P15_2, GPO, 0, PUSHPULL);

    gtm_pwm_init(SERVO_PIN, SERVO_FREQUENCY, 730);
}



/*
 * 舵机驱动函数
 *
 *问题 到底是写个入口函数好还是用全局变量好?
 */
void Servo_Control(int16 servo_duty)
{
    if (servo_duty >= Servo_zuo_Max)                  //限制幅值
        servo_duty = Servo_zuo_Max;



    else if (servo_duty <= Servo_you_Min)            //限制幅值
        servo_duty = Servo_you_Min;

    pwm_duty(SERVO_PIN,servo_duty);  //舵机频率为50hz，初始值为1.5ms中值
}



/*
 *BTN7960
 *  电机PWM实时控制  From LQ
 *入口参数 传入 PWM DUTY 占空比 0% 0-10000 100%
 *
 *给正负值  支持正反转
 */
void MotorControl(double motor1, double motor2)//输入 速度值即可控制电机转动 最大速度 1 最小速度 0
{
    static sint32 motor11,motor22;  //强制类型转换

    if(motor1>=0.85)motor1=0.85;
    if(motor1<=-0.85)motor1=-0.85;

    if(motor2>=0.85)motor2=0.85;
    if(motor2<=-0.85)motor2=-0.85;

    motor11=motor1*10000;
    motor22=motor2*10000;

    if (motor11 >= 0)
    {
        pwm_duty(MOTOR1_P,motor11);
        pwm_duty(MOTOR1_N, 0);
    }
    else if(motor11 < 0)    //反转
    {
        pwm_duty(MOTOR1_P, 0);
        pwm_duty(MOTOR1_N,abs(motor11));
    }
    if (motor22 >= 0)
    {
        pwm_duty(MOTOR2_P,motor22);
        pwm_duty(MOTOR2_N, 0);
    }
    else if(motor22 < 0)
    {
        pwm_duty(MOTOR2_P, 0);
        pwm_duty(MOTOR2_N, abs(motor22));
    }
}

void Motor_test(void)
{
    pwm_duty(MOTOR1_P, 0);
    pwm_duty(MOTOR1_N,2000);
    pwm_duty(MOTOR2_P, 0);
    pwm_duty(MOTOR2_N, 2000);
}

void Servo_test(void)
{
    pwm_duty(SERVO_PIN,0);  //舵机频率为100HZ，初始值为1.5ms中值
}

