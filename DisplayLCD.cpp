#include "DisplayLCD.h"

DisplayLCD* DisplayLCD::instancia;

DisplayLCD::DisplayLCD() {
    fd = serialOpen("/dev/rfcomm0", 9600);
    
    if(fd == -1) {
        cout << "No se pudo abrir el puerto serie" << endl;
    }
    serialPutchar(fd, '#');
}

DisplayLCD::~DisplayLCD() {
    
    serialClose(fd);
    
}

void DisplayLCD::escribirLCD(string mensaje, int linea) {
    
    if(linea == 1)
        serialPutchar(getInstancia()->fd, '@');
    if(linea == 2)
        serialPutchar(getInstancia()->fd, '$');
    
    serialPuts(getInstancia()->fd, mensaje.c_str());
    
}
void DisplayLCD::borrarLCD() {
    
    serialPutchar(getInstancia()->fd, '*');
    
}

DisplayLCD* DisplayLCD::getInstancia() {
    
    if (instancia == NULL) {
        instancia = new DisplayLCD();
    }
    return instancia;
    
}
