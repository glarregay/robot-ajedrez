#ifndef CASILLANOVALIDAEXCEPTION_H
#define	CASILLANOVALIDAEXCEPTION_H

#include <stdexcept>

class CasillaNoValidaException {
public:
    CasillaNoValidaException();
    CasillaNoValidaException(const CasillaNoValidaException& orig);
    virtual ~CasillaNoValidaException();
    virtual const char* what() const throw();
private:

};

#endif	/* CASILLANOVALIDAEXCEPTION_H */

