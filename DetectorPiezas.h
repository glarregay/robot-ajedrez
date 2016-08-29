#ifndef DETECTORPIEZAS_H
#define DETECTORPIEZAS_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "Configuracion.h"
//#include "DisplayLCD.h"
#include "Estructuras.h"
#include "clasificadores/ClasificadorVotacion.h"
#include "muestreadores/MuestreadorHexagonal.h"

//extern DisplayLCD * display;

#define ORIGEN_X_TABLERO 102
#define ORIGEN_Y_TABLERO 17
#define ANCHO_TABLERO 440
#define ALTO_TABLERO  440
#define ANCHO_CASILLA (ANCHO_TABLERO / 8.0)
#define ALTO_CASILLA (ALTO_TABLERO / 8.0)

using namespace cv;
using namespace std;

class DetectorPiezas {

public:
    DetectorPiezas();
    DetectorPiezas(const DetectorPiezas& orig);
    virtual ~DetectorPiezas();
    
    string detectarCambios(estadoTableroInt estado);
    string detectarCambios(string archivo, estadoTableroInt estado);
    estadoTableroInt convertirVectorEstado(estadoTableroChar estado);
    void generarReferencias();
    void generarReferencias(string archivo);
    estadoTableroInt obtenerVotaciones();
    estadoTableroInt obtenerVotaciones(string archivo);
    estadoTableroInt obtenerEstadoAnterior();
    
    void mostrarEstadoActual();
    string mostrarCasilla(int fila, int columna);
    string mostrarReferencias();
    void guardarImagenMuestreada();
    
private:
    
    int ancho;
    int alto;
    int debug;
    float centrosfilas[8];
    float centroscolumnas[8];
    struct referencias calibracion[16];
    struct referencias ref_calibracion;
    estadoTableroInt estadoAnterior;
    
    Clasificador* clasificador;    
    Muestreador* proveedor;
    
    struct coord coordenadaCasilla(struct casilla cas);
    struct coord coordenadaCasilla(int columna, int fila);
    
    void mostrarTablero(Mat &imagen);
    float distancia(struct color v1, struct color v2);
    int minimo(float a, float b, float c, float d);
    int maximo(float a, float b, float c, float d);
    float contar(int* vector, int elementos, int buscado);
    int votarCasilla(Mat &imagen, struct casilla cas);
    
    struct casilla buscarValor(estadoTableroInt c, int valor);
    string casillaNotacion(struct casilla in);
    void mostrarVector(estadoTableroInt in);
    void mostrarVectorChar(estadoTableroChar in);
    string convertirCambioEnJugada(estadoTableroInt c, int cant);
    
};

#endif /* DETECTORPIEZAS_H */

