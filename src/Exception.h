#ifndef Exception_H
#define Exception_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Exception Exception;
typedef struct Exception* ExceptionPtr;


struct Exception{               //If got more variable can add here
  char *msg;
  int errorCode;
};
Exception *createException(char *msg,int errorCode);

void freeException(Exception *e);
void dumpException(Exception *e);

#endif // Exception_H
