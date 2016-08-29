#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

#include <cmath>
#include <sstream>
#include <vector>
#include "../Estructuras.h"
#include "../Configuracion.h"

using namespace std;

class Clasificador {
public:
    Clasificador();
    Clasificador(const Clasificador& orig);
    virtual ~Clasificador();
    
    virtual void calibrar(resultadoMuestreo tab) = 0;
    virtual estadoTableroInt clasificar(resultadoMuestreo tab) = 0;
    
protected:
    
    // Modo depuracion
    bool debug;
    
    // Variables para calibracion
    struct referencias ref_calibracion;
    struct referencias calibracion[16];
    
    // Funciones utiles
    float distanciaEuclidiana(struct color v1, struct color v2);
    int minimo(float a, float b, float c, float d);
    
    // Funciones debug
    string mostrarReferencias();
    string mostrarColores(resultadoMuestreo r);
    string mostrarArff(resultadoMuestreo r, estadoTableroInt in);
    void mostrarClasificacion(estadoTableroInt in);

};

#endif /* CLASIFICADOR_H */

