
#include"config.h"

unsigned int pres;
void adcinit(void)
{
    ADCON0=0X00;
    ADCON1=0X0A;
    ADCON2=0x99;

}

int adcread(int channel)
{
    int x;
    ADCON0=0X00;
    ADCON0|=channel<<2;
    ADCON0|=(1<<0);
    ADCON0|=(1<<1);
    while((ADCON0&(1<<1)));
    x=ADRESH;
    pres=ADRESL|(x<<7);
    return pres;
}
