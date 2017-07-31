#include <malloc.h>
#include <stdarg.h>
#include "Exception.h"
#include "CException.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


Exception *createException(char *msg, uint8_t errorCode)
{
  Exception *e;
  e= malloc(sizeof(Exception));
  e -> msg = msg;
  e -> errorCode = errorCode;
  Throw(e);
}

void freeException(Exception *e){
  free(e);
}

void dumpException(Exception *e){
  printf ("%s (err = %d)\n", e->msg, e->errorCode);
}
