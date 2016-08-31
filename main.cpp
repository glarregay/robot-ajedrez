#define _XOPEN_SOURCE 600
#define __USE_BSD

#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cctype>
#include <cstring>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include "Tablero.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "ABBchess/ABBchess.h"
#include "DisplayLCD.h"

#define MAXCMD 500

using namespace std;

Tablero* tab;
DetectorPiezas* visor;
ABBchess abb_chess("10.123.0.118",8001);

int fdm, fds;
int rc;
char input[MAXCMD];
int debug = 1;

int mostrarError(int numero, string mensaje) {

    fprintf(stderr, "Error %d en %s\n", numero, mensaje.c_str());
    exit(1);

}

double s2f(string str) {
    istringstream buffer(str);
    double temp;
    buffer >> temp;
    return temp;
}

vector<string> split(const string cadena, const string lim) {
    
    vector<string> tokens;
    size_t  start = 0, end = 0;
    
    while ( end != string::npos) {
        end = cadena.find(lim, start);

        // If at end, use length=maxLength.  Else use length=end-start.
        tokens.push_back( cadena.substr( start, (end == string::npos) ? string::npos : end - start));

        // If at end, use start=maxSize.  Else use start=end+delimiter.
        start = ((end>(string::npos - lim.size())) ? string::npos : end + lim.size());
    }
    
    return tokens;
    
}

string trimRight(const string& cadena) {
    size_t endpos = cadena.find_last_not_of(" \n\r\t");
    return (endpos == std::string::npos) ? "" : cadena.substr(0, endpos+1);
}

string interpretarComando(string cmd) {
    
    if(debug)
        cout << "Comando a interpretar: [ " << cmd << "] " << endl;
    
    cmd = trimRight(cmd);
    vector<string> comando = split(cmd, " ");
    stringstream enviar;
    enviar.clear();
    
    // Comando de tiempo maximo de juego
    // Formato: T <int 0-1000>
    if(comando.at(0).compare("T") == 0) {
        if(comando.size() != 2)
            return "";
        
        int tm = atoi(comando.at(1).c_str());
        
        if(tm < 0 || tm > 1000)
            return "";
        
        enviar << "time " << tm << endl;
    }
    
    // Comando de movimiento
    // Formato: M
    else if(comando.at(0).compare("M") == 0) {
        
/*        display->borrarLCD();
        display->escribirLCDlinea1("Ubicando robot");*/
            
        string mov; 
        
        //abb_chess.motionCapture();
        
        mov = visor->detectarCambios(visor->convertirVectorEstado(tab->estadoActual()));
        if(mov.length() > 0) {
            tab->mover(mov);
            enviar << mov << endl;

/*            display->borrarLCD();
            display->escribirLCDlinea1("Mov. detectado: ");
            display->escribirLCDlinea2(mov);*/
        } else {
/*            display->borrarLCD();
            display->escribirLCDlinea1("No hay cambios");
            display->escribirLCDlinea2("Su turno...");*/
        }
    }
    
    // Comando de referenciación del visor
    // Formato: R
    else if(comando.at(0).compare("R") == 0) {
        visor->generarReferencias();
    }
    // Comando de cargar imagenes debug
    // Formato: I
    else if(comando.at(0).compare("I") == 0) {
        if(comando.size() != 2)
            return "";
        
        string arch = comando.at(1);
        string mov = visor->detectarCambios(arch, visor->convertirVectorEstado(tab->estadoActual()));
        if(mov.length() > 0) {
            tab->mover(mov);
            enviar << mov << endl;
        }
    }
    else if(comando.at(0).compare("J") == 0) {
        if(comando.size() != 2)
            return "";
        
        string arch = comando.at(1);
        visor->generarReferencias(arch);
    }
    
    // Comando de calibración
    // Formato: C <a1x>;<a1y> <a8x>;<a8y> <h1x>;<h1y>
    else if(comando.at(0).compare("C") == 0) {
        if(comando.size() != 4)
            return "";
        
        double x, y;
        vector<coordenadasFisicas> casillas;
        casillas.resize(3);
        
        for(int i = 1; i < 4; i++) {
            vector<string> coords = split(comando.at(i), ";");
            
            x = s2f(coords.at(0));
            y = s2f(coords.at(1));
            casillas.at(i-1) = pair<double, double>(x, y);
        }
        
        tab->calibrarCoordenadasExtremos(casillas[0], casillas[1], casillas[2]);
        
    }
    
    // Comando de nueva partida
    // Formato: N
    else if(comando.at(0).compare("N") == 0) {   
        enviar << "new" << endl;
        tab->nuevaPartida();
    }
    
    // Comando de debug
    // Formato: D (R|C|T) fila columna
    else if(comando.at(0).compare("D") == 0) {
        if(comando.size() != 4)
            return "";
        
        // 0, referencia. 1, casilla. 2, tablero
        int tipo;
        
        if(comando.at(1).compare("R") == 0)
            tipo = 0;
        if(comando.at(1).compare("C") == 0)
            tipo = 1;
        if(comando.at(1).compare("T") == 0)
            tipo = 2;
        
//        int fila = atoi(comando.at(2).c_str());
//        int columna = atoi(comando.at(3).c_str());
        
        if (tipo == 0)
            //cout << visor->mostrarReferencias() << endl;
        
        if (tipo == 1)
            //cout << visor->mostrarCasilla(fila, columna);
        
        if (tipo == 2) {
            //cout << "Imagen guardada en muestreo.jpg" << endl;
            //visor->guardarImagenMuestreada();
        }
    }
    
    return enviar.str();
    
}

int main(int ac, char *av[]) {

    int fdm, fds;
    int rc;
    int retvals;
    char input[MAXCMD];
    string respuesta;
    ChessMove respGNU;
    int calibrado = 0;
    int ejecutado = 1;
    
    Configuracion::leerConfiguracion();
        
    DisplayLCD::borrarLCD();
    
    tab = new Tablero();
    visor = new DetectorPiezas();
    
    DisplayLCD::escribirLCD("Conexion ABB: ", 1);
    abb_chess.connectABBchess();
    DisplayLCD::escribirLCD("OK", 2);
    
    int dificultad = Configuracion::getParametro("DIFICULTAD_GNUCHESS");
    
    tab->calibrarCoordenadasExtremos(
            make_pair<double, double>(0,350),
            make_pair<double, double>(0,0),
            make_pair<double, double>(350,350));
    
    fdm = posix_openpt(O_RDWR);
    if (fdm < 0) mostrarError(errno, "posix_openpt()");

    rc = grantpt(fdm);
    if (rc != 0) mostrarError(errno, "grantpt()");

    rc = unlockpt(fdm);
    if (rc != 0) mostrarError(errno, "unlockpt()");

    fds = open(ptsname(fdm), O_RDWR); // Abrir el lado esclavo de la PTY
    
/*    display->borrarLCD();
    display->escribirLCDlinea1("Esperando...");*/
    
    if (fork()) { // Crear el proceso hijo
        fd_set fd_in;
        
        ServerSocket srv(5000);

        // Proceso Padre
        // *************

        close(fds); // Se cierra el lado esclavo de la PTY

        ServerSocket nvo_sock;
        //srv.accept(nvo_sock);
        
        if(debug) {
            cout << "main:" << endl;
            cout << "   Socket creado, conexión recibida." << endl;
        }
        
/*        display->borrarLCD();
        display->escribirLCDlinea1("Conectado.");*/
            
        while (1) {
                        
            // Espera de datos de stdin y del lado maestro de la PTY
            FD_ZERO(&fd_in);
            FD_SET(0, &fd_in);
            FD_SET(fdm, &fd_in);

            struct timespec timeout;
            timeout.tv_sec = 0;
            timeout.tv_nsec = 500000000;
            
            string datos_sock;
            stringstream resp_gnuch;
            
            //nvo_sock >> datos_sock;
            
            if(calibrado == 0) {
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Ubicando robot.", 1);
                DisplayLCD::escribirLCD("Espere...", 2);
                
                this_thread::sleep_for(chrono::milliseconds(5000));
                abb_chess.motionCalibration();
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Pulse el boton", 1);
                DisplayLCD::escribirLCD("para calibrar", 2);
                interpretarComando("R"); 
                
                abb_chess.waitButton();
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Espere...", 1);
                
                this_thread::sleep_for(chrono::milliseconds(5000));
                interpretarComando("R");
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Camara calibrada", 1);
                
                this_thread::sleep_for(chrono::milliseconds(2000));
                
                string msg = "Dific.: " + to_string(dificultad);
                string cmd = "T " + to_string(dificultad);
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Nueva partida.", 1);
                DisplayLCD::escribirLCD(msg, 2);
                
                interpretarComando("N");
                interpretarComando(cmd);
                
                calibrado = 1;
                
            }
            
            if(calibrado == 1 && ejecutado == 1) {
                
                DisplayLCD::borrarLCD();
                DisplayLCD::escribirLCD("Esperando jugada", 1);

                abb_chess.waitButtonNonBlocking();
                
                ejecutado = 0;
                
                string respuesta = interpretarComando("M");
                write(fdm, respuesta.c_str(), respuesta.length());
                
            }
            
            if(ejecutado == 0) {
                ejecutado = abb_chess.buttonPressed();
            }
            
            //rc = pselect(fdm + 1, &fd_in, NULL, NULL, &timeout, NULL);
            //if (rc > 0) {
            if(pselect(fdm + 1, &fd_in, NULL, NULL, &timeout, NULL) > 0) {
                if (FD_ISSET(fdm, &fd_in)) { // Si hay datos en el lado maestro de la PTY
                    memset(input, 0, MAXCMD);
                    rc = read(fdm, input, sizeof (input));
                    resp_gnuch << input;
                    
                    if (resp_gnuch.str().length() > 0) {
                        
                        if(debug) {
                            cout << "main:" << endl;
                            cout << "   Datos recibidos de terminal esclavo." << endl;
                            cout << "   DATA: " << resp_gnuch.str() << endl;
                            cout << "   LEN:  " << resp_gnuch.str().length() << endl;
                        }
                        
                        if (Configuracion::getParametro("HABILITAR_MOVIMIENTO") == 1) {
                            respGNU = tab->analizarRespuestaGNUChess(resp_gnuch.str());  
                            
                            if (respGNU.mate_type == MateType::Black) {
                                DisplayLCD::borrarLCD();
                                DisplayLCD::escribirLCD("Fin del juego", 1);
                                DisplayLCD::escribirLCD("Ganan negras", 2);
                            }
                            
                            if (respGNU.mate_type == MateType::White) {
                                DisplayLCD::borrarLCD();
                                DisplayLCD::escribirLCD("Fin del juego", 1);
                                DisplayLCD::escribirLCD("Ganan blancas", 2);
                            }
                                
                            if(respGNU.move_type != MovementType::None) {
                                abb_chess.updateChessMove(&respGNU);
                                abb_chess.playMove();
                            }
                            resp_gnuch.clear();
                            memset(input, 0, MAXCMD);
                        }
                    } else if (rc < 0) mostrarError(errno, "lectura del lado maestro de la PTY");
                }
            } 
        }
    } else {
        // Proceso Hijo
        // ************

        struct termios slave_orig_term_settings; // Configuracion de terminal guardada
        struct termios new_term_settings; // Configuracion de terminal actual
        
        close(fdm); // Se cierra el lado maestro de la PTY

        // Se guardan los parametros por defecto del lado esclavo de la PTY
        rc = tcgetattr(fds, &slave_orig_term_settings);

        // Se habilita el modo RAW en el lado esclavo de la PTY
        new_term_settings = slave_orig_term_settings;
        cfmakeraw(&new_term_settings);
        tcsetattr(fds, TCSANOW, &new_term_settings);

        // Se configura el lado esclavo de la PTY, pasa a ser la entrada y 
        // salida estandar del proceso hijo

        // Se cierra stdin, stdout y stderr de la terminal actual
        close(0);
        close(1);
        close(2);

        // La PTY pasa a ser stdin, stdout y stderr
        retvals = dup(fds);
        retvals = dup(fds);
        retvals = dup(fds);

        close(fds); // Ahora el descriptor de archivo no sirve mas, se cierra

        setsid(); // El proceso actual pasa a ser lider de sesion

        // Como el proceso hijo es lider de sesion, configurar la terminal para que sea
        // el lado esclavo del PTY. (Esto es obligatorio para programas como la shell,
        // para hacer que manejen correctamente sus salidas)
        ioctl(0, TIOCSCTTY, 1);

        // Se ejecuta el proceso hijo
        execl("/usr/games/gnuchess", "gnuchess", "-x", (char *) NULL);

        return 1; // Si todo funciona bien, esta linea no deberia ejecutarse
    }

    delete tab;
    return 0;
    
} 