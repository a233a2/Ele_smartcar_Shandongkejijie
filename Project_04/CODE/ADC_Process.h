

extern uint8 Element_Processing_Flag; //元素正在处理标志位

extern uint8 Round_Flag;         //环岛

extern uint8 Round_statue;       //环岛状态标志位


extern uint8 Cross_Flag;          //十字
extern uint8 Garage_In_Flag;       //入库
extern uint8 Garage_Out_Flag;       //出

extern int16 Round_Turn1;//环岛入环打脚 环岛入环角度积分
extern int16 Round_Angle1;

extern int16 Round_AngleIn;   //环岛内角度积分

extern int16 Round_Turn2;//环岛出环打脚 环岛出环积分
extern int16 Round_Angle2;

extern uint16 Round_Cnt_Boring;

extern uint8 Final_Cross_Cnt;  //等于8的时候开始积分
extern uint16 In_Garage_Num;


void Element_Judge(void);
void Element_Do(void);

void Round_Judge(void);
void Round_Judge2(void);   //环岛入环判断

void Round_data(void);
void Round_Road_Process(void);   //环岛状态机

void Out_Garage(void);
void In_Garage(void);   //549843

void Final_Cross_Read(void);
void Cross_Read(void);

