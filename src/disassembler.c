#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

CheckIdentifier opcodeTable[256] = {
  [0x24]={addwf,0,0},
  [0x25]={addwf,0,1},
  [0x26]={addwf,1,0},
  [0x27]={addwf,1,1},
  [0x20]={addwfc,0,0},
  [0x21]={addwfc,0,1},
  [0x22]={addwfc,1,0},
  [0x23]={addwfc,1,1},
  [0x14]={andwf,0,0},
  [0x15]={andwf,0,1},
  [0x16]={andwf,1,0},
  [0x17]={andwf,1,1},
  [0x6A]={clrf,0,0},
  [0x6B]={clrf,0,1},
  [0x1C]={comf,0,0},
  [0x1D]={comf,0,1},
  [0x1E]={comf,1,0},
  [0x1F]={comf,1,1},
  [0x62]={cpfseq,0,0},
  [0x63]={cpfseq,0,1},
  [0x64]={cpfsgt,0,0},
  [0x65]={cpfsgt,0,1},
  [0x60]={cpfslt,0,0},
  [0x61]={cpfslt,0,1},
  [0x04]={decf,0,0},
  [0x05]={decf,0,1},
  [0x06]={decf,1,0},
  [0x07]={decf,1,1},
  [0x2C]={decfsz,0,0},
  [0x2D]={decfsz,0,1},
  [0x2E]={decfsz,1,0},
  [0x2F]={decfsz,1,1},
  [0x4C]={dcfsnz,0,0},
  [0x4D]={dcfsnz,0,1},
  [0x4E]={dcfsnz,1,0},
  [0x4F]={dcfsnz,1,1},
  [0x28]={incf,0,0},
  [0x29]={incf,0,1},
  [0x2A]={incf,1,0},
  [0x2B]={incf,1,1},
  [0x3C]={incfsz,0,0},
  [0x3D]={incfsz,0,1},
  [0x3E]={incfsz,1,0},
  [0x3F]={incfsz,1,1},
  [0x48]={infsnz,0,0},
  [0x49]={infsnz,0,1},
  [0x4A]={infsnz,1,0},
  [0x4B]={infsnz,1,1},
  [0x10]={iorwf,0,0},
  [0x11]={iorwf,0,1},
  [0x12]={iorwf,1,0},
  [0x13]={iorwf,1,1},
  [0x50]={movf,0,0},
  [0x51]={movf,0,1},
  [0x52]={movf,1,0},
  [0x53]={movf,1,1},      // STOP AT movf



};


  char * disassembler (uint32_t code)
{
  uint8_t opcode = code >> 8;
  uint32_t ci = code;
  char *buffer;
  buffer = malloc(1028);
  uint8_t next_8 = code & 0x00ff;
  printf("addwf  0x%2x WREG,ACCESS",next_8);
  sprintf(buffer,"addwf  0x%2x WREG,ACCESS",next_8);
  return buffer;
}

char* addwf (uint8_t *code/*,CheckIdentifier* ci*/){
  char *buffer;
  buffer = malloc(1028);
  uint8_t next_8 = *code & 0x00ff;
  sprintf(buffer,"addwf  0x%2x WREG,ACCESS",next_8);

/*
  if(a==0 && d==0)
    printf("addwf %d WREG,ACCESS",next_8);
  if(a==0 && d==1)
    printf("addwf %d WREG,f",next_8);
  if(a==1 && d==0)
    printf("addwf %d BANKED,ACCESS",next_8);
  else
    printf("addwf %d BANKED,f",next_8);
*/
  return buffer;
};

char* addwfc(uint8_t *code){
  return NULL;
};

char* andwf(uint8_t *code){
  return NULL;
};
char* clrf(uint8_t *code){
  return NULL;
};
char* comf(uint8_t *code){
  return NULL;
};
char* cpfseq(uint8_t *code){
  return NULL;
};
char* cpfsgt(uint8_t *code){
  return NULL;
};
char* cpfslt(uint8_t *code){
  return NULL;
};
char* decf(uint8_t *code){
  return NULL;
};
char* decfsz(uint8_t *code){
  return NULL;
};
char* dcfsnz(uint8_t *code){
  return NULL;
};
char* incf(uint8_t *code){
  return NULL;
};
char* incfsz(uint8_t *code){
  return NULL;
};
char* infsnz(uint8_t *code){
  return NULL;
};
char* iorwf(uint8_t *code){
  return NULL;
};
char* movf(uint8_t *code){
  return NULL;
};
