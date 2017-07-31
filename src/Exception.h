#ifndef Exception_H
#define Exception_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
typedef struct Exception Exception;
typedef struct Exception* ExceptionPtr;


struct Exception{               //If got more variable can add here
  char *msg;
  uint8_t errorCode;
};
Exception *createException(char *msg, uint8_t errorCode);

void freeException(Exception *e);
void dumpException(Exception *e);

#endif // Exception_H
