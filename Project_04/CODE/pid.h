


extern float dir_kp;
extern float dir_kd;

extern float dir_err;
extern float dir_last_err;

extern float Position_dif;

extern uint8 Road_statue; //1ֱ�� 2��ͨ����� 3ʮ�ֺ�����


extern float speed_kp;
extern float speed_ki;

extern sint32 real_speed;  //������  set_speed��̬����

extern float Zuo_duty;
extern float You_duty;

extern uint16 servo_duty;


extern float speed_out;

extern sint32 zuo_real_speed;
extern sint32 you_real_speed;

extern uint8 stop_flag;//ͣ��ָ��


extern float Speed_dif;
extern float C_dir_kp;
extern float C_dir_kd;



void Mid_err_get(void);


float Position_Control(void);

float Position_Control_ChaSu(void);
void ChaSu_Control(void);

float Speed_Control(void);

void Incremental_PI_control(void);

void Road_Contain(void);

void PID_init(void);


void Road_Judge(void);
void Position_PD_control(int dir);


void MODE1(void);
void MODE2(void);
void MODE3(void);
