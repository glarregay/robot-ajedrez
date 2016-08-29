#include "MuestreadorHexagonal.h"

MuestreadorHexagonal::MuestreadorHexagonal() {
    
    radioMuestra     = Configuracion::getParametro("RADIO_MUESTRA");
    rangoComparacion = Configuracion::getParametro("RANGO_COMPARACION");
    
}

MuestreadorHexagonal::MuestreadorHexagonal(const MuestreadorHexagonal& orig) {
}

MuestreadorHexagonal::~MuestreadorHexagonal() {
}

resultadoMuestreo MuestreadorHexagonal::muestrearDesdeCamara() {
    
    VideoCapture cap(0);
    Mat imagen;
    resultadoMuestreo out;
    
    // Inicializacion de out en 0 para el caso en que no se pueda capturar imagen
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            out.at(i).at(j).resize(1);
            out.at(i).at(j).at(0) = {0, 0, 0};
        }
    }
    
    if(debug)
        cout << "Leyendo imagen desde camara..." << endl;
    
    if(!cap.read(imagen)) {
        cout << "Error leyendo la imagen desde la camara." << endl;
        return out;
    }
    
    procesarImagen(imagen);
    out = muestrearCasillas(imagen);
    
    return out;
    
}

resultadoMuestreo MuestreadorHexagonal::muestrearDesdeArchivo(string archivo) {
    
    resultadoMuestreo out;
    
    // Inicializacion de out en 0
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            out.at(i).at(j).resize(1);
            out.at(i).at(j).at(0) = {0,0,0};
        }
    }
    
    if(debug)
        cout << "Leyendo imagen desde archivo <<" << archivo << ">> ..." << endl;
    
    Mat imagen = imread(archivo);
    
    if(imagen.data == NULL) {
        cout << "Error leyendo el archivo <<" << archivo << ">>." << endl;
        return out;
    }
    
    procesarImagen(imagen);
    out = muestrearCasillas(imagen);
        
    return out;
    
}

struct color MuestreadorHexagonal::promedioPixels(Mat& imagen, int x, int y, int radio) {
    
    int elementos = (2*radio+1)*(2*radio+1);
    Vec3b col;
    struct color resultado = {0,0,0};
        
    for(int i = x-radio; i <= x+radio; i++) {
        for(int j = y-radio; j <= y+radio; j++){
            col = imagen.at<Vec3b>(j, i);
            resultado.a += col.val[0];
            resultado.b += col.val[1];
            resultado.c += col.val[2];
        }
    }
    
    // Calculo del promedio de cada canal
    resultado.a /= elementos;
    resultado.b /= elementos;
    resultado.c /= elementos;
    
    return resultado;
    
}

resultadoMuestreo MuestreadorHexagonal::muestrearCasillas(Mat &imagen) {
            
    resultadoMuestreo out;
    
    // Muestreo el color de cada casilla
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            // Para cada casilla, tomo 7 puntos centrados
            out.at(fila).at(columna).resize(7);
            
            int coord_x, coord_y;
            
            for(int i = 0; i < 7; i++) {
                if(i == 0) {
                    coord_x = anchoCasilla*(2*fila+1)/2;
                    coord_y = altoCasilla*(2*columna+1)/2;
                } else {
                    coord_x = anchoCasilla*(2*fila+1)/2   + radioMuestra*cos(i*M_PI/3.0);
                    coord_y = altoCasilla*(2*columna+1)/2 + radioMuestra*sin(i*M_PI/3.0);
                }

                // En cada punto calculo el promedio del color de los pixeles en rango
                out.at(fila).at(columna).at(i) = promedioPixels(imagen, coord_x, coord_y, rangoComparacion);
            }           
        }
    }     
    
    return out;
    
}
