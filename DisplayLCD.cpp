#include "DisplayLCD.h"

DisplayLCD::DisplayLCD() {
    fd = serialOpen("/dev/rfcomm0", 9600);
    
    if(fd == -1) {
        cout << "No se pudo abrir el puerto serie" << endl;
    }
    serialPutchar(fd, '#');
}

DisplayLCD::DisplayLCD(const DisplayLCD& orig) {
}

DisplayLCD::~DisplayLCD() {
    
    serialClose(fd);
    
}

void DisplayLCD::escribirLCDlinea1(string mensaje) {
    
    serialPutchar(fd, '@');
    serialPuts(fd, mensaje.c_str());
    
}
void DisplayLCD::escribirLCDlinea2(string mensaje) {
    
    serialPutchar(fd, '$');
    serialPuts(fd, mensaje.c_str());
    
}
void DisplayLCD::escribirLCD(string mensaje) {
    
    serialPuts(fd, mensaje.c_str());
    
}
void DisplayLCD::borrarLCD() {
    
    serialPutchar(fd, '*');
    
}
