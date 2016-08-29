#include "TableroDescalibradoException.h"

TableroDescalibradoException::TableroDescalibradoException() {
}

TableroDescalibradoException::TableroDescalibradoException(const TableroDescalibradoException& orig) {
}

TableroDescalibradoException::~TableroDescalibradoException() {
}

const char* TableroDescalibradoException::what() const throw () {
    return "Tablero no calibrado.";
}
