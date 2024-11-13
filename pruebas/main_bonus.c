#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    int     fd3;
    char    *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    fd3 = open("test3.txt", O_RDONLY);
    
    // Leer alternadamente de diferentes FDs
    line = get_next_line(fd1);
    printf("fd1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("fd2: %s", line);
    free(line);
    
    line = get_next_line(fd3);
    printf("fd3: %s", line);
    free(line);
    
    // Segunda ronda de lecturas
    line = get_next_line(fd1);
    printf("fd1: %s", line);
    free(line);
    
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
} 