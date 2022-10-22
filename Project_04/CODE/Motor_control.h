#ifndef _motor_control_h
#define _motor_control_h






void MotorInit(void);

void ADC_Init(void);

void Loss_line_Protect(void);

void MotorControl(double motor1, double motor2);

void Motor_test(void);

void ServoInit(void);
void Servo_Control(int16 servo_duty);



#endif
