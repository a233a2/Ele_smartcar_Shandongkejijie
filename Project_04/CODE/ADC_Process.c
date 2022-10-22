#include "headfile.h"

uint8 Element_Processing_Flag=1; //元素正在处理标志位

uint8 Round_Flag=0;         //环岛
uint8 Round_statue=0;       //环岛状态标志位


uint8 Cross_Flag=0;          //十字
uint8 Garage_In_Flag=0;       //入库
uint8 Garage_Out_Flag=1;       //出
uint8 Out_statue=1;
uint8 In_statue=0;

uint16 Round_Cnt_Boring=0;


int16 Round_Turn1,Round_Angle1;  //环岛入环打脚 环岛入环角度积分
int16 Round_AngleIn;   //环岛内角度积分
int16 Round_Turn2,Round_Angle2;  //环岛出环打脚 环岛出环积分

uint8 Final_Cross_Cnt=0;  //等于8的时候开始积分
uint16 Cross_boring=0;  //防止二次判断计数器

uint8 Round_Cnt=0;

uint16 In_Garage_Num;


//CPU1 main

//环岛即是斜八的差值绝对值小于某个值，横电感，斜八电感的乘积大于某个值，当竖电感产生差值时再进入入环状态
void Element_Judge(void)
{
    if(Element_Processing_Flag==0)
    {
        if(Round_Cnt!=2)
        {
            Round_Judge();
        }
        if(Round_Flag==0&&Round_Cnt==2)    //环岛两次可以关掉 节省单片机资源
        {
            Final_Cross_Read();
        }
    }
}

//环岛判断
void Round_Judge(void)  //环岛初步判断  2800 400 600   +++    2200 2400 2700
{
    if((L3-R1)>=2000  &&  R3>=3300)
    {
        if(R1<=2000 && L2<=1500 )
        {
            Round_Flag=1;
            Round_statue=1;
            Element_Processing_Flag=1;
            Control_Flag=1;  //接管控制
        }
    }
}






void Element_Do(void)
{
    if(Round_Flag)
    {
        Round_Road_Process();
    }
    if(Cross_Flag)
    {
        Cross_Read();
    }
}






//int Round_Turn1,Round_Angle1;  //环岛入环打脚 环岛入环角度积分  -90  -70
//int Round_AngleIn;   //环岛内角度积分  -200
//int Round_Turn2,Round_Angle2;  //环岛出环打脚 环岛出环积分  -70  -100



void Round_data(void)
{
    switch (MODE_SELECT)
    {
        case 1:
        {
            Round_Turn1=-110;  //环岛入环打脚
            Round_Angle1=-70;   //环岛入环角度积分
            Round_AngleIn=-180;
            Round_Turn2=-75;
            Round_Angle2=-130;
            break;
        }
        case 2:
        {
            Round_Turn1=-110;  //环岛入环打脚
            Round_Angle1=-70;   //环岛入环角度积分
            Round_AngleIn=-180;

            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
        case 3:
        {
            Round_Turn1=-110;  //环岛入环打脚
            Round_Angle1=-70;   //环岛入环角度积分
            Round_AngleIn=-200;
            Round_Turn2=-80;
            Round_Angle2=-100;
            break;
        }
        case 4:
        {
            Round_Turn1=-110;  //环岛入环打脚
            Round_Angle1=-70;   //环岛入环角度积分
            Round_AngleIn=-200;
            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
        case 5:
        {
            Round_Turn1=-90;  //环岛入环打脚
            Round_Angle1=-70;   //环岛入环角度积分
            Round_AngleIn=-200;
            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
    }
}


//环岛处理 固定打脚 陀螺仪记角度 仅右环岛
void Round_Road_Process(void)
{
    switch (Round_statue)
    {
        case 1:
        {
            Control_Flag=1;  //接管控制
            Element_Processing_Flag=1;
            Round_statue=2;
            break;
        }

        case 2:
        {
            Control_Flag=1;  //接管控制
            Servo_Duty = Round_Turn1;   //Round_Turn1;

            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_Angle1;  //1设定期望角度值  //Round_Angle1;
                Angle_CNT_Flag=1;  //开角度计数器
            }
            if(ang_err<=10.00&&Angle_CNT_Flag==1)   //到达设定角度
            {
                angle_yaw=0;

                Round_statue=3;
                Angle_CNT_Flag=0;
                Control_Flag=0;  //取消控制 环内PID
            }
            break;
        }
        case 3:   //环内
        {
            Control_Flag=0;  //切换PID控制
            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_AngleIn;  //1设定期望角度值 Round_AngleIn
                Angle_CNT_Flag=1;  //开角度计数器
            }
            if(ang_err<=20.00&&Angle_CNT_Flag==1)   //到达设定角度
            {
//                        Fix_Line_Flag=0;
                Round_statue=4;
                Angle_CNT_Flag=0;
                Control_Flag=1;  //提前接管控制

            }
            break;
        }
        case 4:
        {
            Control_Flag=1;  //接管控制
            Servo_Duty=Round_Turn2;  // Round_Turn2
            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_Angle2;  //1设定期望角度值  Round_Angle2
                Angle_CNT_Flag=1;  //开角度计数器
            }
            if(ang_err<=10.00&&Angle_CNT_Flag==1)   //到达设定角度
            {
//                        Fix_Line_Flag=0;
                Round_statue=5;
                Angle_CNT_Flag=0;
                Control_Flag=0;  //接管控制
            }
            break;
        }
        case 5:
        {
            Control_Flag=0;  //接管控制
//            Servo_Duty=0;
            Round_Cnt_Boring++;  //之后啥也不干 防止下一步误判

            if(Round_Cnt_Boring>=500)  //环岛大结局
            {
                Round_Cnt_Boring=0;
                Round_statue=0;
                Round_Flag=0;
                Round_Cnt_Boring=0;
                Element_Processing_Flag=0;
                Round_Cnt++;
            }

        }
    }



}


void Out_Garage(void)
{
    if(Garage_Out_Flag==1)
    {
        switch (Out_statue)
        {
            case 1:   //等待充电完成
            {
                Target_speed=20;
                Control_Flag=1;  //接管控制
                Element_Processing_Flag=1;
                Out_statue=2;
                break;
            }
            case 2:   //充电完成后延时 直线行驶5FPS
            {
                Servo_Duty=70;
                Control_Flag=1;  //接管控制
                if(Angle_CNT_Flag==0)
                {
                    angle_yaw=0;
                    Target_Z_angle=80.00;  //1设定期望角度值
                    Angle_CNT_Flag=1;  //开角度计数器
                }
                if(ang_err<=10.00 && Angle_CNT_Flag==1)   //到达设定角度
                {
                    Control_Flag=0;  //取消控制
//                    Servo_Duty=0;
                    Garage_Out_Flag=0;
                    Element_Processing_Flag=0;
                    Angle_CNT_Flag=0;
                    Control_Flag=0;  //取消控制
                }
            }
        }
    }
}


void In_Garage(void)   //549843
{
    if(Ecoder_ADD>=In_Garage_Num)  //MODE1 没灯板 535400
    {
        Garage_In_Flag=1;
        In_statue=1;
        Element_Processing_Flag=1;
        Control_Flag=1;  //接管控制
        Ecoder_ADD=0;
    }
    if(Garage_In_Flag==1)
    {
        switch (In_statue)
        {
            case 1:
            {
                Target_speed=20;
                Control_Flag=1;  //接管控制
                Element_Processing_Flag=1;
                In_statue=2;
                Servo_Duty=100;
                break;
            }
            case 2:
            {
                Servo_Duty=90;
                Control_Flag=1;  //接管控制
                if(Angle_CNT_Flag==0)
                {
                    angle_yaw=0;
                    Target_Z_angle=90.00;  //1设定期望角度值
                    Angle_CNT_Flag=1;  //开角度计数器
                }
                if(ang_err<=10.00&&Angle_CNT_Flag==1)   //到达设定角度
                {
                    angle_yaw=0;
                    stop_flag=1;
                    Target_speed=0;
                    Servo_Duty=0;
                    Garage_In_Flag=0;
                    Element_Processing_Flag=0;
                    Angle_CNT_Flag=0;
                }
            }
        }
    }
}


void Final_Cross_Read(void)
{
    if(L2>=2800 && R2>=2800)
    {
        if(R1<=1200||L3<=1200)
        {
            Cross_Flag=1;
            Element_Processing_Flag=1;
        }
    }
}

void Cross_Read(void)
{
    Cross_boring++;
    if(Cross_boring>=300)
    {
        Cross_boring=0;
        Cross_Flag=0;
        Final_Cross_Cnt++;
        Element_Processing_Flag=0;

    }
}
