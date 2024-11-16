#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int main(void)
{
    char *line;
    int fd1, fd2;

    printf("\n=== GET_NEXT_LINE BONUS TESTER ===\n");
    printf("Testing multiple file descriptors...\n\n");

    // Crear archivos de prueba
    system("echo 'Línea 1 del archivo 1\nLínea 2 del archivo 1' > test1.txt");
    system("echo 'Línea 1 del archivo 2\nLínea 2 del archivo 2' > test2.txt");

    // Abrir archivos
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    printf("=== Leyendo alternadamente de archivos y stdin ===\n\n");

    // Primera ronda
    printf("Primera ronda:\n");
    line = get_next_line(fd1);
    printf("Archivo 1: '%s'\n", line);
    free(line);

    printf("Escribe algo para stdin: ");
    line = get_next_line(0);
    printf("Stdin: '%s'\n", line);
    free(line);

    line = get_next_line(fd2);
    printf("Archivo 2: '%s'\n", line);
    free(line);

    // Segunda ronda
    printf("\nSegunda ronda:\n");
    line = get_next_line(fd1);
    printf("Archivo 1: '%s'\n", line);
    free(line);

    printf("Escribe algo más para stdin: ");
    line = get_next_line(0);
    printf("Stdin: '%s'\n", line);
    free(line);

    line = get_next_line(fd2);
    printf("Archivo 2: '%s'\n", line);
    free(line);

    // Cerrar archivos
    close(fd1);
    close(fd2);

    // Limpiar archivos de prueba
    system("rm -f test1.txt test2.txt");

    printf("\n=== Test de error ===\n");
    printf("FD inválido (-1): %s%s%s\n", 
        get_next_line(-1) == NULL ? GREEN "OK" : RED "KO", RESET,
        " (NULL esperado)");

    return (0);
}
