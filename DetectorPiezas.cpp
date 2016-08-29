#include "DetectorPiezas.h"
#include "clasificadores/ClasificadorVotacion.h"
#include "muestreadores/MuestreadorHexagonal.h"

DetectorPiezas::DetectorPiezas() {
    
    clasificador = new ClasificadorVotacion();
    proveedor    = new MuestreadorHexagonal();
    
}

DetectorPiezas::DetectorPiezas(const DetectorPiezas& orig) {
}

DetectorPiezas::~DetectorPiezas() {
    
    delete clasificador;
    delete proveedor;
    
}

estadoTableroInt DetectorPiezas::obtenerVotaciones() {
    
    resultadoMuestreo tab;
    estadoTableroInt nuevoEstado;
    
    tab = proveedor->muestrearDesdeCamara();
    nuevoEstado = clasificador->clasificar(tab);
    
    estadoAnterior = nuevoEstado;
    return nuevoEstado;
    
}

estadoTableroInt DetectorPiezas::obtenerVotaciones(string archivo) {
    
    resultadoMuestreo tab;
    estadoTableroInt nuevoEstado;
    
    tab = proveedor->muestrearDesdeArchivo(archivo);
    nuevoEstado = clasificador->clasificar(tab);
    
    estadoAnterior = nuevoEstado;
    return nuevoEstado;
    
}

struct casilla DetectorPiezas::buscarValor(estadoTableroInt c, int valor) {
    
    struct casilla salida = {0,0};
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (c.at(i).at(j) == valor) {
                salida.columna = i+1;
                salida.fila = j+1;
                return salida;
            }
        }
    }
    
    return salida;
    
}

string DetectorPiezas::casillaNotacion(struct casilla in) {
    
    string salida = "";
    
    salida += (char)(in.columna+'a'-1);
    salida += (char)(in.fila+'0');
    
    return salida;
    
}

void DetectorPiezas::mostrarVector(estadoTableroInt in) {
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << in.at(i).at(j) +1;
        }
        cout << endl;
    }
    
}

void DetectorPiezas::mostrarVectorChar(estadoTableroChar in) {
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << in.at(i).at(j);
        }
        cout << endl;
    }
    
}

void DetectorPiezas::mostrarEstadoActual() {
    
    mostrarVector(obtenerVotaciones());
    
}

string DetectorPiezas::convertirCambioEnJugada(estadoTableroInt c, int cant) {
    
    string salida;
    struct casilla origen, destino;
    
    cout << endl << "Matriz de cambios detectados: cantidad: " << cant << endl;
    mostrarVector(c);
    
    switch(cant) {
        // La imagen es la misma, no hay cambios.
        case 0:
            salida = "";
            break;
            
        // Hubo un movimiento normal o de captura        
        case 2:
            // Normal  si 1 en la casilla de destino, -1 en la casilla de origen
            // Captura si 2 en la casilla de destino, -1 en la casilla de origen
            origen = buscarValor(c, -1);
            destino = buscarValor(c, 1); // Pruebo movimiento normal
            
            if(destino.columna == 0 || destino.fila == 0) {
                // Era captura nomás, buscar de nuevo
                destino = buscarValor(c, 2);
            }
            salida = casillaNotacion(origen) + casillaNotacion(destino);
            break;
            
        // Peon al paso - captura "en passant" como dicen los franceses
        case 3:
            // Esta es fácil. La casilla destino vale 1, la origen vale -1 y la
            // del peon comido vale 1.
            origen = buscarValor(c, -1);
            destino = buscarValor(c, 2);
            
            salida = casillaNotacion(origen) + casillaNotacion(destino);            
            break;
            
        // Enroque
        case 4:
            // Si a1=e1=-1, y c1=d1=1, enroque largo
            if(c.at(0).at(0)==-1 && c.at(4).at(0)==-1 && c.at(2).at(0)==1 && c.at(3).at(0)==1) {
                salida = "e1c1";
            // Si h1=e1=-1, y f1=g1=2, enroque corto
            } else if (c.at(7).at(0)==-1 && c.at(4).at(0)==-1 && c.at(5).at(0)==1 && c.at(6).at(0)==1) {
                salida = "e1g1";
            }
            break;
    }
    
    return salida;
    
}

estadoTableroInt DetectorPiezas::convertirVectorEstado(estadoTableroChar estado) {
    
    estadoTableroInt nuevoEstado;
    
    cout << "Estado que vino desde GNU Chess:" << endl;
    mostrarVectorChar(estado);
        
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {            
            if(estado.at(i).at(j) == '-') {
                nuevoEstado.at(i).at(j) = 0;
                continue;
            }
            if(islower(estado.at(i).at(j))) {
                nuevoEstado.at(i).at(j) = -1;
                continue;
            }
            if(isupper(estado.at(i).at(j))) {
                nuevoEstado.at(i).at(j) = 1;
                continue;
            }
        }
    }
    
    cout << "Estado que vino desde GNU Chess interpretado:" << endl;
    mostrarVector(nuevoEstado);
    
    return nuevoEstado;
    
}

string DetectorPiezas::detectarCambios(estadoTableroInt estado) {
    
    estadoTableroInt resultado, cambios;
    int dif = 0, cantCambios = 0;
    string salida;
    
    resultado = obtenerVotaciones();
    
    cout << endl << "Matriz del tablero antes de detectar cambios:" << endl;
    mostrarVector(resultado);
    
    for (int fila = 0; fila < 8; fila++) {        
        for (int columna = 0; columna < 8; columna++) {
            dif = resultado.at(fila).at(columna) - estado.at(fila).at(columna);
            cambios.at(fila).at(columna) = dif;
            if (dif != 0)
                cantCambios++;
        }
    }
    
    salida = convertirCambioEnJugada(cambios, cantCambios);
    
    cout << "Movimiento detectado: " << salida << endl;
    
    return salida;
    
}

string DetectorPiezas::detectarCambios(string archivo, estadoTableroInt estado) {
    
    estadoTableroInt resultado, cambios;
    int dif = 0, cantCambios = 0;
    string salida;
    
    resultado = obtenerVotaciones(archivo);
    
    cout << endl << "Matriz del tablero antes de detectar cambios (desde archivo):" << endl;
    mostrarVector(resultado);
        
    for (int fila = 0; fila < 8; fila++) {        
        for (int columna = 0; columna < 8; columna++) {
            dif = resultado.at(fila).at(columna) - estado.at(fila).at(columna);
            cambios.at(fila).at(columna) = dif;
            if (dif != 0)
                cantCambios++;
        }
    }
    
    salida = convertirCambioEnJugada(cambios, cantCambios);
    
    cout << "Movimiento detectado: " << salida << endl;
    
    return salida;
    
}

estadoTableroInt DetectorPiezas::obtenerEstadoAnterior() {
    return estadoAnterior;
}

void DetectorPiezas::generarReferencias() {
    
    resultadoMuestreo tab = proveedor->muestrearDesdeCamara();
    clasificador->calibrar(tab);
    
}

void DetectorPiezas::generarReferencias(string archivo) {
    
    resultadoMuestreo tab = proveedor->muestrearDesdeArchivo(archivo);
    clasificador->calibrar(tab);
    
}
