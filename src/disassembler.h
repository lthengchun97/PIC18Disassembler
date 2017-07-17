#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t next_8;
uint8_t opcode;
typedef struct CheckIdentifier CheckIdentifier;

struct CheckIdentifier{
char* (*execute)(uint8_t *code);    // a function
};

int ad(uint8_t code);
int a(uint8_t code);
int bbb(uint8_t code);
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
char* movwf(uint8_t *code);
char* mulwf(uint8_t *code);
char* negf(uint8_t *code);
char* rlcf(uint8_t *code);
char* rlncf(uint8_t *code);
char* rrcf(uint8_t *code);
char* rrncf(uint8_t *code);
char* setf(uint8_t *code);
char* subfwb(uint8_t *code);
char* subwf(uint8_t *code);
char* subwfb(uint8_t *code);
char* swapf(uint8_t *code);
char* tstfsz(uint8_t *code);
char* xorwf(uint8_t *code);
char* bcf(uint8_t *code);
char* bsf(uint8_t *code);
char* btfsc(uint8_t *code);
char* btfss(uint8_t *code);
char* btg(uint8_t *code);
char* bc(uint8_t *code);
char* bn(uint8_t *code);
char* bnc(uint8_t *code);
char* bnn(uint8_t *code);
char* bnov(uint8_t *code);
char* bnz(uint8_t *code);
char* bov(uint8_t *code);
char* zero(uint8_t *code);
char* disassembler (uint32_t code);
extern CheckIdentifier opcodeTable[];
#endif // _DISASSEMBLER_H
