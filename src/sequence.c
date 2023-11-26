#include <wiringPi.h>
#include <stdio.h>
#include <wiringSerial.h>
#include <unistd.h>
#include "sequence.h"
#include "util.h"

const int leds[8] = {0, 1, 2, 3, 4, 5, 6, 7};

int mat_laCarrera[16][8] = {
    {0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}};

int mat_laApilada[37][8] = {
    {0},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 1, 0, 0},
    {1, 1, 0, 0, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 0},
    {1, 1, 1, 0, 0, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}};

int mat_cortina1[16][8] = {
    {0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
};

int mat_cortina2[15][8] = {
    {0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

void ledsOff(void)
{
    for (int i = 0; i < 8; i++)
        digitalWrite(leds[i], LOW);
}

// Requeridos por cátedra
int autoFantastico(enum mode mode, int serial_port)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(leds[i], HIGH);

        if (myDelay(mode, serial_port))
            return 1;

        digitalWrite(leds[i], LOW);
    }

    for (int j = 7; j >= 0; j--)
    {
        digitalWrite(leds[j], HIGH);

        if (myDelay(mode, serial_port))
            return 1;
        digitalWrite(leds[j], LOW);
    }
    return 0;
}
int elChoque(enum mode mode, int serial_port)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(leds[i], HIGH);
        digitalWrite(leds[7 - i], HIGH);

        if (myDelay(mode, serial_port))
            return 1;

        digitalWrite(leds[i], LOW);
        digitalWrite(leds[7 - i], LOW);
    }
    return 0;
}
int laApilada(enum mode mode, int serial_port)
{
    for (int i = 0; i < 37; i++)
    {
        for (int j = 0; j < 8; j++)
            digitalWrite(leds[j], mat_laApilada[i][j]);
        if (myDelay(mode, serial_port))
            return 1;
    }
    return 0;
}
int laCarrera(enum mode mode, int serial_port)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
            digitalWrite(leds[j], mat_laCarrera[i][j]);
        if (myDelay(mode, serial_port))
            return 1;
    }
    return 0;
}

// Definidos por grupo
int alternado(enum mode mode, int serial_port)
{
    for (int i = 0; i < 8; i += 2)
        digitalWrite(leds[i], HIGH);
    for (int i = 1; i < 8; i += 2)
        digitalWrite(leds[i], LOW);

    if (myDelay(mode, serial_port))
        return 1;

    for (int i = 0; i < 8; i += 2)
        digitalWrite(leds[i], LOW);
    for (int i = 1; i < 8; i += 2)
        digitalWrite(leds[i], HIGH);

    if (myDelay(mode, serial_port))
        return 1;
    return 0;
}

int cortina1(enum mode mode, int serial_port)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
            digitalWrite(leds[j], mat_cortina1[i][j]);

        if (myDelay(mode, serial_port))
            return 1;
    }
    return 0;
}

int sombras(enum mode mode, int serial_port)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(leds[i], HIGH);
    }
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(leds[i], LOW);

        if (myDelay(mode, serial_port))
            return 1;

        digitalWrite(leds[i], HIGH);
    }

    for (int j = 7; j >= 0; j--)
    {
        digitalWrite(leds[j], LOW);

        if (myDelay(mode, serial_port))
            return 1;

        digitalWrite(leds[j], HIGH);
    }
    return 0;
}

int cortina2(enum mode mode, int serial_port)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 8; j++)
            digitalWrite(leds[j], mat_cortina2[i][j]);

        if (myDelay(mode, serial_port))
            return 1;
    }
    return 0;
}
