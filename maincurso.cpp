#include <cstdlib>
#include <sstream>
#include <chrono>
#include "Configuracion.h"
#include "muestreadores/MuestreadorCuadrado.h"
#include "muestreadores/MuestreadorHexagonal.h"
#include "clasificadores/ClasificadorKMedoids.h"
#include "clasificadores/ClasificadorVotacion.h"
#include "clasificadores/ClasificadorJ48.h"

using namespace std;

float anchoCasilla, altoCasilla;

string padNumero(int num, char pad, int len) {
    
    stringstream ss; ss << num;
    
    string str = ss.str();
    if(len > str.size())
    	str.insert(0, len - str.size(), pad);
    
    return str;
    
}

void pintarImagen(string archivoEntrada, string archivoSalida, estadoTableroInt resultado) {
    
    Mat imagen = imread(archivoEntrada);
    
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            float x = anchoCasilla*(2*columna+1)/2;
            float y = altoCasilla*(2*fila+1)/2;
            Scalar color;
            
            if(resultado.at(fila).at(columna) == 0)
                color = Scalar(128, 128, 128);
            else if(resultado.at(fila).at(columna) == 1)
                color = Scalar(255, 255, 255);
            else
                color = Scalar(0,0,0);
            
            rectangle(imagen, Point(x-20, y-20), Point(x+20, y+20), color, 4);
        }
    }
    
    imwrite(archivoSalida, imagen);

}

int contarElementos(estadoTableroInt in, int elemento) {
    
    int contador = 0;
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (in.at(i).at(j) == elemento)
                contador++;
        }
    }
    
    return contador;
    
}

int main(int argc, char** argv) {

    Configuracion::leerConfiguracion();
    
    anchoCasilla = Configuracion::getParametro("ANCHO_TABLERO") / 8;
    altoCasilla  = Configuracion::getParametro("ALTO_TABLERO")  / 8;
    
    //Muestreador*  m = new MuestreadorHexagonal();
    Muestreador*  m = new MuestreadorCuadrado();
    
    //Clasificador* c = new ClasificadorVotacion();
    Clasificador* c = new ClasificadorKMedoids();
    //Clasificador* c = new ClasificadorJ48();
    
    estadoTableroInt salidaClasificador;
    
    int tiemposEjecucion[80];
    int piezasBlancas = 0, piezasNegras = 0, casillasVacias = 0;
    
    string refConLuz  = "/home/guille/testbot/cl-ref.jpg";
    string refSinLuz  = "/home/guille/testbot/sl-ref.jpg";
    string baseConLuz = "/home/guille/testbot/cl/cl-";
    string baseSinLuz = "/home/guille/testbot/sl/sl-";
    string baseOutput = "/home/guille/testbot/out/km-";
    
    c->calibrar(m->muestrearDesdeArchivo(refConLuz));
    
    for(int i = 1; i < 41; i++) {
        string archivoEntrada    = baseConLuz + padNumero(i, '0', 2) + ".jpg";
        string archivoEntradaRec = baseConLuz + "rec-" + padNumero(i, '0', 2) + ".jpg";
        string archivoSalida     = baseOutput + "cl-" + padNumero(i, '0', 2) + ".jpg";
        
        resultadoMuestreo rm = m->muestrearDesdeArchivo(archivoEntrada);
        
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
        
        salidaClasificador = c->clasificar(rm);
        
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        
        tiemposEjecucion[i-1] = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
        
        pintarImagen(archivoEntradaRec, archivoSalida, salidaClasificador);
        
        piezasBlancas  += contarElementos(salidaClasificador, 1);
        piezasNegras   += contarElementos(salidaClasificador, -1);
        casillasVacias += contarElementos(salidaClasificador, 0);
        
    }
    
    c->calibrar(m->muestrearDesdeArchivo(refSinLuz));
    
    for(int i = 1; i < 41; i++) {
        string archivoEntrada    = baseSinLuz + padNumero(i, '0', 2) + ".jpg";
        string archivoEntradaRec = baseSinLuz + "rec-" + padNumero(i, '0', 2) + ".jpg";
        string archivoSalida     = baseOutput + "sl-" + padNumero(i, '0', 2) + ".jpg";
        
        resultadoMuestreo rm = m->muestrearDesdeArchivo(archivoEntrada);
        
        chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
        
        salidaClasificador = c->clasificar(rm);
        
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        
        tiemposEjecucion[40 + i-1] = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        
        pintarImagen(archivoEntradaRec, archivoSalida, salidaClasificador);
        
        piezasBlancas  += contarElementos(salidaClasificador, 1);
        piezasNegras   += contarElementos(salidaClasificador, -1);
        casillasVacias += contarElementos(salidaClasificador, 0);
        
    }
    
    cout << "t = [ ";
    
    for(int i = 0; i < 80; i++) {
        cout << tiemposEjecucion[i];
        if(i != 79)
            cout << ",";
    }
    
    cout << " ];" << endl;
    
    cout << "PB = " << piezasBlancas << ", PN = " << piezasNegras << ", CV = " << casillasVacias << endl;
    return 0;
    
}

