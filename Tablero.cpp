#include "Tablero.h"

Tablero::Tablero() {
    
    debug = Configuracion::getParametro("DEBUG");
    
    est.at(0) = {'T','P','-','-','-','-','p','t'};
    est.at(1) = {'C','P','-','-','-','-','p','c'};
    est.at(2) = {'A','P','-','-','-','-','p','a'};
    est.at(3) = {'D','P','-','-','-','-','p','d'};
    est.at(4) = {'R','P','-','-','-','-','p','r'};
    est.at(5) = {'A','P','-','-','-','-','p','a'};
    est.at(6) = {'C','P','-','-','-','-','p','c'};
    est.at(7) = {'T','P','-','-','-','-','p','t'};
    
}

Tablero::Tablero(const Tablero& orig) {
}

Tablero::~Tablero() {
}

void Tablero::nuevaPartida() {
    
    est.at(0) = {'T','P','-','-','-','-','p','t'};
    est.at(1) = {'C','P','-','-','-','-','p','c'};
    est.at(2) = {'A','P','-','-','-','-','p','a'};
    est.at(3) = {'D','P','-','-','-','-','p','d'};
    est.at(4) = {'R','P','-','-','-','-','p','r'};
    est.at(5) = {'A','P','-','-','-','-','p','a'};
    est.at(6) = {'C','P','-','-','-','-','p','c'};
    est.at(7) = {'T','P','-','-','-','-','p','t'};
    
}

bool Tablero::casillaValida(string casilla) {
    
    if (casilla.length() != 2)
        throw CasillaNoValidaException();

    if (toupper(casilla.at(0) < 'A') || toupper(casilla.at(0)) > 'H')
        throw CasillaNoValidaException();

    if (casilla.at(1) < '1' || casilla.at(1) > '8')
        throw CasillaNoValidaException();
    
    return true;

}

bool Tablero::casillaVacia(string casilla) {

    return (est.at(columna(casilla)).at(fila(casilla)) == '-');

}

char Tablero::piezaEnCasilla(string casilla) {

    return est.at(columna(casilla)).at(fila(casilla));

}

piece Tablero::piezaEnCasillaCM(string casilla) {

    char pz = tolower(est.at(columna(casilla)).at(fila(casilla)));
    
    switch(pz) {
        case 'c':
            return piece::Knight;
        case 'p':
            return piece::Pawn;
        case 't':
            return piece::Rook;
        case 'a':
            return piece::Bishop;
        case 'r':
            return piece::King;
        case 'd':
            return piece::Queen;
        default:
            return piece::None;
    }
    
}

int Tablero::columna(string casilla) {

    //es valida la casilla?
    casillaValida(casilla);

    return toupper(casilla.at(0))-'A';

}

int Tablero::fila(string casilla) {

    //es valida la casilla?
    casillaValida(casilla);

    return casilla.at(1) - '1';

}

ChessMove Tablero::analizarRespuestaGNUChess(string mensaje) {

    size_t pRes;
    string movimiento;
    string reporte;
    string mate = "None";
    
    ChessMove cm;
    cm.move_type = MovementType::None;
    cm.mate_type = MateType::None;
    
    if(debug) {
        cout << "analizarRespuesta:" << endl;
        cout << "   argin: " << mensaje << endl;
    }

    pRes = mensaje.find("mates",0);
    if (pRes != std::string::npos) {
        mate = mensaje.substr(pRes-6,5);
    }
    
    pRes = mensaje.find(":",0);

    if (pRes != string::npos) { // Existe el caracter ":"

        if (mensaje.find("Illegal move",0) != string::npos) {
            throw MovimientoIlegalException();
        } else if (mensaje.find("Invalid move",0) != string::npos) {
            movimiento = mensaje.substr(pRes+2);
            
            cout << "Movimiento inválido, intentando corregir..." << endl;
            
            string origen = movimiento.substr(0,2);
            string destino = movimiento.substr(2,2);
            cm = reporteMovimientoCorregirCM(destino, origen, mate);
            
            if(tipoMovimiento(destino,origen).compare("Normal") != 0) {
                cout << "Estado de tablero inconsistente" << endl;
                cout << "Se debe reponer una pieza negra (" << piezaEnCasilla(destino) << ") en " << destino << endl;
            }
                        
            cout << "Movimiento deshecho" << endl;
            
        } else if (mensaje.find("My move is",0) != string::npos) {
            
            movimiento = mensaje.substr(pRes+2);
            
            for (unsigned int i = 0; i < movimiento.length(); i++)
                if (!isalnum(movimiento.at(i))) movimiento.at(i) = 0;
            
            cm = reporteMovimientoCM(movimiento.substr(0,2), movimiento.substr(2,2), mate);
            mover(movimiento);
            
/*            display->borrarLCD();
            display->escribirLCDlinea1("R: ");
            display->escribirLCD(movimiento);*/
                        
        }
        
        if(debug) {
            cout << "analizarRespuesta:" << endl;
            cout << "   argout: " << reporte << endl;
        }
        
        return cm;

    } else {
        if(debug) {
            cout << "analizarRespuesta:" << endl;
            cout << "   argout: " << "" << endl;
        }
        
        if(mate.compare("White") == 0) {
            cm = reporteMovimientoCM(movimiento.substr(0,2), movimiento.substr(2,2), mate);            
        } else {
            cm.move_type = MovementType::None;
        }
       
        return cm;
    }
}

string Tablero::mover(string movimiento) {

    string origen, destino, reporte;
    int co = 0, fo = 0, cd = 0, fd = 0;
    
    if(debug) {
        cout << "mover:" << endl;
        cout << "   argin: " << movimiento << endl;
    }
    
    try {
        
        if (movimiento.length() < 4 || movimiento.length() > 5)
            throw MovimientoIlegalException();

        origen = movimiento.substr(0, 2);
        destino = movimiento.substr(2, 2);

        co = columna(origen);
        fo = fila(origen);
        cd = columna(destino);
        fd = fila(destino);
        
        reporte = reporteMovimiento(origen, destino, "None");

        // VER CASOS ESPECIALES (enroque, promocion)

        // Enroque Corto
        if((tipoMovimiento(origen, destino).compare("ShortCastling") == 0) ||
           (tipoMovimiento(origen, destino).compare("LongCastling") == 0)) {
            if(origen.compare("e1") == 0) {
                if(destino.compare("g1") == 0) {
                    cout << "Enroque blanco corto: " << origen << destino << endl;
                    est.at(columna("e1")).at(fila("e1")) = '-';
                    est.at(columna("f1")).at(fila("f1")) = 'T';
                    est.at(columna("g1")).at(fila("g1")) = 'R';
                    est.at(columna("h1")).at(fila("h1")) = '-';
                } else {
                    cout << "Enroque blanco largo: " << origen << destino << endl;
                    est.at(columna("c1")).at(fila("c1")) = 'R';
                    est.at(columna("e1")).at(fila("e1")) = '-';
                    est.at(columna("d1")).at(fila("d1")) = 'T';
                    est.at(columna("a1")).at(fila("a1")) = '-';
                }
            } else {
                if(destino.compare("g8") == 0) {
                    cout << "Enroque negro corto: " << origen << destino << endl;
                    est.at(columna("g8")).at(fila("g8")) = 'r';
                    est.at(columna("e8")).at(fila("e8")) = '-';
                    est.at(columna("f8")).at(fila("f8")) = 't';
                    est.at(columna("h8")).at(fila("h8")) = '-';
                } else {
                    cout << "Enroque negro largo: " << origen << destino << endl;
                    est.at(columna("c8")).at(fila("c8")) = 'r';
                    est.at(columna("e8")).at(fila("e8")) = '-';
                    est.at(columna("d8")).at(fila("d8")) = 't';
                    est.at(columna("a8")).at(fila("a8")) = '-';
                }
            }
        }
        
        // Al paso
        else if(tipoMovimiento(origen, destino).compare("Passant") == 0) {
            est.at(cd).at(fo) = '-';    // saca el peon opuesto
            est.at(cd).at(fd) = est.at(co).at(fo);
            est.at(co).at(fo) = '-';
        }
        
        // Normal
        else {
            est.at(cd).at(fd) = est.at(co).at(fo);
            est.at(co).at(fo) = '-';
        }
        
        if(debug) {
            cout << "Despues del movimiento en GNUChess" << endl;
            mostrarTablero();
        }
        
        return reporte;

    } catch (CasillaNoValidaException const& e) {
        printf("%s\n", e.what());
        return "";
    } catch (MovimientoIlegalException const& e) {
        printf("%s\n", e.what());
        return "";
    }


}

int Tablero::calibrarCoordenadasExtremos(coordenadasFisicas a1, coordenadasFisicas a8, coordenadasFisicas h1) {
    
    this->a1 = a1;
    this->vx = make_pair<double, double>((h1.first - a1.first) / 7.0, (h1.second - a1.second) / 7.0);
    this->vy = make_pair<double, double>((a8.first - a1.first) / 7.0, (a8.second - a1.second) / 7.0);
    this->calibrado = true;
    
    return 0;
    
}

coordenadasFisicas Tablero::obtenerCoordenadas(int f, int c) {
    
    coordenadasFisicas casilla;
    
    if(calibrado == false)
        throw TableroDescalibradoException();
    
    casilla.first  = this->a1.first  + f*this->vy.first  + c*this->vx.first;
    casilla.second = this->a1.second + f*this->vy.second + c*this->vx.second;
    
    return casilla;
    
}

string Tablero::reporteMovimiento(string origen, string destino, string mate) {
    
    /*     
    <?xml version="1.0"?><ChessMove><Pieces><Play>
    Pawn,Rook,Knight,King,Queen,Bishop
    </Play><Die>
    Pawn,Rook,Knight,King,Queen,Bishop
    </Die></Pieces><Movement>
    Normal,Attack,LongCastling,ShortCastling
    </Movement><Coords><Origin><X>
    30.10
    </X><Y>
    31.11
    </Y></Origin><Destiny><X>
    40.10
    </X><Y>
    41.11
    </Y></Destiny></Coords></ChessMove>
     */
    
    stringstream out;
    
    string tipomov = tipoMovimiento(origen, destino);
           
    coordenadasFisicas orig = obtenerCoordenadas(fila(origen) , columna(origen));
    coordenadasFisicas dest = obtenerCoordenadas(fila(destino), columna(destino));
    
    if(mate.compare("White") == 0) {
/*        display->borrarLCD();
        display->escribirLCDlinea1("Fin del juego.");
        display->escribirLCDlinea2("Ganan blancas.");*/
    }
    if(mate.compare("Black") == 0) {
/*        display->borrarLCD();
        display->escribirLCDlinea1("Fin del juego.");
        display->escribirLCDlinea2("Ganan negras.");*/
    }
    
    out << "<?xml version=\"1.0\"?><ChessMove><Pieces><Play>" 
        << nombrePieza(piezaEnCasilla(origen))
        << "</Play><Die>"
        << nombrePieza(piezaEnCasilla(destino))
        << "</Die></Pieces><Movement>"
        << tipomov
        << "</Movement><Coords><Origin><X>"
        << orig.first
        << "</X><Y>"
        << orig.second
        << "</Y></Origin><Destiny><X>"
        << dest.first
        << "</X><Y>"
        << dest.second
        << "</Y></Destiny></Coords><ChessNotation>"
        << origen << destino
        << "</ChessNotation><Mate>"
        << mate
        << "</Mate></ChessMove>"
        << std::endl;
    
    return out.str(); 
    
}

ChessMove Tablero::reporteMovimientoCM(string origen, string destino, string mate) {
    
    ChessMove cm;
           
    coordenadasFisicas orig = obtenerCoordenadas(fila(origen) , columna(origen));
    coordenadasFisicas dest = obtenerCoordenadas(fila(destino), columna(destino));
    
    cm.move_type = tipoMovimientoCM(origen, destino);
    cm.piece_origin.setPiece(piezaEnCasillaCM(origen));
    cm.piece_origin.setCoord(orig.first, orig.second);
    cm.piece_destiny.setPiece(piezaEnCasillaCM(destino));
    cm.piece_destiny.setCoord(dest.first, dest.second);
    cm.mate_type = MateType::None;
    
    if(mate.compare("White") == 0) {
        cm.mate_type = MateType::White;
/*        display->borrarLCD();
        display->escribirLCDlinea1("Fin del juego.");
        display->escribirLCDlinea2("Ganan blancas.");*/
    }
    if(mate.compare("Black") == 0) {
        cm.mate_type = MateType::Black;
/*        display->borrarLCD();
        display->escribirLCDlinea1("Fin del juego.");
        display->escribirLCDlinea2("Ganan negras.");*/
    }

    return cm; 
    
}


string Tablero::reporteMovimientoCorregir(string origen, string destino, string mate) {
    
    /*     
    <?xml version="1.0"?><ChessMove><Pieces><Play>
    Pawn,Rook,Knight,King,Queen,Bishop
    </Play><Die>
    Pawn,Rook,Knight,King,Queen,Bishop
    </Die></Pieces><Movement>
    Normal,Attack,LongCastling,ShortCastling
    </Movement><Coords><Origin><X>
    30.10
    </X><Y>
    31.11
    </Y></Origin><Destiny><X>
    40.10
    </X><Y>
    41.11
    </Y></Destiny></Coords></ChessMove>
     */
    
    stringstream out;
    
    string tipomov = "Normal";
           
    coordenadasFisicas orig = obtenerCoordenadas(fila(origen) , columna(origen));
    coordenadasFisicas dest = obtenerCoordenadas(fila(destino), columna(destino));
    
    out << "<?xml version=\"1.0\"?><ChessMove><Pieces><Play>" 
        << nombrePieza(piezaEnCasilla(origen))
        << "</Play><Die>"
        << nombrePieza(piezaEnCasilla(destino))
        << "</Die></Pieces><Movement>"
        << tipomov
        << "</Movement><Coords><Origin><X>"
        << orig.first
        << "</X><Y>"
        << orig.second
        << "</Y></Origin><Destiny><X>"
        << dest.first
        << "</X><Y>"
        << dest.second
        << "</Y></Destiny></Coords><ChessNotation>"
        << origen << destino
        << "</ChessNotation><Mate>"
        << mate
        << "</Mate></ChessMove>"
        << std::endl;
    
    return out.str(); 
    
}

ChessMove Tablero::reporteMovimientoCorregirCM(string origen, string destino, string mate) {

    ChessMove cm;
           
    coordenadasFisicas orig = obtenerCoordenadas(fila(origen) , columna(origen));
    coordenadasFisicas dest = obtenerCoordenadas(fila(destino), columna(destino));
    
    cm.move_type = MovementType::Normal;
    cm.piece_origin.setPiece(piezaEnCasillaCM(origen));
    cm.piece_origin.setCoord(orig.first, orig.second);
    cm.piece_destiny.setPiece(piezaEnCasillaCM(destino));
    cm.piece_destiny.setCoord(dest.first, dest.second);
    cm.mate_type = MateType::None;

    return cm; 
    
}

string Tablero::nombrePieza(char p) {
    
    char pz = tolower(p);
    
    switch(pz) {
        case 'c':
            return "Knight";
        case 'p':
            return "Pawn";
        case 't':
            return "Rook";
        case 'a':
            return "Bishop";
        case 'r':
            return "King";
        case 'd':
            return "Queen";
        default:
            return "-";
    }
    
}

string Tablero::tipoMovimiento(string origen, string destino) {
    
    string tipo; 
       
    if(debug) {
        cout << "tipoMovimiento:" << endl;
        cout << "   argin: " << origen << endl;
        cout << "   argin: " << destino << endl;
    }
    // Enroque Corto
    if((origen.compare("e1")==0 && destino.compare("g1")==0) ||
       (origen.compare("e8")==0 && destino.compare("g8")==0)) {
        if((piezaEnCasilla(origen) == 'R') || (piezaEnCasilla(origen) == 'r')) {
            tipo = "ShortCastling";
        } else {
            tipo = "Normal";
        }
    }
    
    // Enroque Largo
    else if((origen.compare("e1")==0 && destino.compare("c1")==0) ||
       (origen.compare("e8")==0 && destino.compare("c8")==0)) {
        if((piezaEnCasilla(origen) == 'R') || (piezaEnCasilla(origen) == 'r')) {
            tipo = "LongCastling";
        } else {
            tipo = "Normal";
        }
    }
    
    // Peon al paso
    /*else if((tolower(piezaEnCasilla(origen)) == 'p') &&
            (fila(origen) == 5 || fila(origen) == 4) &&
            piezaEnCasilla(destino) == '-' &&
            abs(columna(origen) - columna(destino)) == 1) {
        tipo = "Passant";
    }*/
    
    // Ataque  
    else if(piezaEnCasilla(destino) != '-') {
        tipo = "Attack";
    } 
    
    // Normal
    else {
        tipo = "Normal";
    }
    
    //cout << "Movimiento: " << origen << destino << " " << tipo << endl;
      
    if(debug) {
        cout << "tipoMovimiento:" << endl;
        cout << "   argout: " << tipo << endl;
    }
    return tipo;
    
}

MovementType Tablero::tipoMovimientoCM(string origen, string destino) {
    
    MovementType tipo; 
       
    if(debug) {
        cout << "tipoMovimiento:" << endl;
        cout << "   argin: " << origen << endl;
        cout << "   argin: " << destino << endl;
    }
    // Enroque Corto
    if((origen.compare("e1")==0 && destino.compare("g1")==0) ||
       (origen.compare("e8")==0 && destino.compare("g8")==0)) {
        if((piezaEnCasilla(origen) == 'R') || (piezaEnCasilla(origen) == 'r')) {
            tipo = MovementType::ShortCastling;
        } else {
            tipo = MovementType::Normal;
        }
    }
    
    // Enroque Largo
    else if((origen.compare("e1")==0 && destino.compare("c1")==0) ||
       (origen.compare("e8")==0 && destino.compare("c8")==0)) {
        if((piezaEnCasilla(origen) == 'R') || (piezaEnCasilla(origen) == 'r')) {
            tipo = MovementType::LongCastling;
        } else {
            tipo = MovementType::Normal;
        }
    }
    
    // Peon al paso
    /*else if((tolower(piezaEnCasilla(origen)) == 'p') &&
            (fila(origen) == 5 || fila(origen) == 4) &&
            piezaEnCasilla(destino) == '-' &&
            abs(columna(origen) - columna(destino)) == 1) {
        tipo = "Passant";
    }*/
    
    // Ataque  
    else if(piezaEnCasilla(destino) != '-') {
        tipo = MovementType::Attack;
    } 
    
    // Normal
    else {
        tipo = MovementType::Normal;
    }
    
    return tipo;
    
}

estadoTableroChar Tablero::estadoActual() {
    
    return est;
    
}

void Tablero::mostrarTablero() {
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << est.at(i).at(j);
        }
        cout << endl;
    }
    
}
