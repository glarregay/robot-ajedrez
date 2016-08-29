#include "MovimientoIlegalException.h"

MovimientoIlegalException::MovimientoIlegalException() {
}

MovimientoIlegalException::MovimientoIlegalException(const MovimientoIlegalException& orig) {
}

MovimientoIlegalException::~MovimientoIlegalException() {
}

const char* MovimientoIlegalException::what() const throw () {
    return "Movimiento ilegal.";
}
