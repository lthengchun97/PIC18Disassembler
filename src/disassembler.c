#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

CheckIdentifier opcodeTable[256] = {
  [0x24]={addwf},
  [0x25]={addwf},
  [0x26]={addwf},
  [0x27]={addwf},

  [0x20]={addwfc},
  [0x21]={addwfc},
  [0x22]={addwfc},
  [0x23]={addwfc},

  [0x14]={andwf},
  [0x15]={andwf},
  [0x16]={andwf},
  [0x17]={andwf},

  [0x6A]={clrf},
  [0x6B]={clrf},

  [0x1C]={comf},
  [0x1D]={comf},
  [0x1E]={comf},
  [0x1F]={comf},

  [0x62]={cpfseq},
  [0x63]={cpfseq},

  [0x64]={cpfsgt},
  [0x65]={cpfsgt},

  [0x60]={cpfslt},
  [0x61]={cpfslt},

  [0x04]={decf},
  [0x05]={decf},
  [0x06]={decf},
  [0x07]={decf},

  [0x2C]={decfsz},
  [0x2D]={decfsz},
  [0x2E]={decfsz},
  [0x2F]={decfsz},

  [0x4C]={dcfsnz},
  [0x4D]={dcfsnz},
  [0x4E]={dcfsnz},
  [0x4F]={dcfsnz},


  [0x28]={incf},
  [0x29]={incf},
  [0x2A]={incf},
  [0x2B]={incf},
  /*
  [0x3C]={incfsz},
  [0x3D]={incfsz},
  [0x3E]={incfsz},
  [0x3F]={incfsz},
  [0x48]={infsnz},
  [0x49]={infsnz},
  [0x4A]={infsnz},
  [0x4B]={infsnz},
  [0x10]={iorwf},
  [0x11]={iorwf},
  [0x12]={iorwf},
  [0x13]={iorwf},
  [0x50]={movf},
  [0x51]={movf},
  [0x52]={movf},
  [0x53]={movf},      // STOP AT movf
*/
};


  char* disassembler (uint32_t code)
{
  opcode = code >> 8;
  next_8 = code & 0x00ff;
  opcodeTable[opcode].execute(opcode);
}

char* addwf (uint8_t *code/*,CheckIdentifier* ci*/)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("addwf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"addwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("addwf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"addwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("addwf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"addwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("addwf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"addwf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}



char* addwfc(uint8_t *code){
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("addwfc  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"addwfc  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("addwfc  0x%2x WREG,BANEKD",next_8);
    sprintf(buffer,"addwfc  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("addwfc  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"addwfc  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("addwfc  0x%2x f,BANKED",next_8);
    sprintf(buffer,"addwfc  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* andwf(uint8_t *code){
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("andwf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"andwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("andwf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"andwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("andwf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"andwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("andwf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"andwf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* clrf(uint8_t *code){
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 10)
  {
    printf("clrf  0x%2x ACCESS",next_8);
    sprintf(buffer,"clrf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("clrf  0x%2x BANKED",next_8);
    sprintf(buffer,"clrf  0x%2x BANKED",next_8);
  }

  return buffer;
}

char* comf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("comf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"comf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("comf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"comf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("comf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"comf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("comf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"comf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* cpfseq(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 10)
  {
    printf("cpfseq  0x%2x ACCESS",next_8);
    sprintf(buffer,"cpfseq  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("cpfseq  0x%2x BANKED",next_8);
    sprintf(buffer,"cpfseq  0x%2x BANKED",next_8);
  }

  return buffer;
}

char* cpfsgt(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("cpfsgt  0x%2x ACCESS",next_8);
    sprintf(buffer,"cpfsgt  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("cpfsgt  0x%2x BANKED",next_8);
    sprintf(buffer,"cpfsgt  0x%2x BANKED",next_8);
  }
  return buffer;
}

char* cpfslt(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("cpfslt  0x%2x ACCESS",next_8);
    sprintf(buffer,"cpfslt  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("cpfslt  0x%2x BANKED",next_8);
    sprintf(buffer,"cpfslt  0x%2x BANKED",next_8);
  }
  return buffer;
}

char* decf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("decf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"decf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("decf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"decf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("decf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"decf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("decf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"decf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* decfsz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("decfsz  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"decfsz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("decfsz  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"decfsz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("decfsz  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"decfsz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("decfsz  0x%2x f,BANKED",next_8);
    sprintf(buffer,"decfsz  0x%2x f,BANKED",next_8);
  }
  return buffer;
}


char* dcfsnz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("dcfsnz  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"dcfsnz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("dcfsnz  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"dcfsnz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("dcfsnz  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"dcfsnz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("dcfsnz  0x%2x f,BANKED",next_8);
    sprintf(buffer,"dcfsnz  0x%2x f,BANKED",next_8);
  }
  return buffer;
}


char* incf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("incf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"incf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("incf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"incf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("incf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"incf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("incf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"incf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}
/*
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
*/
int ad(uint8_t code)
{
  uint8_t adcode = code & 0x03;
  if(adcode == 0x00)
  {
    return 00;
  }
  else if( adcode == 0x01)
  {
    return 01;
  }
  else if( adcode == 0x02)
  {
    return 10;
  }
  else
  {
    return 11;
  }
}
