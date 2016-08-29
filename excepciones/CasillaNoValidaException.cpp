#include "CasillaNoValidaException.h"

CasillaNoValidaException::CasillaNoValidaException() {
}

CasillaNoValidaException::CasillaNoValidaException(const CasillaNoValidaException& orig) {
}

CasillaNoValidaException::~CasillaNoValidaException() {
}

const char* CasillaNoValidaException::what() const throw () {
    return "Casilla no valida.";
}
