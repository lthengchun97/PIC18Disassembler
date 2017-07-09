#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H
#include <stdint.h>


typedef struct CheckIdentifier CheckIdentifier;
struct CheckIdentifier{
  char* (*execute)(uint8_t *code);    // a function
  int d;
  int a;
};
char* addwf (uint8_t *code/*,CheckIdentifier* ci*/);
char* addwfc(uint8_t *code);
char* andwf(uint8_t *code);
char* clrf(uint8_t *code);
char* comf(uint8_t *code);
char* cpfseq(uint8_t *code);
char* cpfsgt(uint8_t *code);
char* cpfslt(uint8_t *code);
char* decf(uint8_t *code);
char* decfsz(uint8_t *code);
char* dcfsnz(uint8_t *code);
char* incf(uint8_t *code);
char* incfsz(uint8_t *code);
char* infsnz(uint8_t *code);
char* iorwf(uint8_t *code);
char* movf(uint8_t *code);
char *disassembler (uint32_t code);
extern CheckIdentifier opcodeTable[];
#endif // _DISASSEMBLER_H
