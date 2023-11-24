#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "util.h"
//Requeridos por cátedra
void ledsOff(void);
int autoFantastico(enum mode, int);
int elChoque(enum mode, int);
int laApilada(enum mode, int);
int laCarrera(enum mode, int);

//Definidos por grupo
int alternado(enum mode, int);
int cortina(enum mode, int);
int sombras(enum mode, int);
int shimmer(enum mode, int);
#endif // SEQUENCE_H