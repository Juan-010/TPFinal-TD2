

#include <stdio.h>  /* Standard input / output definitions */
#include <stdlib.h> 
#include <fcntl.h>  /* File control definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include "termset.h"
#define FD_STDIN 0
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
void keyControl(int fd){
	unsigned int key;
	unsigned char dato;
  while (1)
  {
	read(0, &key, 3);
	dato = getKey(key);
	key = 0;
	write(fd, &dato, sizeof(dato));
	if(dato == 3)
		break;
  }
}

int main (void){
  int fd ; /* Descriptor de archivo del puerto serie*/
	struct termios old_serial, new_serial, old_term, new_term;
  char dato = 0;
	unsigned int key = 0;

	tcgetattr(FD_STDIN, &old_term); // lee atributos del teclado
	
	//Setup de terminal
  new_term = old_term;
  new_term.c_lflag &= ~(ECHO | ICANON); // anula entrada canónica y eco
  new_term.c_cc[VMIN]=1;			//setea el minimo numero de caracteres que espera read()
	new_term.c_cc[VTIME] = 0;			//setea tiempo maximo de espera de caracteres que lee read()
  tcsetattr(FD_STDIN,TCSANOW,&new_term);
  
	//Aperturae puerto
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY );
  if (fd == -1)
  {
  printf("ERROR : no se pudo abrir el dispositivo.\n");
  return -1;
  }
  if (termset(fd , 115200, &old_serial, &new_serial) == -1)
  {
  printf (" ERROR : no se pudo configurar el TTY \n" );
  return -1;
  }
  tcflush(fd, TCIOFLUSH);

	//Bucle Principal
	while(key != 10){
		system("clear");
    puts("Bienvenido al programa auxiliar del TPF de Técnicas Digitales 2");
    puts("Elige una de las siguientes opciones:");
    puts("(1) El Auto Fantástico");
    puts("(2) El Choque");
    puts("(3) La Apilada");
    puts("(4) La Carrera");
    puts("(5) Alternado");
    puts("(6) Cortina 1");
    puts("(7) Cortina 2");
    puts("(8) Sombras");
    puts("(ENTER) Salir");
		read(0, &key, 1);
		switch(key){
			case '1':
				dato = 11;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("El Auto Fantastico (Enter para Salir)");
				keyControl(fd);
				break;

			case '2':
				dato = 12;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("El Choque (Enter para Salir)");
				keyControl(fd);
				break;
			case '3':	
				dato = 13;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("La Apilada (Enter para Salir)");
				keyControl(fd);
				break;
			case '4':
				dato = 14;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("La Carrera (Enter para Salir)");
				keyControl(fd);
				break;
			case '5':
				dato = 15;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("Alternado (Enter para Salir)");
				keyControl(fd);
				break;
			case '6':
				dato = 16;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("Cortina 1 (Enter para Salir)");
				keyControl(fd);
				break;
			case '7':
				dato = 17;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("Cortina 2 (Enter para Salir)");
				keyControl(fd);
				break;
			case '8':
				dato = 18;
  			write(fd, &dato, sizeof(dato));
				system("clear");
				puts("Sombra (Enter para Salir)");
				keyControl(fd);
				break;
			default:
				break;
	}
	}
  tcflush(fd, TCIOFLUSH);
close(fd);
tcsetattr(FD_STDIN,TCSANOW,&old_term);
return 0;
}
