#ifndef CLASIFICADORJ48_H
#define CLASIFICADORJ48_H

#include "Clasificador.h"

class ClasificadorJ48 : public Clasificador {
public:
    ClasificadorJ48();
    ClasificadorJ48(const ClasificadorJ48& orig);
    virtual ~ClasificadorJ48();
    
    void calibrar(resultadoMuestreo tab);
    estadoTableroInt clasificar(resultadoMuestreo tab);
    
private:

};

#endif /* CLASIFICADORJ48_H */

