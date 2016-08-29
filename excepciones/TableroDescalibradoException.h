#ifndef TABLERODESCALIBRADOEXCEPTION_H
#define TABLERODESCALIBRADOEXCEPTION_H

class TableroDescalibradoException {
public:
    TableroDescalibradoException();
    TableroDescalibradoException(const TableroDescalibradoException& orig);
    virtual ~TableroDescalibradoException();
    virtual const char* what() const throw();
private:

};

#endif /* TABLERODESCALIBRADOEXCEPTION_H */

