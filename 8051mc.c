#include <reg51.h>
sbit int1=P3^2;
sbit int2=P3^3;
#define FIRST_LINE 0x80
#define SECOND_LINE 0xC0
#define CONTROL_REGISTER 0x00
#define DATA_REGISTER 0x01
#define LCD_DATA P1
sbit LCD_ENABLE = P3^7;
sbit LCD_REGISTER_SELECT = P3^6;
void LCD_Initialization();
void LCD_MESSAGE_WRITE( unsigned int message_charactor);
void LCD_COMMAND_WRITE(char command_value);
DECLARE_OUTPUT_PORT=0X00;
sbit BUZZER_CONTROL=P3^5;
unsigned int flag,count,timer_count,rpm,display1,display2,display3,display4,display5,digit1,digit2,digit3;
void intER1() interrupt 0 //Interrupt to count no. of rotation in 1 second
{
count=count+1;
}
void timer() interrupt 3 //Interrupt to create 1s timer
{ TF1=0;
TL1=0X7f;
TH1=0X44;
	flag=flag+1;
}
void main()
{
		P1=DECLARE_OUTPUT_PORT;
		P2=DECLARE_OUTPUT_PORT;
	int1=1;
	int2=1;
			TMOD=0X10;//Timer mode 1
	BUZZER_CONTROL=1;
	while(1)
	{flag=0;
	count=0;
TL1=0X7f;
TH1=0X44;
		EA=1; //Enables the intterrupt
		ET1=1;//Enables the timer 1 Interrupt
TR1=1;//Starts the timer
		EX0=1;//Enables the External interrupt 0
		IT0=1;//Enables the Timer 0 interrupt for falling edge trigger
while(flag<19);
EA=0;         //Disables the interrupts
rpm=60*count; //To convert no. of roation in secs to no. of rotation in min
display1=rpm/10000;	
digit1=(rpm%10000);
	display2=(digit1/1000);
	digit2=(digit1%1000);
display3=(digit2/100);	
digit3=(digit2%100);
	display4=(digit3/10);
	display5=(digit3%10);
LCD_Initialization();
LCD_COMMAND_WRITE(0X80);
LCD_MESSAGE_WRITE('S');
LCD_COMMAND_WRITE(0X81);
LCD_MESSAGE_WRITE('P');
LCD_COMMAND_WRITE(0X82);
LCD_MESSAGE_WRITE('E');
LCD_COMMAND_WRITE(0X83);
LCD_MESSAGE_WRITE('E');
LCD_COMMAND_WRITE(0X84);
LCD_MESSAGE_WRITE('D');
LCD_COMMAND_WRITE(0X85);
LCD_MESSAGE_WRITE('=');
LCD_COMMAND_WRITE(0X86);
LCD_MESSAGE_WRITE(0x30+display1);
LCD_COMMAND_WRITE(0X87);
LCD_MESSAGE_WRITE(0x30+display2);
LCD_COMMAND_WRITE(0X88);
LCD_MESSAGE_WRITE(0x30+display3);
LCD_COMMAND_WRITE(0X89);
LCD_MESSAGE_WRITE(0x30+display4);
LCD_COMMAND_WRITE(0X8A);
LCD_MESSAGE_WRITE(0x30+display5);
	
}}
 void LCD_Initialization()
{      
LCD_COMMAND_WRITE(0X38);
LCD_COMMAND_WRITE(0X10);
LCD_COMMAND_WRITE(0X0C);
LCD_COMMAND_WRITE(0X06);
LCD_COMMAND_WRITE(0X01);
}
void LCD_COMMAND_WRITE(char command_value)
{ char i;
LCD_DATA= command_value;
LCD_REGISTER_SELECT= CONTROL_REGISTER;
LCD_ENABLE=1;
for(i=0;i<100;i++);
LCD_ENABLE=0;
for(i=0;i<100;i++);
}
void LCD_MESSAGE_WRITE( unsigned int message_charactor)
{ char k;
LCD_DATA= message_charactor;
LCD_REGISTER_SELECT= DATA_REGISTER;
LCD_ENABLE=1;
for(k=0;k<100;k++);
LCD_ENABLE=0;
for(k=0;k<100;k++);
}
