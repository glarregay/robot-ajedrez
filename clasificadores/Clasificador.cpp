#include "Clasificador.h"

Clasificador::Clasificador() {
    debug = Configuracion::getParametro("DEBUG");
}

Clasificador::Clasificador(const Clasificador& orig) {
}

Clasificador::~Clasificador() {
}

/*string Clasificador::mostrarReferencias() {
    
    stringstream out;
    
    for(int i = 0; i < 16; i++) {
        out << calibracion[i].pb.a << "," << calibracion[i].pb.b << "," << calibracion[i].pb.c << ",'blanca'" << endl;
    }
    
    for(int i = 0; i < 16; i++) {
        out << calibracion[i].pn.a << "," << calibracion[i].pn.b << "," << calibracion[i].pn.c << ",'negra'" << endl;
    }
    
    for(int i = 0; i < 16; i++) {
        out << calibracion[i].cc.a << "," << calibracion[i].cc.b << "," << calibracion[i].cc.c << ",'vacia'" << endl;
    }
    
    for(int i = 0; i < 16; i++) {
        out << calibracion[i].co.a << "," << calibracion[i].co.b << "," << calibracion[i].co.c << ",'vacia'" << endl;
    }
    
    return out.str();
    
}*/

string Clasificador::mostrarReferencias() {
    
    stringstream out;
    
    out << "pb= [" << endl;
    for(int i = 0; i < 16; i++) {
        out << "[ " << calibracion[i].pb.a << " " << calibracion[i].pb.b << " " << calibracion[i].pb.c << " ]" << endl;
    }
    out << "];" << endl;
    
    out << "pn= [" << endl;
    for(int i = 0; i < 16; i++) {
        out << "[ " << calibracion[i].pn.a << " " << calibracion[i].pn.b << " " << calibracion[i].pn.c << " ]" << endl;
    }
    out << "];" << endl;
    
    out << "cc= [" << endl;
    for(int i = 0; i < 16; i++) {
        out << "[ " << calibracion[i].cc.a << " " << calibracion[i].cc.b << " " << calibracion[i].cc.c << " ]" << endl;
    }
    out << "];" << endl;
    
    out << "co= [" << endl;
    for(int i = 0; i < 16; i++) {
        out << "[ " << calibracion[i].co.a << " " << calibracion[i].co.b << " " << calibracion[i].co.c << " ]" << endl;
    }
    out << "];" << endl;
    
    return out.str();
    
}

string Clasificador::mostrarColores(resultadoMuestreo r) {
    
    stringstream out;
    
    out << "t= [" << endl;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            out << "[ " << r.at(i).at(j).at(0).a << " " << r.at(i).at(j).at(0).b << " " << r.at(i).at(j).at(0).c << " ]" << endl;
        }
    }
    out << "];" << endl;
    
    return out.str();
    
}

void Clasificador::mostrarClasificacion(estadoTableroInt in) {
    
    for(int fila = 0; fila < 8; fila++) {
        for(int columna = 0; columna < 8; columna++) {
            cout << in.at(fila).at(columna) +1;
        }
        cout << endl;
    }
    
}

string Clasificador::mostrarArff(resultadoMuestreo r, estadoTableroInt in) {
    
    stringstream out;
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            string clase;
            
            if(in.at(j).at(i) == 0)
                clase = "'vacia'";
            if(in.at(j).at(i) == 1)
                clase = "'blanca'";
            if(in.at(j).at(i) == -1)
                clase = "'negra'";
            
            out << r.at(i).at(j).at(0).a << "," << r.at(i).at(j).at(0).b << "," << r.at(i).at(j).at(0).c << "," << clase << endl;
        }
    }
    
    return out.str();
    
}

// Calcula la distancia entre dos colores
float Clasificador::distanciaEuclidiana(struct color v1, struct color v2) {
    
    float sumacuadrados = pow(v1.a-v2.a, 2) + pow(v1.b-v2.b, 2) + pow(v1.c-v2.c, 2);
    float d = sqrt(sumacuadrados);
    
    return d;
    
}

// Devuelve el número de argumento que es el menor
// NO DEVUELVE EL MENOR VALOR.
// Ejemplo: minimo(3, 4, 1, 5) devuelve 2 (0 es el primer argumento)
int Clasificador::minimo(float a, float b, float c, float d) {
    
    if(a<=b && a<=c && a<=d)
        return 0;
    if(b<=a && b<=c && b<=d)
        return 1;
    if(c<=b && c<=a && c<=d)
        return 2;
    if(d<=b && d<=c && d<=a)
        return 3;
    
    return -1;
    
}
