#include "../Configuracion.h"
#include "ClasificadorKMedoids.h"

ClasificadorKMedoids::ClasificadorKMedoids() {    
}

ClasificadorKMedoids::ClasificadorKMedoids(const ClasificadorKMedoids& orig) {
}

ClasificadorKMedoids::~ClasificadorKMedoids() {
}

void ClasificadorKMedoids::calibrar(resultadoMuestreo tab) {
    
    int indiceCO = 0, indiceCC = 0, indicePN = 0, indicePB = 0;
    ref_calibracion = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
    
    if(debug)
        cout << "Calibrando clasificador k-medoids." << endl;
    
    for(int i = 0; i < 16; i++) {
        calibracion[i].cc = {0, 0, 0};
        calibracion[i].co = {0, 0, 0};
        calibracion[i].pb = {0, 0, 0};
        calibracion[i].pn = {0, 0, 0};
    }    
    
    // Fichas blancas
    for(int fila = 0; fila < 2; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            calibracion[ indicePB ].pb = tab.at(fila).at(columna).at(0);
            ref_calibracion.pb.a += calibracion[indicePB].pb.a;
            ref_calibracion.pb.b += calibracion[indicePB].pb.b;
            ref_calibracion.pb.c += calibracion[indicePB].pb.c;
            indicePB++;
        }
    }
    
    // Fichas negras
    for(int fila = 6; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            calibracion[ indicePN ].pn = tab.at(fila).at(columna).at(0);
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
                calibracion[ indiceCC ].cc = tab.at(fila).at(columna).at(0);
                ref_calibracion.cc.a += calibracion[indiceCC].cc.a;
                ref_calibracion.cc.b += calibracion[indiceCC].cc.b;
                ref_calibracion.cc.c += calibracion[indiceCC].cc.c;
                indiceCC++;
            } else {
                calibracion[ indiceCO ].co = tab.at(fila).at(columna).at(0);
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

estadoTableroInt ClasificadorKMedoids::clasificar(resultadoMuestreo tab){
    
    struct referencias medoides;
    estadoTableroInt grupos, salida;
    float costo_act = 1e6, costo_ant = 1e6;
    
    // Inicio el algoritmo con los puntos de referencia
    medoides = asignarMedoidesIniciales(tab, ref_calibracion);
    
    if(debug)
        cout << "Clasificador K-Medoids, entrada: " << endl << mostrarColores(tab) << endl;
    
    // Iteración principal, hasta que se obtenga la mejor distribución de grupos
    do {        
        costo_ant = costo_act;
        grupos = asignarGrupos(tab, medoides);
        costo_act = evaluarCosto(tab, medoides, grupos);
        medoides = recalcularMedoides(tab, grupos);        
    } while(costo_act < costo_ant);
    
    // Una vez clasificados los grupos, re-etiquetarlos como:
    //  0 = casilla vacia
    //  1 = pieza blanca
    // -1 = pieza negra
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            if(grupos.at(fila).at(columna) == 0 || grupos.at(fila).at(columna) == 1) {
                grupos.at(fila).at(columna) = 0;
            } else if(grupos.at(fila).at(columna) == 2) {
                grupos.at(fila).at(columna) = 1;
            } else {
                grupos.at(fila).at(columna) = -1;
            }
        }
    }
    
    // Rotar la matriz, debido a la diferencia entre las coordenadas tablero y las coordenadas imagen
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            salida.at(columna).at(fila) = grupos.at(fila).at(columna);
        }
    }
    
    if(debug) {
        cout << "Fin de la clasificación de K-Medoids. Tablero detectado:" << endl;
        mostrarClasificacion(salida);
    }
    
    return salida;
    
}

struct referencias ClasificadorKMedoids::asignarMedoidesIniciales(resultadoMuestreo tab, struct referencias r) {
    
    struct referencias medoides;
    float dis_cc = 1e6, dis_co = 1e6, dis_pb = 1e6, dis_pn = 1e6;
    
    // Busco el elemento mas cercano a los puntos de referencia
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.cc) < dis_cc) {
                dis_cc = distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.cc);
                medoides.cc = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.co) < dis_co) {
                dis_co = distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.co);
                medoides.co = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.pb) < dis_pb) {
                dis_pb = distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.pb);
                medoides.pb = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.pn) < dis_pn) {
                dis_pn = distanciaEuclidiana(tab.at(fila).at(columna).at(0), r.pn);
                medoides.pn = tab.at(fila).at(columna).at(0);
            }
        }
    }
    
    return medoides;
    
}

// Asigna los grupos de acuerdo a la menor distancia a los medoides
// Grupo 0, Casilla Clara
// Grupo 1, Casilla Oscura
// Grupo 2, Pieza Blanca
// Grupo 3, Pieza Negra
estadoTableroInt ClasificadorKMedoids::asignarGrupos(resultadoMuestreo tab, struct referencias med) {
    
    estadoTableroInt grupos;
        
    float dis_cc, dis_co, dis_pb, dis_pn;
    
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            
            dis_cc = distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.cc);
            dis_co = distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.co);
            dis_pb = distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.pb);
            dis_pn = distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.pn);
            
            grupos.at(fila).at(columna) = minimo(dis_cc, dis_co, dis_pb, dis_pn);
            
        }
    }
    
    return grupos;
    
}

float ClasificadorKMedoids::evaluarCosto(resultadoMuestreo tab, struct referencias med, estadoTableroInt grupos) {
    
    float sumdist = 0;
    
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            
            if(grupos.at(fila).at(columna) == 0) {
                sumdist += distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.cc);
            } else if(grupos.at(fila).at(columna) == 1) {
                sumdist += distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.co);
            } else if(grupos.at(fila).at(columna) == 2) {
                sumdist += distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.pb); 
            } else {
                sumdist += distanciaEuclidiana(tab.at(fila).at(columna).at(0), med.pn);
            }
            
        }
    }
    
    return sumdist;
    
}

struct referencias ClasificadorKMedoids::recalcularMedoides(resultadoMuestreo tab, estadoTableroInt grupos) {
    
    struct referencias medoides, nuevos_medoides;
    medoides.cc = {0,0,0};
    medoides.co = {0,0,0};
    medoides.pb = {0,0,0};
    medoides.pn = {0,0,0};
    int n_cc = 0, n_co = 0, n_pb = 0, n_pn = 0;
    float dis_cc = 1e6, dis_co = 1e6, dis_pb = 1e6, dis_pn = 1e6;
    
    // Calcular el nuevo centroide
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            if(grupos.at(fila).at(columna) == 0) {
                medoides.cc.a += tab.at(fila).at(columna).at(0).a;
                medoides.cc.b += tab.at(fila).at(columna).at(0).b;
                medoides.cc.c += tab.at(fila).at(columna).at(0).c;
                n_cc++;
            } else if(grupos.at(fila).at(columna) == 1) {
                medoides.co.a += tab.at(fila).at(columna).at(0).a;
                medoides.co.b += tab.at(fila).at(columna).at(0).b;
                medoides.co.c += tab.at(fila).at(columna).at(0).c;
                n_co++;
            } else if(grupos.at(fila).at(columna) == 2) {
                medoides.pb.a += tab.at(fila).at(columna).at(0).a;
                medoides.pb.b += tab.at(fila).at(columna).at(0).b;
                medoides.pb.c += tab.at(fila).at(columna).at(0).c;
                n_pb++;
            } else if(grupos.at(fila).at(columna) == 3) {
                medoides.pn.a += tab.at(fila).at(columna).at(0).a;
                medoides.pn.b += tab.at(fila).at(columna).at(0).b;
                medoides.pn.c += tab.at(fila).at(columna).at(0).c;
                n_pn++;
            }
        }
    }
    
    // Promedio de todos los elementos del grupo
    if(n_cc) {
        medoides.cc.a /= n_cc;
        medoides.cc.b /= n_cc;
        medoides.cc.c /= n_cc;
    }
    if(n_co) {
        medoides.co.a /= n_co;
        medoides.co.b /= n_co;
        medoides.co.c /= n_co;
    }
    if(n_pb) {
        medoides.pb.a /= n_pb;
        medoides.pb.b /= n_pb;
        medoides.pb.c /= n_pb;
    }
    if(n_pn) {
        medoides.pn.a /= n_pn;
        medoides.pn.b /= n_pn;
        medoides.pn.c /= n_pn;
    }
    
    // Busco el punto más cercano a cada centroide, y ese es el nuevo medoide
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.cc) < dis_cc) {
                dis_cc = distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.cc);
                nuevos_medoides.cc = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.co) < dis_co) {
                dis_co = distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.co);
                nuevos_medoides.co = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.pb) < dis_pb) {
                dis_pb = distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.pb);
                nuevos_medoides.pb = tab.at(fila).at(columna).at(0);
            }
            if(distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.pn) < dis_pn) {
                dis_pn = distanciaEuclidiana(tab.at(fila).at(columna).at(0), medoides.pn);
                nuevos_medoides.pn = tab.at(fila).at(columna).at(0);
            }
        }
    }
    
    return nuevos_medoides;
    
}
