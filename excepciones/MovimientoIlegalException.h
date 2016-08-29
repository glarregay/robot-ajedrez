#ifndef MOVIMIENTOILEGALEXCEPTION_H
#define	MOVIMIENTOILEGALEXCEPTION_H

class MovimientoIlegalException {
public:
    MovimientoIlegalException();
    MovimientoIlegalException(const MovimientoIlegalException& orig);
    virtual ~MovimientoIlegalException();
    virtual const char* what() const throw();
private:

};

#endif	/* MOVIMIENTOILEGALEXCEPTION_H */

