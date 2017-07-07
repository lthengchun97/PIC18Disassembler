#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H
#include <stdint.h>


typedef struct CheckIdentifier CheckIdentifier;
struct CheckIdentifier{
  int (*execute)(uint8_t *code);    // a function
  int a;
  int d;
};
int addwf (uint8_t *code,CheckIdentifier* ci);
char *disassembler (uint32_t code);
extern CheckIdentifier opcodeTable[];
#endif // _DISASSEMBLER_H
