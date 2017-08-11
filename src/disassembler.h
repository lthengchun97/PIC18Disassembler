#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

uint8_t next_8;
uint8_t opcode;
uint8_t thirdcode;
uint8_t forthcode;
uint8_t upperByte;
uint8_t next_16;
uint8_t next_32;

typedef struct CheckIdentifier CheckIdentifier;

struct CheckIdentifier{
  char* (*execute)(uint8_t *code);    // a function
  int size;
};
char* printError(uint8_t *code);
int ad(uint8_t code);
int a(uint8_t code);
int bbb(uint8_t code);
char* addwf (uint8_t *code);
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
char* addlw(uint8_t *code);
char* andlw(uint8_t *code);
char* iorlw(uint8_t *code);
char* movlw(uint8_t *code);
char* mullw(uint8_t *code);
char* retlw(uint8_t *code);
char* sublw(uint8_t *code);
char* xorlw(uint8_t *code);
char* movlb(uint8_t *code);
char* nop1(uint8_t *code);
char* call(uint8_t *code);
char* goto1(uint8_t *code);
char* lfsr(uint8_t *code);
char* rcall(uint8_t *code);
char* movff(uint8_t *code);
char* disassemble (uint8_t **codePtrPtr);
char* disassembleNBytes(uint8_t **codePtrPtr, int nBytes);
char* codeAlign(char* displayOut, ...);
extern CheckIdentifier opcodeTable[];
#endif // _DISASSEMBLER_H
