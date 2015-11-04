/*
 * File:   main.c
 * Author: ccsn
 *
 * Created on December 11, 2015, 10:27 PM
 */
#include "config.h"

int ch;
void interrupt ISR()
{
  if(RBIF)
  {
    if(PORTB&(0X04))
    {
       pneumaticout(0); 
    }
    if(PORTB&(0X05));
    {
       pneumaticout(1);
    }
    if(PORTB&(0X06));
    {
       pneumaticout(2);  
    }
    if(PORTB&(0X07));
    {
       pneumaticout(3);  
    }
    RBIF=0;
  }
}

void communication(void);
void offsetread(void);
void test1(void);
void test2(void);
void comparison(void);
void ejectbad(void);
void ejectgood(void);
int good[4]={0};


void main(void) 
{
        ioinit();                                   //initialize all modules
        adcinit();
        timerinit();
        uartinit();
    while(1)
    {
        while((PORTA&0x20)==0x20);
        communication();
        offsetread();
        while((LATD&0XF0)==0XF0);
        test1();
        delaysec(25);
        test2();
        comparison();
        while(PORTA&(1<<5));
            delaysec((int)glove.Air_eject_time_for_bad);
            ejectbad();
            delaysec((int)glove.Air_eject_time_for_good);
            ejectgood();
           
           
    }
   
    while(1)  ;
    return ;
}

void communication(void)
{
  char rx, tx[3];
  ID: uarttx("id1") ;
  rx=uartrx();
  if(rx!=1)
  goto ID;
  else
  uarttxch('1');
  glove.Gloves_Size=uartrx();
  glove.Inflate_time_1=uartrx();
  glove.Inflate_time_2=uartrx();
  glove.Air_eject_time_for_bad=uartrx();
  glove.Air_eject_time_for_good=uartrx();
  value.Nominal_Pressure=uartrx();
  
  value.Nominal_Pressure=(uartrx()<<8);
  value.Lower_Threshold=uartrx();
  value.Lower_Threshold=(uartrx()<<8);
  value.Upper_Threshold=uartrx();
  value.Upper_Threshold=(uartrx()<<8);
  value.Negative_Tolerance=uartrx();
  value.Negative_Tolerance=(uartrx()<<8);
  value.Positive_Tolerance=uartrx();
  value.Positive_Tolerance=(uartrx()<<8);
  
  uarttxch('1');
  uarttx(sensor[0].sensor_offset);
  uarttx(sensor[0].sensor_P1);
  uarttx(sensor[0].sensor_P2);
  uarttx(sensor[0].sensor_P3);
  uarttx(sensor[0].sensor_P4);
  uarttxch(sensor[0].sensor_Status);
  
  uarttx(sensor[1].sensor_offset);
  uarttx(sensor[1].sensor_P1);
  uarttx(sensor[1].sensor_P2);
  uarttx(sensor[1].sensor_P3);
  uarttx(sensor[1].sensor_P4);
  uarttxch(sensor[1].sensor_Status);
  
  uarttx(sensor[2].sensor_offset);
  uarttx(sensor[2].sensor_P1);
  uarttx(sensor[2].sensor_P2);
  uarttx(sensor[2].sensor_P3);
  uarttx(sensor[2].sensor_P4);
  uarttxch(sensor[2].sensor_Status);
  
  uarttx(sensor[3].sensor_offset);
  uarttx(sensor[3].sensor_P1);
  uarttx(sensor[3].sensor_P2);
  uarttx(sensor[3].sensor_P3);
  uarttx(sensor[3].sensor_P4);
  uarttxch(sensor[3].sensor_Status);
  
 while((rx=uartrx())==1);
 ledout(0);
 ledout(1);
 ledout(2);
 ledout(3);
 delaysec(1);
 ledout(0);
 ledout(1);
 ledout(2);
 ledout(3);
  
}

void test1(void)
{
        ledout(0);
        ledout(1);
        ledout(2);
        ledout(3);
        solinoidout(0);
        solinoidout(1);
        solinoidout(2);
        solinoidout(3);
        delaysec(glove.Inflate_time_1);
        solinoidout(0);
        solinoidout(1);
        solinoidout(2);
        solinoidout(3);
        {                                   //test 1
        sensor[0].sensor_P1=adcread(0);
        sensor[1].sensor_P1=adcread(1);
        sensor[2].sensor_P1=adcread(2);
        sensor[3].sensor_P1=adcread(3);
        delaysec(25);
        sensor[0].sensor_P2=adcread(0);
        sensor[1].sensor_P2=adcread(1);
        sensor[2].sensor_P2=adcread(2);
        sensor[3].sensor_P2=adcread(3);
        } 
        ledout(0);
        ledout(1);
        ledout(2);
        ledout(3);
}

void test2(void)
{
        ledout(0);
        ledout(1);
        ledout(2);
        ledout(3);
        solinoidout(0);
        solinoidout(1);
        solinoidout(2);
        solinoidout(3);
        delaysec(glove.Inflate_time_2);
        solinoidout(0);
        solinoidout(1);
        solinoidout(2);
        solinoidout(3);
        {                                   //test 2
        sensor[0].sensor_P3=adcread(0);
        sensor[1].sensor_P3=adcread(1);
        sensor[2].sensor_P3=adcread(2);
        sensor[3].sensor_P3=adcread(3);
        delaysec(25);
        sensor[0].sensor_P4=adcread(0);
        sensor[1].sensor_P4=adcread(1);
        sensor[2].sensor_P4=adcread(2);
        sensor[3].sensor_P4=adcread(3);
        }
        ledout(0);
        ledout(1);
        ledout(2);
        ledout(3);
}

void offsetread()
{
        sensor[0].sensor_offset=adcread(0);
        sensor[1].sensor_offset=adcread(1);
        sensor[2].sensor_offset=adcread(2);
        sensor[3].sensor_offset=adcread(3);
}

void ejectbad(void)
{
    int i;
    for(i=0;i<4;i++)
    {
        if(good[i]==0)
            {
            pneumaticout(i);
            solinoidout(i);
            }
    }
    delaysec(1);
    for(i=0;i<4;i++)
    {  
        if(good[i]==0)
        solinoidout(i);
    }
}

void ejectgood(void)
{
    int i;
    for(i=0;i<4;i++)
    {
        if(good[i]==1)
            {
            pneumaticout(i);
            solinoidout(i);
            }
    }
    delaysec(1);
    for(i=0;i<4;i++)
    {  
        if(good[i]==1)
        solinoidout(i);
    }
}


void comparison(void)
{
   int i;
   for(i=0;i<4;i++)
   {
   if(((sensor[i].sensor_offset+sensor[i].sensor_P1)<=value.Lower_Threshold) && ((sensor[i].sensor_offset+sensor[i].sensor_P2)<=value.Upper_Threshold) )
       if(((sensor[i].sensor_offset+sensor[i].sensor_P3)<=value.Lower_Threshold )&& ((sensor[i].sensor_offset+sensor[i].sensor_P4)<=value.Upper_Threshold) )
       good[i]=1;
   }
}
