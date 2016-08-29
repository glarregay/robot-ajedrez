#ifndef DISPLAYLCD_H
#define DISPLAYLCD_H

#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>

using namespace std;

class DisplayLCD {
public:
    DisplayLCD();
    DisplayLCD(const DisplayLCD& orig);
    virtual ~DisplayLCD();
    
    void escribirLCDlinea1(string mensaje);
    void escribirLCDlinea2(string mensaje);
    void escribirLCD(string mensaje);
    void borrarLCD();
    
private:
    
    int fd;

};

#endif /* DISPLAYLCD_H */

