#ifndef C_CONFIGURACION_H
#define	C_CONFIGURACION_H

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

class Configuracion {
public:
    static void leerConfiguracion(void);
    
    static double getParametro(string nombre);
    static double getParametroIgnorarError(string nombre);
    static void setParametro(string param, double valor);

private:
    
    static Configuracion* instancia; /**< Referencia a la unica instancia de c_Configuracion. */
        
    map<string, double> configuracion; /**< Mapa que contiene los parametros de configuracion del sistema. */
  
    Configuracion();
    ~Configuracion();
    static Configuracion* getInstancia();
    
    static void limpiar(void);
    
};

#endif	/* C_CONFIGURACION_H */

