#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#define FD_STDIN 0
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

