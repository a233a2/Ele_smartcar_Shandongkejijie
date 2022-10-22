#include "headfile.h"
#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

int core0_main(void)
{
//    disableInterrupts();

    get_clk();//��ȡʱ��Ƶ��  ��ر���
    //�û��ڴ˴����ø��ֳ�ʼ��������

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

    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);    //AD�ɼ� �Լ��ٶȻ� ����

    pit_interrupt_ms(CCU6_0, PIT_CH1, 1);  //�������ɼ��������ǲɼ�

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


