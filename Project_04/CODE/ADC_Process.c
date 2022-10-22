#include "headfile.h"

uint8 Element_Processing_Flag=1; //Ԫ�����ڴ����־λ

uint8 Round_Flag=0;         //����
uint8 Round_statue=0;       //����״̬��־λ


uint8 Cross_Flag=0;          //ʮ��
uint8 Garage_In_Flag=0;       //���
uint8 Garage_Out_Flag=1;       //��
uint8 Out_statue=1;
uint8 In_statue=0;

uint16 Round_Cnt_Boring=0;


int16 Round_Turn1,Round_Angle1;  //�����뻷��� �����뻷�ǶȻ���
int16 Round_AngleIn;   //�����ڽǶȻ���
int16 Round_Turn2,Round_Angle2;  //����������� ������������

uint8 Final_Cross_Cnt=0;  //����8��ʱ��ʼ����
uint16 Cross_boring=0;  //��ֹ�����жϼ�����

uint8 Round_Cnt=0;

uint16 In_Garage_Num;


//CPU1 main

//��������б�˵Ĳ�ֵ����ֵС��ĳ��ֵ�����У�б�˵�еĳ˻�����ĳ��ֵ��������в�����ֵʱ�ٽ����뻷״̬
void Element_Judge(void)
{
    if(Element_Processing_Flag==0)
    {
        if(Round_Cnt!=2)
        {
            Round_Judge();
        }
        if(Round_Flag==0&&Round_Cnt==2)    //�������ο��Թص� ��ʡ��Ƭ����Դ
        {
            Final_Cross_Read();
        }
    }
}

//�����ж�
void Round_Judge(void)  //���������ж�  2800 400 600   +++    2200 2400 2700
{
    if((L3-R1)>=2000  &&  R3>=3300)
    {
        if(R1<=2000 && L2<=1500 )
        {
            Round_Flag=1;
            Round_statue=1;
            Element_Processing_Flag=1;
            Control_Flag=1;  //�ӹܿ���
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






//int Round_Turn1,Round_Angle1;  //�����뻷��� �����뻷�ǶȻ���  -90  -70
//int Round_AngleIn;   //�����ڽǶȻ���  -200
//int Round_Turn2,Round_Angle2;  //����������� ������������  -70  -100



void Round_data(void)
{
    switch (MODE_SELECT)
    {
        case 1:
        {
            Round_Turn1=-110;  //�����뻷���
            Round_Angle1=-70;   //�����뻷�ǶȻ���
            Round_AngleIn=-180;
            Round_Turn2=-75;
            Round_Angle2=-130;
            break;
        }
        case 2:
        {
            Round_Turn1=-110;  //�����뻷���
            Round_Angle1=-70;   //�����뻷�ǶȻ���
            Round_AngleIn=-180;

            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
        case 3:
        {
            Round_Turn1=-110;  //�����뻷���
            Round_Angle1=-70;   //�����뻷�ǶȻ���
            Round_AngleIn=-200;
            Round_Turn2=-80;
            Round_Angle2=-100;
            break;
        }
        case 4:
        {
            Round_Turn1=-110;  //�����뻷���
            Round_Angle1=-70;   //�����뻷�ǶȻ���
            Round_AngleIn=-200;
            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
        case 5:
        {
            Round_Turn1=-90;  //�����뻷���
            Round_Angle1=-70;   //�����뻷�ǶȻ���
            Round_AngleIn=-200;
            Round_Turn2=-70;
            Round_Angle2=-100;
            break;
        }
    }
}


//�������� �̶���� �����ǼǽǶ� ���һ���
void Round_Road_Process(void)
{
    switch (Round_statue)
    {
        case 1:
        {
            Control_Flag=1;  //�ӹܿ���
            Element_Processing_Flag=1;
            Round_statue=2;
            break;
        }

        case 2:
        {
            Control_Flag=1;  //�ӹܿ���
            Servo_Duty = Round_Turn1;   //Round_Turn1;

            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_Angle1;  //1�趨�����Ƕ�ֵ  //Round_Angle1;
                Angle_CNT_Flag=1;  //���Ƕȼ�����
            }
            if(ang_err<=10.00&&Angle_CNT_Flag==1)   //�����趨�Ƕ�
            {
                angle_yaw=0;

                Round_statue=3;
                Angle_CNT_Flag=0;
                Control_Flag=0;  //ȡ������ ����PID
            }
            break;
        }
        case 3:   //����
        {
            Control_Flag=0;  //�л�PID����
            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_AngleIn;  //1�趨�����Ƕ�ֵ Round_AngleIn
                Angle_CNT_Flag=1;  //���Ƕȼ�����
            }
            if(ang_err<=20.00&&Angle_CNT_Flag==1)   //�����趨�Ƕ�
            {
//                        Fix_Line_Flag=0;
                Round_statue=4;
                Angle_CNT_Flag=0;
                Control_Flag=1;  //��ǰ�ӹܿ���

            }
            break;
        }
        case 4:
        {
            Control_Flag=1;  //�ӹܿ���
            Servo_Duty=Round_Turn2;  // Round_Turn2
            if(Angle_CNT_Flag==0)
            {
                angle_yaw=0;
                Target_Z_angle=Round_Angle2;  //1�趨�����Ƕ�ֵ  Round_Angle2
                Angle_CNT_Flag=1;  //���Ƕȼ�����
            }
            if(ang_err<=10.00&&Angle_CNT_Flag==1)   //�����趨�Ƕ�
            {
//                        Fix_Line_Flag=0;
                Round_statue=5;
                Angle_CNT_Flag=0;
                Control_Flag=0;  //�ӹܿ���
            }
            break;
        }
        case 5:
        {
            Control_Flag=0;  //�ӹܿ���
//            Servo_Duty=0;
            Round_Cnt_Boring++;  //֮��ɶҲ���� ��ֹ��һ������

            if(Round_Cnt_Boring>=500)  //��������
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
            case 1:   //�ȴ�������
            {
                Target_speed=20;
                Control_Flag=1;  //�ӹܿ���
                Element_Processing_Flag=1;
                Out_statue=2;
                break;
            }
            case 2:   //�����ɺ���ʱ ֱ����ʻ5FPS
            {
                Servo_Duty=70;
                Control_Flag=1;  //�ӹܿ���
                if(Angle_CNT_Flag==0)
                {
                    angle_yaw=0;
                    Target_Z_angle=80.00;  //1�趨�����Ƕ�ֵ
                    Angle_CNT_Flag=1;  //���Ƕȼ�����
                }
                if(ang_err<=10.00 && Angle_CNT_Flag==1)   //�����趨�Ƕ�
                {
                    Control_Flag=0;  //ȡ������
//                    Servo_Duty=0;
                    Garage_Out_Flag=0;
                    Element_Processing_Flag=0;
                    Angle_CNT_Flag=0;
                    Control_Flag=0;  //ȡ������
                }
            }
        }
    }
}


void In_Garage(void)   //549843
{
    if(Ecoder_ADD>=In_Garage_Num)  //MODE1 û�ư� 535400
    {
        Garage_In_Flag=1;
        In_statue=1;
        Element_Processing_Flag=1;
        Control_Flag=1;  //�ӹܿ���
        Ecoder_ADD=0;
    }
    if(Garage_In_Flag==1)
    {
        switch (In_statue)
        {
            case 1:
            {
                Target_speed=20;
                Control_Flag=1;  //�ӹܿ���
                Element_Processing_Flag=1;
                In_statue=2;
                Servo_Duty=100;
                break;
            }
            case 2:
            {
                Servo_Duty=90;
                Control_Flag=1;  //�ӹܿ���
                if(Angle_CNT_Flag==0)
                {
                    angle_yaw=0;
                    Target_Z_angle=90.00;  //1�趨�����Ƕ�ֵ
                    Angle_CNT_Flag=1;  //���Ƕȼ�����
                }
                if(ang_err<=10.00&&Angle_CNT_Flag==1)   //�����趨�Ƕ�
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
