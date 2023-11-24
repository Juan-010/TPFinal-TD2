#ifndef UTIL_H
#define UTIL_H
enum mode {LOCAL, REMOTE};
int menu(void);
int menuSecuencia(void);
int getKey(unsigned int);
int setDelay(int); //hacer en ARM
int myDelay(enum mode, int);
int login(char *);
#endif