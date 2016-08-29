#include "Configuracion.h"

Configuracion* Configuracion::instancia;

/**
 * Constructor por defecto.
 */
Configuracion::Configuracion() {
    
    atexit(limpiar);
    
}

/**
 * Destructor por defecto.
 */
Configuracion::~Configuracion() {
    
}

/**
 * Carga los parametros desde el archivo de configuracion.\n
 * El nombre de archivo de configuracion por defecto es ./config.txt, es decir, 
 * busca en el directorio local un archivo llamado config.txt\n
 * Se sale del programa en los siguientes casos:.\n
 *    - El archivo de configuracion no existe.\n
 *    - El archivo de configuracion no se puede abrir.\n
 *    - El archivo de configuracion no contiene los parametros esenciales 
 *      para el funcionamiento del sistema.\n
 * Cada clase que utilice parametros de configuracion debe chequear la validez
 * de los mismos, ya que los parametros necesarios dependen de la geometria, del
 * actuador, etc.
 */
void Configuracion::leerConfiguracion(void) {

    vector<string> archivo;
    string linea, parametro;
    char temp[30];
    double valor = 0;

    // Leo el archivo y lo copio al vector, salgo si no puedo abrirlo o no existe.
    ifstream entrada("/home/guille/testbot/config.txt");
    if (!entrada) {
        cout << "No se pudo abrir el archivo de configuracion" << endl;
        exit(1);
    }

    while (getline(entrada, linea)) { archivo.push_back(linea); }
    
    cout << "Archivo de configuracion cargado: " << archivo.size() << " parametros encontrados." << endl;
    entrada.close();

    // Cargo los parametros en memoria, a medida que los voy leyendo del archivo.
    // Ignoro los comentarios (comienzan por #) y las lineas vacías.
    for (unsigned int i = 0; i < archivo.size(); i++) {
        if ((archivo.at(i).c_str()[0] == '#') || (archivo.at(i).length() < 3)) 
            continue;

        sscanf(archivo.at(i).c_str(), "%s %lf", temp, &valor);
        parametro.assign(temp);
        setParametro(parametro, valor);
    }

}

/**
 * Obtener un parametro de configuracion por nombre.\n
 * En el caso que el parametro no exista o tenga valor negativo, se llama a
 * c_Registro::registrar(R_ERROR, "...") con un mensaje descriptivo. Esto implica
 * que el programa finaliza cuando encuentra un error, ya que se asume que todos
 * los parametros del archivo son estrictamente necesarios para la ejecucion del
 * programa.
 * @param nombre String que contiene el nombre del parametro solicitado.
 * @return Double que contiene el valor del parametro.
 * @see getParametro(string nombre, int indice)
 * @see c_Registro::registrar(const int tipo, string mensaje, ...)
 */
double Configuracion::getParametro(string nombre) {
    
    if (getInstancia()->configuracion.find(nombre) != getInstancia()->configuracion.end()) {
        return getInstancia()->configuracion.at(nombre);
        cout << "Parametro consultado : " << nombre << " = " << getInstancia()->configuracion.at(nombre);
    } else {
        return -1;
    }
    
}

/**
 * Carga un parametro de configuracion en memoria.
 * @param nombre String que contiene el nombre del parametro a cargar.
 * @param valor Double que contiene el valor del parametro.
 * @see setParametro(string nombre, int indice, double valor)
 */
void Configuracion::setParametro(string nombre, double valor){
    
    if(getParametro(nombre) == -1)
        getInstancia()->configuracion.insert(pair<string, double>(nombre, valor));
    else
        getInstancia()->configuracion.find(nombre)->second = valor;
    
}

/**
 * @return Devuelve la unica instancia de c_Configuracion.
 */
Configuracion* Configuracion::getInstancia() {
    
    if (instancia == NULL) {
        instancia = new Configuracion();
    }
    return instancia;
    
}

/**
 * Funcion llamada al finalizar el programa, se asegura la ejecucion del destructor
 * por defecto de la clase (ejecuta @a delete sobre la instancia)
 */
void Configuracion::limpiar(void) {
    
    delete getInstancia()->instancia;
    
}
