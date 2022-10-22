#include "headfile.h"
//舵机转向环PID
float dir_kp,dir_kd;
float dir_err, dir_last_err, dir_err_integration;

//速度环PID
int32    speed_err,  speed_err1, speed_err2;
float speed_kp,  speed_ki;
float set_duty=0;
float speed_out=0,  speed_out_increment;

//电机输出占空比
float Zuo_duty=0;
float You_duty=0;
//舵机输出占空比
uint16 servo_duty;


float Position_dif;



//n次平均滤波之后的速度数据
sint32 zuo_real_speed;
sint32 you_real_speed;

//pid中用的数据 real_speed = (zuo_real_speed+you_real_speed)/2
sint32 real_speed,real_speed_last;  //输出误差  set_speed动态调整


//赛道初步跑完标志位
uint8 Road_statue=0; //1直线 2普通的弯道 3十字后大弯道



uint8 stop_flag=0;//停车指令


void Mid_err_get(void)
{
    dir_err = (float)(diff_adc/sum_adc);//差比和
}

//输出的Position_dif范围在-1`1之间
float Position_Control(void)
{

    Mid_err_get();   //dir_err = L1-L2;   err最大值0.6      0.6x=1  x=1/0.6 等于?   1.6667
    dir_err = dir_err*0.900+dir_last_err*0.100;  //误差低通滤波

//    Road_Judge();

    Position_dif = dir_kp*dir_err + dir_kd*(dir_err-dir_last_err);
    //printf("DIF : %lf",Speed_dif);
    dir_last_err=dir_err;

    if(Position_dif>=1.00)Position_dif=1.00;     //输出限幅
    if(Position_dif<=-1.00)Position_dif=-1.00;


    return Position_dif;
}




float Speed_Control(void)
{
       zuo_real_speed = zuo_real_speed_add/8;//速度平均滤波，分母为控制周期对于采集周期的倍数
       you_real_speed = you_real_speed_add/8;

       you_real_speed_add = 0;//积分归零
       zuo_real_speed_add = 0;

       real_speed_last = real_speed;
       real_speed = (sint32)((zuo_real_speed+you_real_speed)/2);//左右轮的平均值为车轴中心速度，既车速
       real_speed = 0.9*real_speed + 0.1*real_speed_last;//低通滤波
       //printf("REAL SPEED = %d ", real_speed);


      speed_err2 = speed_err1;
      speed_err1 = speed_err;
      speed_err = Target_speed - real_speed;

//      Incremental_PI_control();


      speed_out_increment=
                              speed_kp*(speed_err-speed_err1)
                              +speed_ki*speed_err;
//                              +speed_ki*(speed_err-2*speed_err2+speed_err2);

      speed_out += speed_out_increment;

    if(speed_out>=0.85)speed_out=0.85;
    if(speed_out<=-0.85)speed_out=-0.85;
    //printf("SPEED OUT = %lf ", speed_out);
    return speed_out;
}


//速度环参数调整  特殊元素控制
void Incremental_PI_control(void)
{


}

//pid参数初始化 方便vofa调参数
void PID_init(void)
{
    dir_kp=1.2;
    dir_kd=20.0;
    Target_speed=50;


    servo_duty=730;

    speed_kp=0.0060;
    speed_ki=0.0020;//16
}

void Position_PD_control(int dir)
{
    if(dir==1)   //测试速度
    {
        if(dir_err<0.20 || dir_err>(-0.20) )
        {
            dir_kp=1.0;
            dir_kd=11.0;
            Target_speed=70;
        }
        if(dir_err>0.20 || dir_err<(-0.20) )
        {
            dir_kp=4.0;
            dir_kd=60.0;
            Target_speed=60;
        }
        if(dir_err > 0.40 || dir_err < (-0.40) )
        {
            dir_kp=7.00;
            dir_kd=110.0;
            Target_speed=60;
        }
        if(Round_Flag)
        {
            dir_kp=5.00;
            dir_kd=70.0;
            Target_speed=50;
        }
        if(Garage_Out_Flag==1)
        {
            dir_kp=3.50;
            dir_kd=40.0;
            Target_speed=40;
        }
//        In_Garage_Num=4800;
    }


    if(dir==2)   //测试速度
    {
        if(dir_err<0.20 || dir_err>(-0.20) )
        {
            dir_kp=2.0;
            dir_kd=20.0;
            Target_speed=90;
        }
        if(dir_err>0.20 || dir_err<(-0.20) )
        {
            dir_kp=3.0;
            dir_kd=40.0;
            Target_speed=90;
        }
        if(dir_err > 0.40 || dir_err < (-0.40) )
        {
            dir_kp=4.0;
            dir_kd=70.0;
            Target_speed=80;
        }
        if(Round_Flag&&Round_statue<=2)
        {
            dir_kp=4.00;
            dir_kd=70.0;
            Target_speed=70;
        }
        if(Garage_Out_Flag==1)
        {
            dir_kp=2.50;
            dir_kd=40.0;
            Target_speed=40;
        }
//        In_Garage_Num=4400;
    }


    if(dir==3)   //测试速度
    {
        if(dir_err<0.20 || dir_err>(-0.20) )
        {
            dir_kp=2.0;
            dir_kd=20.0;
            Target_speed=100;
        }
        if(dir_err>0.20 || dir_err<(-0.20) )
        {
            dir_kp=3.0;
            dir_kd=40.0;
            Target_speed=90;
        }
        if(dir_err > 0.40 || dir_err < (-0.40) )
        {
            dir_kp=5.0;
            dir_kd=70.0;
            Target_speed=90;
        }
        if(Round_Flag&&Round_statue<=2)
        {
            dir_kp=6.00;
            dir_kd=70.0;
            Target_speed=65;
        }
        if(Garage_Out_Flag==1)
        {
            dir_kp=3.50;
            dir_kd=40.0;
            Target_speed=50;
        }
//        In_Garage_Num=4400;
    }


    if(dir==4)   //测试速度
    {
        if(dir_err<0.20 || dir_err>(-0.20) )
        {
            dir_kp=1.0;
            dir_kd=20.0;
            Target_speed=110;
        }
        if(dir_err>0.20 || dir_err<(-0.20) )
        {
            dir_kp=4.0;
            dir_kd=80.0;
            Target_speed=100;
        }
        if(dir_err > 0.40 || dir_err < (-0.40) )
        {
            dir_kp=5.0;
            dir_kd=120.0;
            Target_speed=90;
        }
        if(Round_Flag&&Round_statue<=2)
        {
            dir_kp=6.00;
            dir_kd=70.0;
            Target_speed=75;
        }
        if(Garage_Out_Flag==1)
        {
            dir_kp=3.50;
            dir_kd=40.0;
            Target_speed=50;
        }
//        In_Garage_Num=3500;
    }



    if(Garage_In_Flag==1)
    {
        Target_speed=40;
    }
    if(Final_Cross_Cnt>=4)
    {
        Target_speed=50;
    }

//    speed_kp=0.0060;
//    speed_ki=0.0020;//16
}




float Speed_dif;
float C_dir_kp=0.3;
float C_dir_kd=5.5;
float C_dir_last_err;
//dir_err  0.6 ` -0.6
float Position_Control_ChaSu(void)
{
    Speed_dif = C_dir_kp*dir_err + C_dir_kd*(dir_err-C_dir_last_err);
    C_dir_last_err=dir_err;

    if(Speed_dif>=0.5)Speed_dif=0.5;     //输出限幅
    if(Speed_dif<=-0.5)Speed_dif=-0.5;

    return Speed_dif;
}


void ChaSu_Control(void)
{
    Position_Control_ChaSu();
    if(Speed_dif > 0)
    {
        Zuo_duty -= Speed_dif/2;  //减左轮速度
        You_duty += Speed_dif/2;   //加右轮速度
    }
    if(Speed_dif <= 0)
    {
        Zuo_duty += (-Speed_dif)/2;  //加左轮速度
        You_duty -= (-Speed_dif)/2;   //减右轮速度
    }


}
