#ifndef MUESTREADORCUADRADO_H
#define MUESTREADORCUADRADO_H

#include "Muestreador.h"

using namespace cv;
using namespace std;

class MuestreadorCuadrado : public Muestreador {
public:
    MuestreadorCuadrado();
    MuestreadorCuadrado(const MuestreadorCuadrado& orig);
    virtual ~MuestreadorCuadrado();
    
    resultadoMuestreo muestrearDesdeCamara();
    resultadoMuestreo muestrearDesdeArchivo(string archivo);
    
private:
    
    // Configuraciones particulares
    int radioMuestra;
    
    // Funciones de analisis del tablero
    struct color promedioPixels(Mat& imagen, int x, int y, int radio);
    resultadoMuestreo muestrearCasillas(Mat &imagen);
    
};

#endif /* MUESTREADORCUADRADO_H */

