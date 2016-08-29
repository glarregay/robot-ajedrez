#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <array>
#include <vector>
#include <utility>

using namespace std;

struct coord {
    int x;
    int y;
};

struct color {
    int a;
    int b;
    int c;
};

struct colorf {
    float a;
    float b;
    float c;
};

struct muestreo {
    struct coord coord[7];
    struct color color[7];
};

struct referencias {
    struct color pb;
    struct color pn;
    struct color cc;
    struct color co;
};

struct casilla {
    int fila;
    int columna;
};

typedef array<array<int, 8>, 8>                  estadoTableroInt;
typedef array<array<char, 8>, 8>                 estadoTableroChar;
typedef pair<double, double>                     coordenadasFisicas;
typedef array<array<vector<struct color>, 8>, 8> resultadoMuestreo;

#endif /* ESTRUCTURAS_H */

