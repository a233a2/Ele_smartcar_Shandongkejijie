#include "headfile.h"

float tempFloat[16];  //7

unsigned char tail[4]={0x00, 0x00, 0x80, 0x7f};

uint8 uart_buff[4];

uint32 Ecoder_ADD=0;


void Vofa_Send_Data(void)
{
    tempFloat[0]=(float)ADC_SJY[0];
    tempFloat[1]=(float)ADC_SJY[1];
    tempFloat[2]=(float)ADC_SJY[2];

    tempFloat[3]=(float)ADC_SJY[3];
    tempFloat[4]=(float)ADC_SJY[4];
    tempFloat[5]=(float)ADC_SJY[5];

    tempFloat[6]=(float)speed_kp;
    tempFloat[7]=(float)speed_ki;
    tempFloat[8]=(float)dir_err;
    tempFloat[9]=(float)dir_kp;

    tempFloat[10]=(float)dir_kd;
    tempFloat[11]=(float)Position_dif;

    tempFloat[12]=(float)MODE_SELECT;
    tempFloat[13]=(float)Final_Cross_Cnt;
    tempFloat[14]=(float)angle_yaw;

    tempFloat[15]=(float)Ecoder_ADD;



    seekfree_wireless_send_buff((unsigned char *)tempFloat, sizeof(float)*16);
    seekfree_wireless_send_buff(tail, 4);    // 发送帧尾
    //systick_delay_ms(STM0,100);
}

//在线调参 弱智写法
void Vofa_Read_Data(void)
{
    if(uart_query(UART_3,&uart_buff[0]))
    {
        if(uart_buff[0]=='A')
        {
            speed_kp+=0.0001;
        }
        if(uart_buff[0]=='B')
        {
            speed_kp-=0.0001;
        }

        if(uart_buff[0]=='C')
        {
            speed_ki+=0.0001;
        }
        if(uart_buff[0]=='D')
        {
            speed_ki-=0.0001;
        }

        if(uart_buff[0]=='E')
        {
            stop_flag=1;
        }


        if(uart_buff[0]=='F')
        {
            dir_kp+=0.1;
        }
        if(uart_buff[0]=='G')
        {
            dir_kp-=0.1;
        }

        if(uart_buff[0]=='H')
        {
            dir_kd+=0.5;
        }
        if(uart_buff[0]=='I')
        {
            dir_kd-=0.5;
        }


        if(uart_buff[0]=='J')
        {
            Target_speed+=5;
        }
        if(uart_buff[0]=='K')
        {
            Target_speed-=5;
        }
    }
}
