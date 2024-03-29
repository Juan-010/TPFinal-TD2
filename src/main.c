#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>
#include <ads1115.h>
#include <termios.h>
#include <unistd.h>
#include "sequence.h"
#include "util.h"

#define ENTER 10
#define FD_STDIN 0
#define AD_BASE 120
#define ADDR 0x48
extern unsigned int delays;
char *pass = "12345";

int main(void)
{
    // Login
    if (!login(pass)) // si login devuelve 0, termina el programa
        exit(EXIT_FAILURE);

    // Configuraciones
    wiringPiSetup();
    int serial_port = serialOpen("/dev/ttyS0", 115200);
    ads1115Setup(AD_BASE, ADDR);
    for (int i = 0; i < 8; i++)
        pinMode(i, OUTPUT);

    // Terminal no bloqueante inicial
    struct termios t_old, t_new;
    tcgetattr(FD_STDIN, &t_old); // lee atributos del teclado
    t_new = t_old;
    t_new.c_lflag &= ~(ECHO | ICANON); // anula entrada canónica y eco
    t_new.c_cc[VMIN] = 1;              // setea el minimo numero de caracteres que espera read()
    t_new.c_cc[VTIME] = 0;             // setea tiempo maximo de espera de caracteres que lee read()
    tcsetattr(FD_STDIN, TCSANOW, &t_new);

    // Variables Auxiliares
    int choice;
    int key = 0;

    while (1)
    { // Bucle principal
        choice = menu();

        switch (choice)
        {
        case 1: // Seleccion de Secuencias
            choice = menuSecuencia();
            setMinChar(0);

            system("clear");
            switch (choice)
            {
            case 1:
                puts("El Auto Fantastico (Enter para Salir)");
                while (1)
                {
                    if (autoFantastico(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 2:
                puts("El Choque (Enter para Salir)");
                while (1)
                {
                    if (elChoque(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 3:
                puts("La Apilada (Enter para Salir)");
                while (1)
                {
                    if (laApilada(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 4:
                puts("La Carrera (Enter para Salir)");
                while (1)
                {
                    if (laCarrera(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 5:
                puts("Alternado (Enter para Salir)");
                while (1)
                {
                    if (alternado(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 6:
                puts("Cortina 1 (Enter para Salir)");
                while (1)
                {
                    if (cortina1(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 7:
                puts("Cortina 2 (Enter para Salir)");
                while (1)
                {
                    if (cortina2(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            case 8:
                puts("Sombras (Enter para Salir)");
                while (1)
                {
                    if (sombras(LOCAL, 0) == 1)
                    {
                        ledsOff();
                        break;
                    }
                }
                break;

            default:
                puts("Opción inválida");
            }
            setMinChar(1);
            break;

        case 2: // Configuracion de Velocidad
            setMinChar(0);

            int firstEntry = 1;
            while (key != ENTER)
            {
                unsigned int reading = analogRead(AD_BASE);
                reading = (reading / 32768) * 1000;
                if ((reading != delays) || firstEntry)
                {
                    system("clear");
                    puts("Definir Velocidad Inicial (Enter para Salir)");
                    delays = reading;
                    printf("Velocidad Inicial: %d ms\n", delays);
                    firstEntry = 0;
                }
                read(FD_STDIN, &key, 1);
            }
            setMinChar(1);
            key = 0;
            break;

        case 3: // Modo Remoto
            system("clear");
            unsigned char serialDat;
            puts("Modo de control remoto. Presione ENTER para salir.");
            setMinChar(0);
            while (key != ENTER)
            {
                if (serialDataAvail(serial_port))
                {
                    serialDat = serialGetchar(serial_port);
                    switch (serialDat)
                    {
                    case 11:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (autoFantastico(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 12:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (elChoque(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 13:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (laApilada(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 14:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (laCarrera(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 15:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (alternado(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 16:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (cortina1(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 17:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (cortina2(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    case 18:
                        while (key != ENTER)
                        {
                            read(FD_STDIN, &key, 1);
                            if (sombras(REMOTE, serial_port) == 1)
                            {
                                ledsOff();
                                break;
                            }
                        }
                        break;
                    } // Switch SerialDat
                }     // if serialDataAvail
                read(FD_STDIN, &key, 1);
            } // while
            setMinChar(1);
            key = 0;
            break;
        case 4: // Salir
            tcsetattr(FD_STDIN, TCSANOW, &t_old);
            exit(EXIT_SUCCESS);

        default: // Opcion invalida
            puts("Opción inválida");

        }                                 // Switch choice
    }                                     // while(1)
    tcsetattr(FD_STDIN, TCSANOW, &t_old); // actualiza con los valores previos
    return 0;
}
