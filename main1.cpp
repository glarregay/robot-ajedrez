
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int in[2], out[2];
FILE *entrada;
FILE *salida;

void leer() {
  int c;
  while ((c = fgetc(entrada)) != EOF)
    putchar (c);
}

/* Write some random text to the pipe. */
void escribir(char *texto) {
  fprintf (salida, "%s", texto);
  fflush(salida);
}

void error(char *s) {
    perror(s);
    exit(1);
}

int inicializarPipes() {

    /* In a pipe, xx[0] is for reading, xx[1] is for writing */
    if (pipe(in) < 0) error("pipe in");
    if (pipe(out) < 0) error("pipe out");

}

int redireccionarPipes() {

    /* Cerrar stdin, stdout, stderr */
    close(0);
    close(1);
    close(2);
    
    /* Crear los pipes, y linkearlos con std* */
    dup2(in[0], 0);
    dup2(out[1], 1);
    dup2(out[1], 2);

    /* Cerrar los extremos de los pipes usados por el padre, para evitar que
       no reciban los EOF cuando se cierre el pipe */
    close(in[1]);
    close(out[0]);
   
}

int main() {
    int n, pid;
    char buf[255];

    inicializarPipes();

    if ((pid = fork()) == 0) {
        /* Proceso hijo */
        redireccionarPipes();
        
        /* Ejecutar el proceso hijo */
        execl("/usr/bin/hexdump", "hexdump", "-C", (char *) NULL);
        error("Could not exec hexdump");
    }

    printf("Ejecutado el proceso 'hexdump -C' con pid %d\n", pid);

    /* Proceso padre */
    /* Cerramos los extremos del pipe que usa el hijo para leer / escribir
     * para que cuando enviemos los EOF se transmitan correctamente. */
    close(in[0]);
    close(out[1]);
    
    salida = fdopen(in[1], "w");
    setbuf(salida, NULL);
    entrada = fdopen(out[0], "r");
    setbuf(entrada, NULL);

    //printf("<- %s", data);
    /* Write some data to the childs input */
    escribir("hola");
    freopen(NULL, "w", salida);

    /* Because of the small amount of data, the child may block unless we
     * close it's input stream. This sends an EOF to the child on it's
     * stdin.
     */
    //close(in[1]);
    
    /* Read back any output */
    leer();
    freopen(NULL, "r", entrada);
    
    escribir("chau");
    fclose(salida);
    leer();
    fclose(entrada);
    
    exit(0);
}

