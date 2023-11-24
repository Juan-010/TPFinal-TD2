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
#define FD_STDIN 0
#define AD_BASE 120
#define ADDR 0x48
extern unsigned int delays;
char *pass = "12345";
int main(void){
    if(!login(pass))
        return(1);

    wiringPiSetup();
    int serial_port = serialOpen("/dev/ttyS0", 115200);
    ads1115Setup(AD_BASE, ADDR);		//configuracion del ADC	
    for(int i=0;i<8;i++)
        pinMode(i,OUTPUT);

    struct termios t_old, t_new;
    tcgetattr(FD_STDIN, &t_old); // lee atributos del teclado
    t_new = t_old;
    t_new.c_lflag &= ~(ECHO | ICANON); // anula entrada canónica y eco
    t_new.c_cc[VMIN]=1;			//setea el minimo numero de caracteres que espera read()
	t_new.c_cc[VTIME] = 0;			//setea tiempo maximo de espera de caracteres que lee read()
    tcsetattr(FD_STDIN,TCSANOW,&t_new);

    int choice;
    int key = 0;
    
    while(1){ // Bucle principal
        choice = menu();

        switch(choice){
            case 1:
                choice = menuSecuencia();
                t_new.c_cc[VMIN]=0;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                system("clear");
                switch(choice){
                    case 1:
                        puts("El Auto Fantastico (Enter para Salir)");
                        while(1){
                            if (autoFantastico(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 2:
                        puts("El Choque (Enter para Salir)");
                        while(1){
                            if (elChoque(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 3:
                        puts("La Apilada (Enter para Salir)");
                        while(1){
                            if (laApilada(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 4:
                        puts("La Carrera (Enter para Salir)");
                        while(1){
                            if (laCarrera(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 5:
                        puts("Alternado (Enter para Salir)");
                        while(1){
                            if (alternado(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 6:
                        puts("Cortina (Enter para Salir)");
                        while(1){
                            if (cortina(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 7:
                        puts("Sombras (Enter para Salir)");
                        while(1){
                            if (sombras(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    case 8:
                        puts("Shimmer (Enter para Salir)");
                        while(1){
                            if (shimmer(LOCAL, 0) == 1){
                                ledsOff();
                                break;
                            }
                        }
                    break;

                    default: 
                        puts("Opción inválida");
                }
                t_new.c_cc[VMIN]=1;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                break;

            case 2:
                t_new.c_cc[VMIN]=0;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                while(key != 10){
                    system("clear");
                    puts("Definir Velocidad Inicial (Enter para Salir)");
                    delays = (unsigned int)(((float) analogRead(AD_BASE) / 32768) * 1000);
                    printf("Velocidad Inicial: %d ms\n", delays);
                    read(0, &key, 1);
                }
                t_new.c_cc[VMIN]=1;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                key = 0;
                break;

            case 3:
                system("clear");
                unsigned char serialDat;
                puts("Modo de control remoto. Presione ENTER para salir.");
                t_new.c_cc[VMIN]=0;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                while(key != 10){
                    if(serialDataAvail(serial_port)){
                        serialDat = serialGetchar(serial_port);
                        switch(serialDat){
                            case 11:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (autoFantastico(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 12:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (elChoque(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 13:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (laApilada(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 14:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (laCarrera(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 15:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (alternado(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 16:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (cortina(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 17:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (sombras(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            case 18:
                                while(key!=10){
                                    read(0, &key, 1);
                                    if (shimmer(REMOTE, serial_port) == 1){
                                        ledsOff();
                                        break;
                                    }
                                }
                                break;
                            default:
                            ;
                        }
                    }
                    read(0, &key, 1);
                }
                t_new.c_cc[VMIN]=1;
                tcsetattr(FD_STDIN,TCSANOW,&t_new);
                key = 0;
                break;
            case 4:
                tcsetattr(FD_STDIN, TCSANOW, &t_old);
                exit(0);
            default: 
                puts("Opción inválida");
        }
    }
    tcsetattr(FD_STDIN, TCSANOW, &t_old); // actualiza con los valores previos 
    return 0;
}