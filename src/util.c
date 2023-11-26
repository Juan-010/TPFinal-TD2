#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "util.h"
#include <termios.h>

#define FD_STDIN 0

#define DELTAMS 20
extern unsigned int delays;
unsigned int delays = 100;
int key;

// Menues

// menu: Función para el menú principal
// Parámetros: Ninguno
// Valor de retorno: Entero que representa la opción elegida
int menu(void)
{
    system("clear");
    puts("Bienvenido al Trabajo práctico Final de Técnicas Digitales 2");
    puts("Elige una de las siguientes opciones:");
    puts("(1) Elegir Secuencia");
    puts("(2) Definir Velocidad Inicial");
    puts("(3) Modo Remoto");
    puts("(4) Salir");

    char choice;
    do
    {
        read(FD_STDIN, &choice, 1);
        choice -= 48;
    } while (choice < 1 || choice > 4);

    return choice;
}

// menuSecuencia: Función para el menú de selección de secuencia
// Parámetros: Ninguno
// Valor de retorno: Entero que representa la opción elegida
int menuSecuencia(void)
{
    system("clear");
    puts("Bienvenido al Trabajo práctico Final de Técnicas Digitales 2");
    puts("Elige una de las siguientes opciones:");
    puts("(1) El Auto Fantástico");
    puts("(2) El Choque");
    puts("(3) La Apilada");
    puts("(4) La Carrera");
    puts("(5) Alternado");
    puts("(6) Cortina 1");
    puts("(7) Cortina 2");
    puts("(8) Sombras");

    char choice;
    do
    {
        read(FD_STDIN, &choice, 1);
        choice -= 48;
    } while (choice < 1 || choice > 8);

    return choice;
}

// Utilidades

// getKey: Función para obtener la tecla presionada
// Parámetros: key - valor de la tecla presionada
// Valor de retorno: Entero que representa la tecla interpretada (1: Flecha arriba, 2: Flecha abajo, 3: Enter, 0: Otra tecla)
int getKey(unsigned int key)
{
    switch (key)
    {
    case 0x415b1b: // ARROW UP
        return 1;

    case 0x425b1b: // ARROW DOWN
        return 2;

    default:
        if ((key & 0x000000FF) == 0x0a) // ENTER
            return 3;
        else
            return 0; // OTHER
    }
}

// myDelay: Función para gestionar el retardo y la entrada del usuario
// Parámetros: mode - enum mode que indica si el modo es LOCAL o REMOTE
//             serial_port - puerto serial para el modo REMOTE
// Valor de retorno: 1 si la tecla Enter fue presionada, 0 en otros casos
int myDelay(enum mode mode, int serial_port)
{
    if (mode == LOCAL)
    {
        read(0, &key, 3);
        key = getKey(key);
    }
    if (mode == REMOTE)
    {
        key = 0;
        if (serialDataAvail(serial_port))
            key = serialGetchar(serial_port);
    }

    if (key == 3)
        return 1;
    delays = setDelay((key == 1) ? delays - DELTAMS : (key == 2) ? delays + DELTAMS : delays);
    delay(delays);
    return 0;
}

// login: Función para realizar el inicio de sesión
// Parámetros: password - cadena de caracteres que representa la contraseña esperada
// Valor de retorno: 1 si la contraseña es correcta, 0 en otros casos
int login(char *password)
{
    system("clear");
    int ret_value = 0;
    struct termios login_old, login_new;
    tcgetattr(FD_STDIN, &login_old); // lee atributos del teclado
    login_new = login_old;
    login_new.c_lflag &= ~(ECHO | ICANON); // anula entrada canónica y eco
    login_new.c_cc[VMIN] = 1;              // setea el minimo numero de caracteres que espera read()
    login_new.c_cc[VTIME] = 0;             // setea tiempo maximo de espera de caracteres que lee read()
    tcsetattr(FD_STDIN, TCSANOW, &login_new);

    int tries = 3;
    char key = 0, attempt[6] = {0};
    while (tries > 0)
    {
        printf("Ingrese su password de 5 dígitos: ");
        int i = 0;
        while ((key = getchar()) != 10)
        {
            if (i == 5)
                break;
            attempt[i] = key;
            printf("*");
            i++;
        }
        printf("\n");
        if (!strcmp(attempt, password))
        {
            ret_value = 1;
            break;
        }
        else
        {
            system("clear");
            printf("Password no válida\n");
            tries--;
        }
    }

    tcsetattr(FD_STDIN, TCSANOW, &login_old); // actualiza con los valores previos
    return ret_value;
}

// setMinChar: Función para configurar el número mínimo de caracteres para la entrada del usuario
// Parámetros: minChar - número mínimo de caracteres
// Valor de retorno: Ninguno
void setMinChar(int minChar)
{
    struct termios term;
    tcgetattr(FD_STDIN, &term);
    term.c_cc[VMIN] = minChar;
    tcsetattr(FD_STDIN, TCSANOW, &term);
}
