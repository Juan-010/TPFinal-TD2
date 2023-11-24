#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "util.h"
#define FD_STDIN 0

#define DELTAMS 20
extern unsigned int delays;
unsigned int delays = 100;
int key;
//Menues

int menu(void){
    system("clear");
    puts("Bienvenido al Trabajo práctico Final de Técnicas Digitales 2");
    puts("Elige una de las siguientes opciones:");
    puts("(1) Elegir Secuencia");
    puts("(2) Definir Velocidad Inicial");
    puts("(3) Modo Remoto");
    puts("(4) Salir");

    char choice; 
    do{
    read(FD_STDIN, &choice, 1);
    choice -= 48;
    }while(choice < 1 || choice > 4);
    
    return choice;
}

int menuSecuencia(void){
    system("clear");
    puts("Bienvenido al Trabajo práctico Final de Técnicas Digitales 2");
    puts("Elige una de las siguientes opciones:");
    puts("(1) El Auto Fantástico");
    puts("(2) El Choque");
    puts("(3) La Apilada");
    puts("(4) La Carrera");
    puts("(5) Alternado");
    puts("(6) Cortina");
    puts("(7) Sombras");
    puts("(8) Shimmer");
    char choice; 
    do{
    read(FD_STDIN, &choice, 1);
    choice -= 48;
    }while(choice < 1 || choice > 8);
    
    return choice;
}


//Utilidades
int getKey(unsigned int key){
    switch(key){
        case 0x415b1b: //ARROW UP
        return 1;

        case 0x425b1b: //ARROW DOWN
        return 2;

        case 0x435b1b: //ARROW LEFT
        return 3;

        case 0x445b1b: //ARROW RIGHT
        return 4;

        default:
        if ((key & 0x00000000FF) == 0x0a)
            return 5; //ENTER
        else
            return 0; //NO KEY
    }
        
}

void setDelay(int newDelay){
    if (newDelay < 10)
        delays = 10;
    else
        delays = newDelay;
}

int myDelay(enum mode mode, int serial_port){
    if(mode == LOCAL){
            read(0, &key, 3);
            key = getKey(key);  
        }
        if(mode == REMOTE){
            key = 0;
            if (serialDataAvail(serial_port))
                key = serialGetchar(serial_port);
        }

        if (key == 5)
                return 1;
        setDelay((key == 1) ? delays + DELTAMS : (key == 2) ? delays - DELTAMS : delays);
        delay(delays);
        return 0;
}


