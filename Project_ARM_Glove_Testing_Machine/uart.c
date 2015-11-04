#include"config.h"



void uartinit(void)
{
    
    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input
    SPBRG=51;
    TXSTA|=(1<<5)|(0<<4)|(1<<2);
    RCSTA=(1<<7)|(1<<4);
    BAUDCON|=(0<<3);
 //   INTCON|=(1<<7)|(1<<6);
}

void uarttx(char *s)
{
    while(*s)
        {
           while(!(TXIF));
           TXREG=*(s++);
          
        }
}


void uarttxch(unsigned char ch)
{
    while(!(TXIF));
    TXREG=ch;
}

char uartrx(void)
{
    char rx;
    while(!RCIF);
    rx=RCREG;
    return rx; 
}

