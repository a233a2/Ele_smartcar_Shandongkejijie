

extern uint8 Element_Processing_Flag; //Ԫ�����ڴ����־λ

extern uint8 Round_Flag;         //����

extern uint8 Round_statue;       //����״̬��־λ


extern uint8 Cross_Flag;          //ʮ��
extern uint8 Garage_In_Flag;       //���
extern uint8 Garage_Out_Flag;       //��

extern int16 Round_Turn1;//�����뻷��� �����뻷�ǶȻ���
extern int16 Round_Angle1;

extern int16 Round_AngleIn;   //�����ڽǶȻ���

extern int16 Round_Turn2;//����������� ������������
extern int16 Round_Angle2;

extern uint16 Round_Cnt_Boring;

extern uint8 Final_Cross_Cnt;  //����8��ʱ��ʼ����
extern uint16 In_Garage_Num;


void Element_Judge(void);
void Element_Do(void);

void Round_Judge(void);
void Round_Judge2(void);   //�����뻷�ж�

void Round_data(void);
void Round_Road_Process(void);   //����״̬��

void Out_Garage(void);
void In_Garage(void);   //549843

void Final_Cross_Read(void);
void Cross_Read(void);

