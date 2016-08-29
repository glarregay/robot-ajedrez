#include "Muestreador.h"

Muestreador::Muestreador() {
    
    // Inicializar las variables de la clase desde el archivo de configuracion
    debug = Configuracion::getParametro("DEBUG");
    guardarImagenes = Configuracion::getParametro("DEBUG_GUARDAR_IMAGENES");
    
    origenTableroX = Configuracion::getParametro("ORIGEN_TABLERO_X");
    origenTableroY = Configuracion::getParametro("ORIGEN_TABLERO_Y");
    anchoTablero   = Configuracion::getParametro("ANCHO_TABLERO");
    altoTablero    = Configuracion::getParametro("ALTO_TABLERO");
    anchoCasilla   = anchoTablero / 8;
    altoCasilla    = altoTablero / 8;
    
    blurRadio = Configuracion::getParametro("BLUR_RADIO");
    blurSigma = Configuracion::getParametro("BLUR_SIGMA");
    claheGrid = Configuracion::getParametro("CLAHE_GRIDSIZE");
    claheClip = Configuracion::getParametro("CLAHE_CLIPLIMIT");
    
    if(debug) {
        cout << "Parametros de imagen:" << endl;
        cout << "    [ OrigenX, OrigenY ] = [ " << origenTableroX << ", " << origenTableroY << " ]" << endl;
        cout << "    [ ancho,   alto    ] = [ " << anchoTablero << ", " << altoTablero << " ]" << endl;
    }
    
}

Muestreador::Muestreador(const Muestreador& orig) {
}

Muestreador::~Muestreador() {
}

// Funciones principales

int Muestreador::procesarImagen(Mat &salida) {
    
    Mat imgTablero;
    vector<Mat> capas(3);
    Rect tablero(origenTableroX, origenTableroY, anchoTablero, altoTablero);
    
    // Algoritmo CLAHE
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(claheClip);
    clahe->setTilesGridSize(Size(claheGrid, claheGrid));
    
    if(guardarImagenes) {
        cout << "Guardando imagen original en foto-orig.jpg" << endl;
        imwrite("foto-orig.jpg", salida);
    }
        
    Mat imgTemp(salida, tablero);
    imgTemp.copyTo(imgTablero);
        
    if(debug)
        cout << "Filtrando..." << endl;
    
    GaussianBlur(imgTablero, salida, Size(blurRadio, blurRadio), blurSigma, 0);
        
    //autobalancearBlancos(salida);
    acomodarHistograma(salida);
    
    corregirGamma(salida, 1.8);
    
    if(debug)
        cout << "Mejorando contraste y saturacion..." << endl;
    
    // Convertir a Lab y promediar luminancia
    cvtColor(salida, salida, CV_BGR2HLS);
    split(salida, capas);
    promediarLuminancia(capas.at(0));
    promediarLuminancia(capas.at(1));
    //clahe->apply(capas.at(1), capas.at(1));
    promediarLuminancia(capas.at(2));   
    merge(capas, salida);
    acomodarHistograma(salida);
    //cvtColor(salida, salida, CV_HLS2BGR);    
    //cvtColor(salida, salida, CV_BGR2HSV);
    
    //incrementarSaturacion(salida);
    //autobalancearBlancos(salida);
    //acomodarHistograma(salida);
    
    if(guardarImagenes) {
        cout << "Guardando imagen procesada en foto-proc.jpg" << endl;
        imwrite("foto-proc.jpg", salida);
    }
    
    return 0;
    
}

// Funciones auxiliares (no necesariamente en uso)

void Muestreador::autobalancearBlancos(Mat &imagen) {
    
    // Adaptado de https://gist.github.com/tomykaira/94472e9f4921ec2cf582
    
    double descarte = 0.05;
    int histogramas[3][256];
    memset(histogramas, 0, 3*256*sizeof(int));

    // Cuento la cantidad de pixeles de cada intensidad, por cada canal
    for (int fila = 0; fila < imagen.rows; fila++) {
        uchar* pFila = imagen.ptr<uchar>(fila);
        for (int columna = 0; columna < imagen.cols; columna++) {
            for (int canal = 0; canal < 3; canal++) {
                histogramas[canal][pFila[columna * 3 + canal]]++;
            }
        }
    }

    // Calculo del histograma acumulado para cada canal
    int totalPixeles = imagen.cols * imagen.rows;
    int vmin[3], vmax[3];
    
    for (int canal = 0; canal < 3; canal++) {
        for (int intensidad = 0; intensidad < 255; intensidad++) 
            histogramas[canal][intensidad + 1] += histogramas[canal][intensidad];
        
        vmin[canal] = 0;
        vmax[canal] = 255;
        
        // El minimo valor a considerar por el histograma es aquel donde el 
        // acumulado supere el porcentaje de descarte (esto evita picos aislados)
        while (histogramas[canal][vmin[canal]] < descarte * totalPixeles)
            vmin[canal]++;
        while (histogramas[canal][vmax[canal]] > (1 - descarte) * totalPixeles)
            vmax[canal]--;
        if (vmax[canal] < 255 - 1)
            vmax[canal]++;
    }

    // Una vez conocido el rango de valores, se escala linealmente cada canal
    // para mapear el rango entre 0 y 255
    for (int fila = 0; fila < imagen.rows; fila++) {
        uchar* pFila = imagen.ptr<uchar>(fila);
        for (int columna = 0; columna < imagen.cols; columna++) {
            for (int canal = 0; canal < 3; canal++) {
                int valor = pFila[columna * 3 + canal];
                
                // Si esta fuera del rango, asumo el valor maximo o minimo
                if (valor < vmin[canal]) valor = vmin[canal];
                if (valor > vmax[canal]) valor = vmax[canal];
                
                pFila[columna * 3 + canal] = 
                        static_cast<uchar>((valor - vmin[canal]) * 255.0 / (vmax[canal] - vmin[canal]));
            }
        }
    }
}

void Muestreador::maximizarRango(Mat &canal) {
    
    uchar max=0, min=255;
    
    // Busco el maximo y minimo valor de cada canal
    for(int i = 0; i < canal.rows; i++) {
        for(int j = 0; j < canal.cols; j++) {
            if (canal.at<uchar>(j,i) > max)
                max = canal.at<uchar>(j,i);
            if (canal.at<uchar>(j,i) < min)
                min = canal.at<uchar>(j,i);
        }
    }
    
    // Mapeo lineal para llevar de (min, max) hasta (0,255)
    for(int i = 0; i < canal.rows; i++) {
        for(int j = 0; j < canal.cols; j++) {
            int valor = canal.at<uchar>(j,i);
            float nuevo = (valor-min) * 255.0/(max-min);
            canal.at<uchar>(j,i) = saturate_cast<uchar>((int)nuevo);
        }
    }
    
}

void Muestreador::acomodarHistograma(Mat &imagen) {
    
    vector<Mat> canales;
    
    split(imagen, canales);
    maximizarRango(canales.at(0));
    maximizarRango(canales.at(1));
    maximizarRango(canales.at(2));
    merge(canales, imagen);    
    
}

void Muestreador::incrementarSaturacion(Mat &imagen) {
        
    int incremento = Configuracion::getParametro("INC_SATURACION");
    if(incremento == 0)
        return;
    
    Mat tabla(1, 256, CV_8U);
    for( int i = 0; i < 256; i++ )
        tabla.at<uchar>(i) = saturate_cast<uchar>(i + incremento);
    
    Mat convertida;
    vector<Mat> hsv(3);
    
    cvtColor(imagen, convertida, CV_BGR2HSV);
    split(convertida, hsv);
    
    if(debug)
        cout << "Incrementando saturacion de color..." << endl;
    
    LUT(hsv.at(1), tabla, hsv.at(1));
    
    merge(hsv, imagen);
    cvtColor(imagen, imagen, CV_HSV2BGR);
        
}

void Muestreador::RGB2rgb(Mat &imagen) {
    
    if(debug)
        cout << "Convirtiendo a rgchroma..." << endl;
    
    for(int i=0;i<imagen.cols;i++) { 
        for(int j=0;j<imagen.rows;j++) { 
            Vec3b px = imagen.at<Vec3b>(j,i);
            float den = (px.val[0] + px.val[1] + px.val[2]);
            imagen.at<Vec3b>(j,i).val[0] = saturate_cast<uchar>((int)(255*px.val[0] / den));
            imagen.at<Vec3b>(j,i).val[1] = saturate_cast<uchar>((int)(255*px.val[1] / den));
            imagen.at<Vec3b>(j,i).val[2] = saturate_cast<uchar>((int)(255*px.val[2] / den));
        }
    }
    
}

void Muestreador::corregirColor(Mat &imagen) {
    
    double vecCorr[3] = {Configuracion::getParametro("CORR_R"), 
                         Configuracion::getParametro("CORR_G"), 
                         Configuracion::getParametro("CORR_B")};
    
    Mat tabla(1, 256, CV_8UC3);
    
    if(vecCorr[0] != 1 || vecCorr[1] != 1 || vecCorr[2] != 1) {
        if(debug)
            cout << "Correccion de color..." << endl;
        
        for( int i = 0; i < 256; i++ ) {
            tabla.at<Vec3b>(i)[0] = saturate_cast<uchar>(i*vecCorr[0]);
            tabla.at<Vec3b>(i)[1] = saturate_cast<uchar>(i*vecCorr[1]);
            tabla.at<Vec3b>(i)[2] = saturate_cast<uchar>(i*vecCorr[2]);
        }
        
        LUT(imagen, tabla, imagen);
    }
    
}

void Muestreador::corregirGamma( Mat &imagen, double gamma ) {
    
    double gammaInverso = 1.0 / gamma;
    
    if(gamma == 1.0)
        return;

    Mat tabla(1, 256, CV_8UC1 );
    uchar* pTabla = tabla.ptr();
    
    for( int i = 0; i < 256; i++ )
        pTabla[i] = (int)( pow( (double) i / 255.0, gammaInverso ) * 255.0 );

    LUT( imagen, tabla, imagen );
    
}   

void Muestreador::promediarLuminancia(Mat& canal) {
    
    if(debug)
        cout << "Promediando luminancia..." << endl;
    
    long suma = 0;
    long promedio = 0;
    
    for(int i=0;i<canal.cols;i++) { 
        for(int j=0;j<canal.rows;j++) { 
            uchar px = canal.at<uchar>(j,i);
            suma += px;
        }
    }
    
    promedio = suma / (canal.cols * canal.rows);
    
    for(int i=0;i<canal.cols;i++) { 
        for(int j=0;j<canal.rows;j++) { 
            int valor = canal.at<uchar>(j,i);
            valor += (128-promedio);
            
            canal.at<uchar>(j,i) = saturate_cast<uchar>(valor);            
        }
    }
    
}