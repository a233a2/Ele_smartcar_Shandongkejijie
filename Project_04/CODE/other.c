#include "headfile.h"

#define SWITCH1 P11_9
#define SWITCH2 P11_6
#define SWITCH3 P11_3
#define SWITCH4 P11_2
#define SWITCH5 P13_3
#define SWITCH6 P13_2

#define SWITCH7 P13_4
#define SWITCH8 P13_5

uint8 Ring_Flag;

uint8 switch1=1,switch2=1,switch3=1,switch4=1,switch5=1,switch6=1,switch7=1,switch8=1;


void Beep_init(void)
{
    gpio_init(P00_12, GPO, 0, PUSHPULL);
}


void Beep_Ring111(void)
{
    gpio_set(P00_12,1);
    systick_delay_ms(STM0,100);
    gpio_set(P00_12,0);
    systick_delay_ms(STM0,50);

    gpio_set(P00_12,1);
    systick_delay_ms(STM0,100);
    gpio_set(P00_12,0);

}


void Beep_Ring(void)
{
    if(Element_Processing_Flag==1)
    {
        gpio_set(P00_12,1);
    }
    else
    {
        gpio_set(P00_12,0);
    }
}


void SWITCH_init(void)
{
    gpio_init(SWITCH1, GPO, 1, PUSHPULL);
    gpio_init(SWITCH2, GPO, 1, PUSHPULL);
    gpio_init(SWITCH3, GPO, 1, PUSHPULL);
    gpio_init(SWITCH4, GPO, 1, PUSHPULL);
    gpio_init(SWITCH5, GPO, 1, PUSHPULL);
    gpio_init(SWITCH6, GPO, 1, PUSHPULL);
    gpio_init(SWITCH5, GPO, 1, PUSHPULL);
    gpio_init(SWITCH6, GPO, 1, PUSHPULL);
}


void SWITCH(void)
{
    switch1=gpio_get(SWITCH1);
    switch2=gpio_get(SWITCH2);
    switch3=gpio_get(SWITCH3);
    switch4=gpio_get(SWITCH4);
    switch5=gpio_get(SWITCH5);
    switch6=gpio_get(SWITCH6);

     if(switch1==0&&switch2==1&&switch3==1&&switch4==1&&switch5==1)
     {
         MODE_SELECT=1;
     }

     if(switch1==1&&switch2==0&&switch3==1&&switch4==1&&switch5==1)
     {
         MODE_SELECT=2;
     }

     if(switch1==1&&switch2==1&&switch3==0&&switch4==1&&switch5==1)
     {
         MODE_SELECT=3;
     }

     if(switch1==1&&switch2==1&&switch3==1&&switch4==0&&switch5==1)
     {
         MODE_SELECT=4;
     }

     if(switch1==1&&switch2==1&&switch3==1&&switch4==1&&switch5==0)
     {
         MODE_SELECT=5;
     }
     if(switch6==0)
     {
         MODE_SELECT=6;
     }
}
