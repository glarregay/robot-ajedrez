#ifndef TABLERO_H
#define	TABLERO_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <sstream>

#include "Configuracion.h"
#include "excepciones/CasillaNoValidaException.h"
#include "excepciones/MovimientoIlegalException.h"
#include "excepciones/TableroDescalibradoException.h"
#include "DetectorPiezas.h"
#include "Estructuras.h"
#include "DisplayLCD.h"
#include "ABBchess/ABBchess.h"

using namespace std;

class Tablero {
public:    
    Tablero();
    Tablero(const Tablero& orig);
    virtual ~Tablero();
    
    string mover(string movimiento);
    void moverDesdeCamara();
    int calibrarCoordenadasExtremos(coordenadasFisicas a1, coordenadasFisicas a8, coordenadasFisicas h1);
    
    ChessMove analizarRespuestaGNUChess(string mensaje);
        
    void nuevaPartida();
    
    estadoTableroChar estadoActual();
    
private:
    
    bool calibrado;
    estadoTableroChar est;
    coordenadasFisicas a1, vx, vy;
    
    bool debug;    
        
    bool casillaValida(string casilla);
    bool casillaVacia(string casilla);
    
    char piezaEnCasilla(string casilla);
    piece piezaEnCasillaCM(string casilla);
        
    int columna(string casilla);
    int fila(string casilla);
    
    coordenadasFisicas obtenerCoordenadas(int fila, int columna);
    string reporteMovimiento(string origen, string destino, string mate);
    ChessMove reporteMovimientoCM(string origen, string destino, string mate);
    string reporteMovimientoCorregir(string origen, string destino, string mate);
    ChessMove reporteMovimientoCorregirCM(string origen, string destino, string mate);
    
    string nombrePieza(char p);
    string tipoMovimiento(string origen, string destino);
    MovementType tipoMovimientoCM(string origen, string destino);
    
    void mostrarTablero();
    
};

#endif	/* TABLERO_H */

