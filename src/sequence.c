#include <wiringPi.h>
#include <unistd.h>
#include "sequence.h"
#include "keys.h"
#define DELTAMS 50
extern unsigned int delays;
unsigned int delays = 100;

const int leds[8] = {0,1,2,3,4,5,6,7};
int arrow;
int mat_laCarrera[16][8]={
    {0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {1,0,0,1,0,0,0,0},
    {0,1,0,0,1,0,0,0},
    {0,0,1,0,1,0,0,0},
    {0,0,0,1,0,1,0,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,1}};

int mat_laApilada[37][8]={
    {0},
    {0,0,0,0,0,0,0,1},{0,0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0,0},{0,0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0,0},{0,0,1,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},
    {1,0,0,0,0,1,0,0},{1,0,0,0,1,0,0,0},
    {1,0,0,1,0,0,0,0},{1,0,1,0,0,0,0,0},
    {1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,1},
    {1,1,0,0,0,0,1,0},{1,1,0,0,0,1,0,0},
    {1,1,0,0,1,0,0,0},{1,1,0,1,0,0,0,0},
    {1,1,1,0,0,0,0,0},{1,1,1,0,0,0,0,1},
    {1,1,1,0,0,0,1,0},{1,1,1,0,0,1,0,0},
    {1,1,1,0,1,0,0,0},{1,1,1,1,0,0,0,0},
    {1,1,1,1,0,0,0,1},{1,1,1,1,0,0,1,0},
    {1,1,1,1,0,1,0,0},{1,1,1,1,1,0,0,0},
    {1,1,1,1,1,0,0,1},{1,1,1,1,1,0,1,0},
    {1,1,1,1,1,1,0,0},{1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,0},{1,1,1,1,1,1,1,1}};

int mat_cortina[16][8]={
    {0},
    {1,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,1,0,0,0,0},
    {1,1,1,1,1,0,0,0},
    {1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1},
    {0,0,0,1,1,1,1,1},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1},
    };

int mat_shimmer[16][8]={
    {0},
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1},
    {0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0}};    

void ledsOff(void){
    for(int i=0; i<8; i++)
        digitalWrite(leds[i], LOW);
}

void setDelay(int newDelay){
    if (newDelay < 10)
        delays = 10;
    else
        delays = newDelay;
}

//Requeridos por cátedra
int autoFantastico(void){
    for(int i=0;i<8;i++)
    {
        digitalWrite(leds[i],HIGH);

        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
        digitalWrite(leds[i],LOW);
    }

    for(int j=7;j>=0;j--)
    {
        digitalWrite(leds[j],HIGH);
        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
        digitalWrite(leds[j],LOW);
    }
    return 0;
}
int elChoque(void){
    for(int i=0; i<8; i++){
        digitalWrite(leds[i], HIGH);
        digitalWrite(leds[7-i], HIGH);

        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);

        digitalWrite(leds[i], LOW);
        digitalWrite(leds[7-i], LOW);
    }
    return 0;
}
int laApilada(void){
    for(int i=0;i<37;i++){
        for(int j = 0; j<8; j++)
            digitalWrite(leds[j], mat_laApilada[i][j]);
        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
    }
    return 0;
}
int laCarrera(void){
    for(int i=0;i<16;i++){
        for(int j = 0; j<8; j++)
            digitalWrite(leds[j], mat_laCarrera[i][j]);
        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
    }
    return 0;
}

//Definidos por grupo
int alternado(void){
    for(int i=0; i<8; i+=2)
        digitalWrite(leds[i], HIGH);
    for(int i=1; i<8; i+=2)
        digitalWrite(leds[i], LOW);

    arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);

    for(int i=0; i<8; i+=2)
        digitalWrite(leds[i], LOW);
    for(int i=1; i<8; i+=2)
        digitalWrite(leds[i], HIGH);

    arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
return 0;}
int cortina(void){
    for(int i=0;i<16;i++){
        for(int j = 0; j<8; j++)
            digitalWrite(leds[j], mat_cortina[i][j]);

        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
    }
    return 0;
}
int sombras(void){
    for(int i = 0; i<8; i++){
        digitalWrite(leds[i], HIGH);
    }
    for(int i=0;i<8;i++)
    {
        digitalWrite(leds[i],LOW);

       arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);

        digitalWrite(leds[i],HIGH);
    }

    for(int j=7;j>=0;j--)
    {
        digitalWrite(leds[j],LOW);

        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);

        digitalWrite(leds[j],HIGH);
    }
    return 0;
}

int shimmer(void){
    for(int i=0;i<16;i++){
        for(int j = 0; j<8; j++)
            digitalWrite(leds[j], mat_shimmer[i][j]);

        arrow = getArrow();
        if (arrow == 5)
            return 1;
        setDelay((arrow == 1) ? delays + DELTAMS : (arrow == 2) ? delays - DELTAMS : delays);
        delay(delays);
    }
    return 0;
}