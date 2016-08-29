#ifndef MUESTREADORHEXAGONAL_H
#define MUESTREADORHEXAGONAL_H

#include "Muestreador.h"

class MuestreadorHexagonal : public Muestreador {
public:
    MuestreadorHexagonal();
    MuestreadorHexagonal(const MuestreadorHexagonal& orig);
    virtual ~MuestreadorHexagonal();
    
    resultadoMuestreo muestrearDesdeCamara();
    resultadoMuestreo muestrearDesdeArchivo(string archivo);
    
private:

    // Configuraciones particulares
    int radioMuestra;
    int rangoComparacion;
    
    // Funciones de analisis del tablero
    struct color promedioPixels(Mat& imagen, int x, int y, int radio);
    resultadoMuestreo muestrearCasillas(Mat &imagen);
    
};

#endif /* MUESTREADORHEXAGONAL_H */

