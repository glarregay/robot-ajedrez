#ifndef CLASIFICADORVOTACION_H
#define CLASIFICADORVOTACION_H

#include "Clasificador.h"

class ClasificadorVotacion : public Clasificador {
public:
    ClasificadorVotacion();
    ClasificadorVotacion(const ClasificadorVotacion& orig);
    virtual ~ClasificadorVotacion();
    
    void calibrar(resultadoMuestreo tab);
    estadoTableroInt clasificar(resultadoMuestreo tab);
    
private:
    
    // Configuraciones particulares
    int minimosVotos;
    
    struct color colorCasilla(resultadoMuestreo tab, int fila, int columna);
    int votarCasilla(resultadoMuestreo tab, int fila, int columna);

};

#endif /* CLASIFICADORVOTACION_H */

