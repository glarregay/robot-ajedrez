#include "ClasificadorVotacion.h"

ClasificadorVotacion::ClasificadorVotacion() {
    
    minimosVotos = Configuracion::getParametro("UMBRAL_VOTACION");
    
}

ClasificadorVotacion::ClasificadorVotacion(const ClasificadorVotacion& orig) {
}

ClasificadorVotacion::~ClasificadorVotacion() {
}

void ClasificadorVotacion::calibrar(resultadoMuestreo tab) {
    
    int indiceCO = 0, indiceCC = 0, indicePN = 0, indicePB = 0;
    ref_calibracion = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
    
    if(debug)
        cout << "Calibrando clasificador votacion." << endl;
    
    for(int i = 0; i < 16; i++) {
        calibracion[i].cc = {0, 0, 0};
        calibracion[i].co = {0, 0, 0};
        calibracion[i].pb = {0, 0, 0};
        calibracion[i].pn = {0, 0, 0};
    }
    
    // Fichas blancas
    for(int fila = 0; fila < 2; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            calibracion[ indicePB ].pb = colorCasilla(tab, fila, columna);
            ref_calibracion.pb.a += calibracion[indicePB].pb.a;
            ref_calibracion.pb.b += calibracion[indicePB].pb.b;
            ref_calibracion.pb.c += calibracion[indicePB].pb.c;
            indicePB++;
        }
    }
    
    // Fichas negras
    for(int fila = 6; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            calibracion[ indicePN ].pn = colorCasilla(tab, fila, columna);
            ref_calibracion.pn.a += calibracion[indicePN].pn.a;
            ref_calibracion.pn.b += calibracion[indicePN].pn.b;
            ref_calibracion.pn.c += calibracion[indicePN].pn.c;
            indicePN++;
        }
    }
    
    // Casillas vacías
    for(int fila = 2; fila < 6; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            // Casillas claras
            if(fila%2 != columna%2) {
                calibracion[ indiceCC ].cc = colorCasilla(tab, fila, columna);
                ref_calibracion.cc.a += calibracion[indiceCC].cc.a;
                ref_calibracion.cc.b += calibracion[indiceCC].cc.b;
                ref_calibracion.cc.c += calibracion[indiceCC].cc.c;
                indiceCC++;
            } else {
                calibracion[ indiceCO ].co = colorCasilla(tab, fila, columna);
                ref_calibracion.co.a += calibracion[indiceCO].co.a;
                ref_calibracion.co.b += calibracion[indiceCO].co.b;
                ref_calibracion.co.c += calibracion[indiceCO].co.c;
                indiceCO++;
            }
        }
    }
    
    ref_calibracion.cc.a /= 16;
    ref_calibracion.cc.b /= 16;
    ref_calibracion.cc.c /= 16;
    ref_calibracion.co.a /= 16;
    ref_calibracion.co.b /= 16;
    ref_calibracion.co.c /= 16;
    ref_calibracion.pb.a /= 16;
    ref_calibracion.pb.b /= 16;
    ref_calibracion.pb.c /= 16;
    ref_calibracion.pn.a /= 16;
    ref_calibracion.pn.b /= 16;
    ref_calibracion.pn.c /= 16;
    
    if(debug)
        cout << mostrarReferencias() << endl;
    
}

estadoTableroInt ClasificadorVotacion::clasificar(resultadoMuestreo tab){
    
    estadoTableroInt grupos, salida;
    
    if(debug)
        cout << "Clasificador votacion, entrada: " << endl << mostrarColores(tab) << endl;
        
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            grupos.at(fila).at(columna) = votarCasilla(tab, fila, columna);
        }
    }
    
    // Rotar la matriz, debido a la diferencia entre las coordenadas tablero y las coordenadas imagen
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            salida.at(columna).at(fila) = grupos.at(fila).at(columna);
        }
    }
    
    if(debug) {
        cout << "Fin de la clasificación de votacion. Tablero detectado:" << endl;
        mostrarClasificacion(salida);
    }
    
    return salida;
    
}

int ClasificadorVotacion::votarCasilla(resultadoMuestreo tab, int fila, int columna) {
    
    // 0 si casilla clara, 1 si casilla oscura
    int votosPB = 0, votosPN = 0, votosCas = 0;
    float distPB, distPN, distCC, distCO;
    
    for(int i = 0; i < 7; i++) {
        
        distPB = 0; distPN = 0; distCC = 0; distCO = 0;
        int minPB = 1000, minPN = 1000, minCC = 1000, minCO = 1000;
                
        for(int j = 0; j < 16; j++) {
            distPB = distanciaEuclidiana(tab.at(fila).at(columna).at(i), calibracion[j].pb);
            minPB = (distPB < minPB)? distPB : minPB;
            
            distPN = distanciaEuclidiana(tab.at(fila).at(columna).at(i), calibracion[j].pn);
            minPN = (distPN < minPN)? distPN : minPN;
            
            distCC = distanciaEuclidiana(tab.at(fila).at(columna).at(i), calibracion[j].cc);
            minCC = (distCC < minCC)? distCC : minCC;
            
            distCO = distanciaEuclidiana(tab.at(fila).at(columna).at(i), calibracion[j].co);
            minCO = (distCO < minCO)? distCO : minCO;
        }
        
        int menor = minimo(minPB, minPN, minCC, minCO);
        
        if (menor == 0)
            votosPB++;
        else if (menor == 1)
            votosPN++;
        else
            votosCas++;
        
    }
    
    if(debug) {
        cout << "F" << fila << "C" << columna << ": { PN=" << votosPN << ", PB=" << votosPB << " }" << endl;
    }
    
    if(votosPN > minimosVotos && votosPN > votosPB)  //(votosPN > (votosPB + votosCas))
        return -1;
    if(votosPB > minimosVotos && votosPB > votosPN)  //(votosPB > (votosPN + votosCas))
        return 1;
    
    return 0;
    
}

struct color ClasificadorVotacion::colorCasilla(resultadoMuestreo tab, int fila, int columna) {
    
    struct color res = {0,0,0};

    for(int i = 0; i < 7; i++) {
        res.a += tab.at(fila).at(columna).at(i).a;
        res.b += tab.at(fila).at(columna).at(i).b;
        res.c += tab.at(fila).at(columna).at(i).c;
    }
    
    res.a /= 7;
    res.b /= 7;
    res.c /= 7;
    
    return res;
    
}