/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"

static void	print_separator(void)
{
    printf("%s==========================================%s\n", BLUE, RESET);
}

static void	print_header(void)
{
    printf("\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║     GET_NEXT_LINE TESTER by ccarrero     ║\n");
    printf("║          (testing myself lol)            ║\n");
    printf("╚══════════════════════════════════���═══════╝\n");
    printf("Buffer size: %d\n", BUFFER_SIZE);
}

static void	print_footer(void)
{
    printf("\n=== INSTRUCCIONES ADICIONALES ===\n");
    printf("==========================================\n");
    printf("1. Prueba con diferentes BUFFER_SIZE:\n");
    printf("   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 (mínimo)\n");
    printf("   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 (normal)\n");
    printf("   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10000000 (grande)\n\n");
    printf("2. Verifica memory leaks:\n");
    printf("   valgrind --leak-check=full ./gnl\n");
    printf("   valgrind --leak-check=full --show-leak-kinds=all ./gnl (detallado)\n");
    printf("==========================================\n");
    printf("\nBuena suerte a mí mismo en la corrección! 🍀\n");
    printf("Gracias por corregirme!\n");
}

static void	test_error_cases(void)
{
    char	*line;
    int     tests_passed = 0;
    int     fd;

    printf("\n%s=== TEST ERROR CASES ===%s\n", MAGENTA, RESET);
    print_separator();
    
    // Test 1: FD negativo
    line = get_next_line(-1);
    printf("1. FD negativo (-1): %s", line ? RED "KO" : GREEN "OK" RESET);
    printf(" (returned: %s)\n", line ? line : "NULL");
    if (!line) tests_passed++;
    if (line) free(line);

    // Test 2: FD inválido
    line = get_next_line(42);
    printf("2. FD inválido (42): %s", line ? RED "KO" : GREEN "OK" RESET);
    printf(" (returned: %s)\n", line ? line : "NULL");
    if (!line) tests_passed++;
    if (line) free(line);

    // Test 3: Archivo sin permisos
    system("echo 'test' > no_perms.txt && chmod 000 no_perms.txt");
    fd = open("no_perms.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("3. Archivo sin permisos: %s", line ? RED "KO" : GREEN "OK" RESET);
    printf(" (returned: %s)\n", line ? line : "NULL");
    if (!line) tests_passed++;
    if (line) free(line);
    if (fd > 0) close(fd);
    system("rm -f no_perms.txt");

    printf("\n→ Tests de error pasados: %s%d/3%s\n", 
        tests_passed == 3 ? GREEN : RED, tests_passed, RESET);
}

static void	test_file_content(void)
{
    int tests_passed = 0;
    char *line;

    printf("\n=== TEST FILE CONTENT ===\n");
    print_separator();
    printf("Escribe texto para probar:\n");

    // Test 1: Línea normal
    printf("1. Línea normal:\n");
    line = get_next_line(0);
    if (line)
    {
        printf("→ Leído: '%s'\n", line);
        if (line[0] != '\n')  // Validar que no sea línea vacía
        {
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            tests_passed++;
        }
        else
        {
            printf("→ Resultado: %sKO%s (línea vacía)\n", RED, RESET);
        }
        free(line);
    }

    // Test 2: Lnea vacía
    printf("\n2. Línea vacía (pulsa SOLO Enter):\n");
    line = get_next_line(0);
    if (line)
    {
        printf("→ Leído: '%s'", line);
        if (line[0] == '\n')  // Validar que sea línea vacía
        {
            printf(" (%s - línea vacía)\n", "OK");
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            tests_passed++;
        }
        else
        {
            printf(" (%s - línea vacía)\n", "KO");
            printf("→ Resultado: %sKO%s (se esperaba línea vacía)\n", RED, RESET);
        }
        free(line);
    }

    // Test 3: Línea vacía después de texto
    printf("\n3. Línea vacía después de texto (escribe texto y se añadirá una línea vacía):\n");
    line = get_next_line(0);
    if (line)
    {
        printf("→ Leído: '%s'\n", line);
        if (line[0] != '\n')  // Validar que no sea línea vacía
        {
            free(line);
            printf("\n");  // Añadir línea vacía automáticamente
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            tests_passed++;
        }
        else
        {
            printf("→ Resultado: %sKO%s (se esperaba texto)\n", RED, RESET);
            free(line);
        }
    }

    printf("\n→ Tests de contenido pasados: %s%d/3%s\n", 
        tests_passed == 3 ? GREEN : RED, tests_passed, RESET);
}

static void test_special_cases(void)
{
    int tests_passed = 0;
    char *line;

    printf("\n=== TEST SPECIAL CASES ===\n");
    print_separator();

    // Test 1: Línea corta (<4 chars)
    printf("1/3. Línea corta (<4 chars):\n");
    line = get_next_line(0);
    if (line)
    {
        if (strlen(line) < 5)  // 4 chars + \n
        {
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            printf("→ Leído: '%s'\n", line);
            tests_passed++;
        }
        else
            printf("→ Resultado: %sKO%s (línea demasiado larga)\n", RED, RESET);
        free(line);
    }

    // Test 2: Caracteres especiales
    printf("\n2/3. Línea con caracteres especiales (pulsa la tecla TAB):\n");
    line = get_next_line(0);
    if (line)
    {
        printf("→ Leído: '%s'\n", line);
        // Buscar un carácter de tabulación real (ASCII 9)
        if (strchr(line, 9))  // 9 es el código ASCII para TAB
        {
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            tests_passed++;
        }
        else
        {
            printf("→ Resultado: %sKO%s (no se detectó TAB)\n", RED, RESET);
        }
        free(line);
    }

    // Test 3: Línea larga
    printf("\n3/3. Línea larga (>1024 chars)\n");
    printf("Escribe caracteres hasta superar 1024:\n");
    line = get_next_line(0);
    if (line)
    {
        int len = strlen(line);
        if (len > 1024)
        {
            printf("→ Resultado: %sOK%s\n", GREEN, RESET);
            printf("→ Longitud: %d caracteres\n", len);
            tests_passed++;
        }
        else
        {
            printf("→ Resultado: %sKO%s (faltan %d caracteres)\n", 
                RED, RESET, 1024 - len);
        }
        free(line);
    }

    printf("\n→ Tests especiales pasados: %s%d/3%s\n", 
        tests_passed == 3 ? GREEN : RED, tests_passed, RESET);
}

static void test_multiple_lines(void)
{
    printf("\n%s=== TEST MULTIPLE LINES ===%s\n", MAGENTA, RESET);
    print_separator();
    printf("Escribe 3 líneas (pulsa Enter después de cada una):\n");
    
    char *line;
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        line = get_next_line(0);
        if (line)
        {
            printf("Línea %d: '%s'\n", i + 1, line);
            free(line);
            count++;
        }
    }
    printf("\n→ Test múltiples líneas: %s%s%s\n", 
        count == 3 ? GREEN : RED,
        count == 3 ? "OK" : "KO",
        RESET);
}

int main(void)
{
    print_header();
    test_error_cases();
    test_file_content();
    test_special_cases();
    test_multiple_lines();
    print_footer();
    return (0);
}
