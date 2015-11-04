
#include "config.h"


void timerinit(void)
{
    T0CON=0x06;  
}


void timeronesec(void)
{
    TMR0H=0x0b;
    TMR0L=0xdb;
    T0CON|=(1<<7);
    while(!T0IF);
    T0IF=0;
    T0CON|=(0<<7);
}


void delaysec(int n)
{
    int i=0;
    for(i=0;i<n;i++);
    timeronesec();
}