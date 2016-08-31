#ifndef DETECTORPIEZAS_H
#define DETECTORPIEZAS_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "Configuracion.h"
#include "Estructuras.h"
#include "clasificadores/ClasificadorVotacion.h"
#include "muestreadores/MuestreadorHexagonal.h"

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
    
private:
    
    int debug;
    estadoTableroInt estadoAnterior;
    
    Clasificador* clasificador;    
    Muestreador* proveedor;
    
    string casillaNotacion(struct casilla in);
    struct casilla buscarValor(estadoTableroInt c, int valor);
    void mostrarVector(estadoTableroInt in);
    void mostrarVectorChar(estadoTableroChar in);
    string convertirCambioEnJugada(estadoTableroInt c, int cant);
    
};

#endif /* DETECTORPIEZAS_H */

