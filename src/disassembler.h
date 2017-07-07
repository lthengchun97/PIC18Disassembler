#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H
#include <stdint.h>


typedef struct checkidentifier checkidentifier;
struct checkidentifier{
  int (*execute)(uint8_t *code);    // a function
  int a;
  int d;
};
int addwf (uint8_t *code);
char *disassembler (uint32_t code);
extern checkidentifier opcodeTable[];
#endif // _DISASSEMBLER_H
