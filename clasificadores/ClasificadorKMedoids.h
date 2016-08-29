#ifndef CLASIFICADORKMEDOIDS_H
#define CLASIFICADORKMEDOIDS_H

#include "Clasificador.h"

using namespace std;

class ClasificadorKMedoids : public Clasificador {
public:
    ClasificadorKMedoids();
    ClasificadorKMedoids(const ClasificadorKMedoids& orig);
    ~ClasificadorKMedoids();
    
    void calibrar(resultadoMuestreo tab);
    estadoTableroInt clasificar(resultadoMuestreo tab);
    
private:
    
    struct referencias asignarMedoidesIniciales(resultadoMuestreo tab, struct referencias r);
    estadoTableroInt asignarGrupos(resultadoMuestreo tab, struct referencias med);
    float evaluarCosto(resultadoMuestreo tab, struct referencias med, estadoTableroInt grupos);
    struct referencias recalcularMedoides(resultadoMuestreo tab, estadoTableroInt grupos);
    
};

#endif /* CLASIFICADORKMEDOIDS_H */

