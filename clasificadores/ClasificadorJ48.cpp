#include "ClasificadorJ48.h"

ClasificadorJ48::ClasificadorJ48() {
}

ClasificadorJ48::ClasificadorJ48(const ClasificadorJ48& orig) {
}

ClasificadorJ48::~ClasificadorJ48() {
}

void ClasificadorJ48::calibrar(resultadoMuestreo tab) {
    
    if(debug) {
        cout << "J48 no requiere calibración, está hardcoded." << endl;
    }
    
}

estadoTableroInt ClasificadorJ48::clasificar(resultadoMuestreo tab) {
    
    /* Según WEKA:
     
    L <= 76: negra (166.0)
    L > 76
    |   S <= 86: vacia (368.0)
    |   S > 86: blanca (170.0)*/
    
    estadoTableroInt salida;
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int L = tab.at(i).at(j).at(0).b;
            int S = tab.at(i).at(j).at(0).c;
            
            if(L <= 76) {
                salida.at(j).at(i) = -1;
            } else {
                if(S <= 86)
                    salida.at(j).at(i) = 0;
                else
                    salida.at(j).at(i) = 1;
            }            
        }
    }
    
    if(debug) {
        cout << "Fin de la clasificación de J48. Tablero detectado:" << endl;
        mostrarClasificacion(salida);
    }
    
    return salida;
    
}
    
    
