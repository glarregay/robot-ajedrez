#ifndef MUESTREADOR_H
#define MUESTREADOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include "../Estructuras.h"
#include "../Configuracion.h"

using namespace std;
using namespace cv;

class Muestreador {
public:
    Muestreador();
    Muestreador(const Muestreador& orig);
    virtual ~Muestreador();
    
    virtual resultadoMuestreo muestrearDesdeArchivo(string archivo) = 0;
    virtual resultadoMuestreo muestrearDesdeCamara() = 0;
    
protected:

    // Modo depuracion
    bool debug;
    bool guardarImagenes;
    
    // Parametros del tablero
    int origenTableroX, origenTableroY;
    int anchoTablero, altoTablero;
    float anchoCasilla, altoCasilla;
    
    // Parametros del procesamiento
    int blurRadio;
    int blurSigma;
    int claheGrid;
    float claheClip;
    
    int procesarImagen(Mat &salida);
    
    // Funciones de proceso de imagen
    void maximizarRango(Mat &canal);
    void acomodarHistograma(Mat &imagen);
    void autobalancearBlancos(Mat &mat);
    void RGB2rgb(Mat &imagen);
    void corregirGamma( Mat& img, double gamma );
    void incrementarSaturacion(Mat &imagen);
    void corregirColor(Mat &imagen);
    void promediarLuminancia(Mat &canal);
    
};

#endif /* MUESTREADOR_H */

