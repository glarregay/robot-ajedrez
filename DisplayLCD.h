#ifndef DISPLAYLCD_H
#define DISPLAYLCD_H

#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>

using namespace std;

class DisplayLCD {
public:
    
    static void escribirLCD(string mensaje, int linea);
    static void borrarLCD();
    
private:
    
    DisplayLCD();
    virtual ~DisplayLCD();
    
    int fd;
    static DisplayLCD* instancia;
    
    static DisplayLCD* getInstancia();

};

#endif /* DISPLAYLCD_H */

