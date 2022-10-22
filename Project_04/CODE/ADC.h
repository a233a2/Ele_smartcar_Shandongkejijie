

extern int16 L1;
extern int16 L2;
extern int16 L3;
extern int16 R1;
extern int16 R2;
extern int16 R3;

extern int16 ADC_SJY[6];


extern int16 sum_adc;
extern int16 diff_adc;

void ADC_Read_SJY(void);

void ADC_Init(void);
void Encoder_get_speed(void);
