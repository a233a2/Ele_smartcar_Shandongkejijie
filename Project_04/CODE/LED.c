#include"headfile.h"

#define L11 P33_13
#define L22 P33_12
#define L33 P33_11


#define LA P33_10
#define LB P33_9
#define LC P33_8
#define LD P33_7
#define LE P33_6

float Show_Duty=0;



void LED_Init(void)
{
        //初始化LED控制引脚
        gpio_init(L11, GPO,1, PUSHPULL);
        gpio_init(L22, GPO,1, PUSHPULL);
        gpio_init(L33, GPO,1, PUSHPULL);
        gpio_init(LA, GPO,0, PUSHPULL);
        gpio_init(LB, GPO,0, PUSHPULL);
        gpio_init(LC, GPO,0, PUSHPULL);
        gpio_init(LD, GPO,0, PUSHPULL);
        gpio_init(LE, GPO,0, PUSHPULL);
}


void Clear_LED(void)
{
    //关闭所有LED显示
    gpio_set(L11,1);
    gpio_set(L22,1);
    gpio_set(L33,1);
    systick_delay_us(STM0,1);
    gpio_set(LA,0);
    gpio_set(LB,0);
    gpio_set(LC,0);
    gpio_set(LD,0);
    gpio_set(LE,0);
}


uint8 temp=0,temp1=0;       //计算变量
uint8 num=0;                //刷新计次

//放定时器4  1ms  或者   cpu0的while(1)中 延时1ms
void Show_Voltage(void)
{
    Show_Duty = (Zuo_duty+You_duty)/2;  // 最大值1+2=1.6 1.7x=12 x=7.05  x大一点显示效果好

    temp=(uint8)(Show_Duty*30);     //获取电源电压

    num++;                          //刷新计次
    if(num>14) num=0;

    Clear_LED();

    if(num < temp)        //点亮需要点亮的LED灯
    {
        temp1 = num/3;
        switch(temp1){                          //打开行
//            case 0:  gpio_set(LA,1);break;
//            case 1:  gpio_set(LB,1);break;
//            case 2:  gpio_set(LC,1);break;
//            case 3:  gpio_set(LD,1);break;
//            case 4:  gpio_set(LE,1);break;

            case 0:  gpio_set(LE,1);break;
            case 1:  gpio_set(LD,1);break;
            case 2:  gpio_set(LC,1);break;
            case 3:  gpio_set(LB,1);break;
            case 4:  gpio_set(LA,1);break;
            default:break;
        }
        temp1 = num%3;
        switch(temp1){                          //打开列
            case 0:  gpio_set(L33,0);break;
            case 1:  gpio_set(L22,0);break;
            case 2:  gpio_set(L11,0);break;
            default:break;
        }
    }
}
