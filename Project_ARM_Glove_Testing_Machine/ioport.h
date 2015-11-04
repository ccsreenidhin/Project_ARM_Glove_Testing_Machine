/* 
 * File:   ioport.h
 * Author: ccsn
 *
 * Created on December 11, 2015, 10:22 PM
 */

#ifndef IOPORT_H
#define	IOPORT_H
    
    void ioinit(void); 
    void solinoidout(int);
    void pneumaticout(int);
    void ledout(int);
    char switchin(int);

#endif	/* IOPORT_H */

