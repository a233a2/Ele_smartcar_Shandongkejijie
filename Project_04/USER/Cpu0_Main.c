#include "headfile.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

int core0_main(void)
{
//    disableInterrupts();

    get_clk();//获取时钟频率  务必保留
    //用户在此处调用各种初始化函数等

    icm20602_init_spi();
    systick_delay_ms(STM0,2);

    PID_init();
    systick_delay_ms(STM0,1);

    ADC_Init();
    systick_delay_ms(STM0,1);

    Beep_init();
    systick_delay_ms(STM0,1);

    MotorInit();
    systick_delay_ms(STM0,1);

    ServoInit();
    systick_delay_ms(STM0,1);

    Encoder_Init();
    systick_delay_ms(STM0,1);

    SWITCH_init();
    systick_delay_ms(STM0,1);

    seekfree_wireless_init();
    systick_delay_ms(STM0,1);



    Beep_Ring111();

    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);    //AD采集 以及速度环 方向环

    pit_interrupt_ms(CCU6_0, PIT_CH1, 1);  //编码器采集和陀螺仪采集

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    while (TRUE)
    {
        SWITCH();
        Round_data();
        Vofa_Send_Data();
        Vofa_Read_Data();
    }
}

#pragma section all restore


