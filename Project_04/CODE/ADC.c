#include "headfile.h"

//���У����ֵ��������ֱ������ѭ�������Ƕ�����ı仯��֪����б��к���ֱ���

//����У���ֱ���������ֵ��������˵����Ϊ0�������ڲ�ͬ�ĳ���˵������ܲ�̫һ�����е����Ϊ0���еĲ�Ϊ0��
//����ƫ��ܴ����ֵ��ͬ��������н�ǿ�ĸ�֪������б�����һ�㡣

//б��У����ֵ�ж��������֪�ǳ�ǿ�ң������жϻ����������Ԫ�أ��������������ߣ��������ڵ���������ѭ����

int16 L1,L2,L3,R1,R2,R3;  //L1 R3 ��  L2  R2 ��ֱ  L3 R1 б��
int16 ad_sum1, ad_sum2, ad_sum3, ad_diff1, ad_diff2, ad_diff3;

int16 ADC_SJY[6];

int16 sum_adc,diff_adc;

void ADC_Init(void)
{
    adc_init(ADC_1, ADC1_CH8_A24);
    adc_init(ADC_1, ADC1_CH9_A25);
    adc_init(ADC_2, ADC2_CH3_A35);
    adc_init(ADC_1, ADC1_CH5_A21);
    adc_init(ADC_1, ADC1_CH1_A17);
    adc_init(ADC_0, ADC0_CH13_A13);


}



//�Ŷ�ʱ���жϸ�Ƶ��ȡ�������
void ADC_Read_SJY(void)
{
    L1=adc_mean_filter(ADC_1, ADC1_CH8_A24, ADC_12BIT, 50);
    L2=adc_mean_filter(ADC_1, ADC1_CH9_A25, ADC_12BIT, 50);
    L3=adc_mean_filter(ADC_2, ADC2_CH3_A35, ADC_12BIT, 50);

    R1=adc_mean_filter(ADC_1, ADC1_CH5_A21, ADC_12BIT, 50);
    R2=adc_mean_filter(ADC_1, ADC1_CH1_A17, ADC_12BIT, 50);
    R3=adc_mean_filter(ADC_0, ADC0_CH13_A13, ADC_12BIT, 50);

    ADC_SJY[0] = L1;
    ADC_SJY[1] = L2;
    ADC_SJY[2] = L3;
    ADC_SJY[3] = R1;
    ADC_SJY[4] = R2;
    ADC_SJY[5] = R3;

    ad_sum1 = L1 + R1;
    ad_sum2 = L2 + R2;
    ad_sum3 = L3 + R3;

    ad_diff1 = L1 - R1;
    ad_diff2 = L2 - R2;
    ad_diff3 = L3 - R3;

    sum_adc= 0.5*ad_sum1+ 0.35*ad_sum2+ 0.15*ad_sum3;

    diff_adc= 0.5*ad_diff1+ 0.35*ad_diff2+ 0.15*ad_diff3;
}





















