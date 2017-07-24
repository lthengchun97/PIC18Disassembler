#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


Exception *createException(char *msg, int errorCode){
  Exception *e = malloc(sizeof(Exception));
  e -> msg = msg;
  e -> errorCode = errorCode;
  return e;
}

void freeException(Exception *e){
  free(e);
}

void dumpException(Exception *e){
  char* buffer;
  printf ("%s (err = %d)\n", e->msg, e->errorCode);
  sprintf(buffer,"invalid opcode");
  return buffer;
}
