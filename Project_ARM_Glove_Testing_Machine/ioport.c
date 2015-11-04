#include "config.h"

void ioinit(void)
{
   TRISB =(0XF0) ;  //last 4 as input            
   TRISD =(0X00) ;  //all as output
   TRISC =(0XF0) ;  //1st 4 as input
   TRISA|=(1<<5) ;  //porta 5 as input(reset)
}

void solinoidout(int x)
{
  
  if(!(LATC &(1<<x)))       //portc 1st 4 as solenoid valve
  LATC |=(1<<x);
  else
  LATC &=(~(1<<x));
}

void pneumaticout(int x)
{
  x+=4;                     //portd last 4 as pneumatic actuator
  if(!(LATD &(1<<x)))
  LATD |=(1<<x);
  else
  LATD &=(~(1<<x));   
  
}

void ledout(int x)
{
  
  if(!(LATD &(1<<x)))       //portd  4 as led
  LATD |=(1<<x);
  else
  LATD &=(~(1<<x));   
}


void switchint(void)
{
    INTCON|=(1<<7)|(1<<6);
    INTCON|=(1<<3);
}

