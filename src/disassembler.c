#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

CheckIdentifier opcodeTable[256] = {
  [0x00]={zero},
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
  [0x6E]={movwf},
  [0x6F]={movwf},
  [0x02]={mulwf},
  [0x03]={mulwf},
  [0x6C]={negf},
  [0x6D]={negf},
  [0x34]={rlcf},
  [0x35]={rlcf},
  [0x36]={rlcf},
  [0x37]={rlcf},
  [0x44]={rlncf},
  [0x45]={rlncf},
  [0x46]={rlncf},
  [0x47]={rlncf},
  [0x30]={rrcf},
  [0x31]={rrcf},
  [0x32]={rrcf},
  [0x33]={rrcf},
  [0x40]={rrncf},
  [0x41]={rrncf},
  [0x42]={rrncf},
  [0x43]={rrncf},
  [0x68]={setf},
  [0x69]={setf},
  [0x54]={subfwb},
  [0x55]={subfwb},
  [0x56]={subfwb},
  [0x57]={subfwb},
  [0x5C]={subwf},
  [0x5D]={subwf},
  [0x5E]={subwf},
  [0x5F]={subwf},
  [0x58]={subwfb},
  [0x59]={subwfb},
  [0x5A]={subwfb},
  [0x5B]={subwfb},
  [0x38]={swapf},
  [0x39]={swapf},
  [0x3A]={swapf},
  [0x3B]={swapf},
  [0x67]={tstfsz},
  [0x68]={tstfsz},
  [0x18]={xorwf},
  [0x19]={xorwf},
  [0x1A]={xorwf},
  [0x1B]={xorwf},
  [0x90]={bcf},
  [0x91]={bcf},
  [0x92]={bcf},
  [0x93]={bcf},
  [0x94]={bcf},
  [0x95]={bcf},
  [0x96]={bcf},
  [0x97]={bcf},
  [0x98]={bcf},
  [0x99]={bcf},
  [0x9A]={bcf},
  [0x9B]={bcf},
  [0x9C]={bcf},
  [0x9D]={bcf},
  [0x9E]={bcf},
  [0x9F]={bcf},

  [0x80]={bsf},
  [0x81]={bsf},
  [0x82]={bsf},
  [0x83]={bsf},
  [0x84]={bsf},
  [0x85]={bsf},
  [0x86]={bsf},
  [0x87]={bsf},
  [0x88]={bsf},
  [0x89]={bsf},
  [0x8A]={bsf},
  [0x8B]={bsf},
  [0x8C]={bsf},
  [0x8D]={bsf},
  [0x8E]={bsf},
  [0x8F]={bsf},

  [0xB0]={btfsc},
  [0xB1]={btfsc},
  [0xB2]={btfsc},
  [0xB3]={btfsc},
  [0xB4]={btfsc},
  [0xB5]={btfsc},
  [0xB6]={btfsc},
  [0xB7]={btfsc},
  [0xB8]={btfsc},
  [0xB9]={btfsc},
  [0xBA]={btfsc},
  [0xBB]={btfsc},
  [0xBC]={btfsc},
  [0xBD]={btfsc},
  [0xBE]={btfsc},
  [0xBF]={btfsc},

  [0xA0]={btfss},
  [0xA1]={btfss},
  [0xA2]={btfss},
  [0xA3]={btfss},
  [0xA4]={btfss},
  [0xA5]={btfss},
  [0xA6]={btfss},
  [0xA7]={btfss},
  [0xA8]={btfss},
  [0xA9]={btfss},
  [0xAA]={btfss},
  [0xAB]={btfss},
  [0xAC]={btfss},
  [0xAD]={btfss},
  [0xAE]={btfss},
  [0xAF]={btfss},

  [0x70]={btg},
  [0x71]={btg},
  [0x72]={btg},
  [0x73]={btg},
  [0x74]={btg},
  [0x75]={btg},
  [0x76]={btg},
  [0x77]={btg},
  [0x78]={btg},
  [0x79]={btg},
  [0x7A]={btg},
  [0x7B]={btg},
  [0x7C]={btg},
  [0x7D]={btg},
  [0x7E]={btg},
  [0x7F]={btg},

  [0xE1]={bnz},
  [0xE2]={bc},
  [0xE3]={bnc},
  [0xE4]={bov},
  [0xE5]={bnov},
  [0xE6]={bn},
  [0xE7]={bnn},

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

char* incfsz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("incfsz  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"incfsz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("incfsz  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"incfsz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("incfsz  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"incfsz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("incfsz  0x%2x f,BANKED",next_8);
    sprintf(buffer,"incfsz  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* infsnz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("infsnz  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"infsnz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("infsnz  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"infsnz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("infsnz  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"infsnz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("infsnz  0x%2x f,BANKED",next_8);
    sprintf(buffer,"infsnz  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* iorwf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("iorfwf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"iorwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("iorwf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"iorwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("iorwf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"iorwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("iorwf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"iorwf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* movf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("movf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"movf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("movf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"movf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("movf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"movf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("movf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"movf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* movwf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 10)
  {
    printf("movwf  0x%2x ACCESS",next_8);
    sprintf(buffer,"movwf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("movwf  0x%2x BANKED",next_8);
    sprintf(buffer,"movwf  0x%2x BANKED",next_8);
  }

  return buffer;
}

char* mulwf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 10)
  {
    printf("mulwf  0x%2x ACCESS",next_8);
    sprintf(buffer,"mulwf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("mulwf  0x%2x BANKED",next_8);
    sprintf(buffer,"mulwf  0x%2x BANKED",next_8);
  }

  return buffer;
}

char* negf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("negf  0x%2x ACCESS",next_8);
    sprintf(buffer,"negf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("negf  0x%2x BANKED",next_8);
    sprintf(buffer,"negf  0x%2x BANKED",next_8);
  }
  return buffer;
}

char* rlcf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("rlcf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"rlcf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rlcf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"rlcf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rlcf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"rlcf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rlcf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"rlcf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* rlncf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("rlncf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"rlncf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rlncf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"rlncf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rlncf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"rlncf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rlncf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"rlncf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* rrcf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("rrcf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"rrcf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rrcf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"rrcf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rrcf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"rrcf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rrcf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"rrcf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* rrncf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("rrncf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"rrncf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rrncf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"rrncf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rrncf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"rrncf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rrncf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"rrncf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* setf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("setf  0x%2x ACCESS",next_8);
    sprintf(buffer,"setf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("setf  0x%2x BANKED",next_8);
    sprintf(buffer,"setf  0x%2x BANKED",next_8);
  }
  return buffer;
}

char* subfwb(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("subfwb  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"subfwb  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("subfwb  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"subfwb  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("subfwb  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"subfwb  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("subfwb  0x%2x f,BANKED",next_8);
    sprintf(buffer,"subfwb  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* subwf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("subwf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"subwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("subwf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"subwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("subwf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"subwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("subwf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"subwf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* subwfb(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("subwfb  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"subwfb  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("subwfb  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"subwfb  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("subwfb  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"subwfb  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("subwfb  0x%2x f,BANKED",next_8);
    sprintf(buffer,"subwfb  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* swapf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("swapf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"swapf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("swapf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"swapf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("swapf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"swapf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("swapf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"swapf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* tstfsz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 10)
  {
    printf("tstfsz  0x%2x ACCESS",next_8);
    sprintf(buffer,"tstfsz  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("tstfsz  0x%2x BANKED",next_8);
    sprintf(buffer,"tstfsz  0x%2x BANKED",next_8);
  }

  return buffer;
}

char* xorwf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("xorwf  0x%2x WREG,ACCESS",next_8);
    sprintf(buffer,"xorwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("xorwf  0x%2x WREG,BANKED",next_8);
    sprintf(buffer,"xorwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("xorwf  0x%2x f,ACCESS",next_8);
    sprintf(buffer,"xorwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("xorwf  0x%2x f,BANKED",next_8);
    sprintf(buffer,"xorwf  0x%2x f,BANKED",next_8);
  }
  return buffer;
}

char* bcf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = a(opcode);
  int getB = bbb(opcode);

  if(differentiate == 0)
  {
    printf("bcf  %#4x %d,ACCESS",next_8,getB);
    sprintf(buffer,"bcf  %#4x %d,ACCESS",next_8,getB);
  }
  else
  {
    printf("bcf  %#4x %d,BANKED",next_8,getB);
    sprintf(buffer,"bcf  %#4x %d,BANKED",next_8,getB);
  }
  return buffer;
}

char* bsf(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = a(opcode);
  int getB = bbb(opcode);

  if(differentiate == 0)
  {
    printf("bsf  %#4x %d,ACCESS",next_8,getB);
    sprintf(buffer,"bsf  %#4x %d,ACCESS",next_8,getB);
  }
  else
  {
    printf("bsf  %#4x %d,BANKED",next_8,getB);
    sprintf(buffer,"bsf  %#4x %d,BANKED",next_8,getB);
  }
  return buffer;
}

char* btfsc(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = a(opcode);
  int getB = bbb(opcode);

  if(differentiate == 0)
  {
    printf("btfsc  %#4x %d,ACCESS",next_8,getB);
    sprintf(buffer,"bstfsc  %#4x %d,ACCESS",next_8,getB);
  }
  else
  {
    printf("btfsc  %#4x %d,BANKED",next_8,getB);
    sprintf(buffer,"btfsc  %#4x %d,BANKED",next_8,getB);
  }
  return buffer;
}


char* btfss(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = a(opcode);
  int getB = bbb(opcode);

  if(differentiate == 0)
  {
    printf("btfss  %#4x %d,ACCESS",next_8,getB);
    sprintf(buffer,"btfss  %#4x %d,ACCESS",next_8,getB);
  }
  else
  {
    printf("btfss  %#4x %d,BANKED",next_8,getB);
    sprintf(buffer,"btfss  %#4x %d,BANKED",next_8,getB);
  }
  return buffer;
}

char* btg(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = a(opcode);
  int getB = bbb(opcode);

  if(differentiate == 0)
  {
    printf("btg  %#4x %d,ACCESS",next_8,getB);
    sprintf(buffer,"btg  %#4x %d,ACCESS",next_8,getB);
  }
  else
  {
    printf("btg  %#4x %d,BANKED",next_8,getB);
    sprintf(buffer,"btg  %#4x %d,BANKED",next_8,getB);
  }
  return buffer;
}

char* bc(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bc %#4x",next_8);
  sprintf(buffer,"bc %#4x",next_8);
  return buffer;
}

char* bn(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bn %#4x",next_8);
  sprintf(buffer,"bn %#4x",next_8);
  return buffer;
}

char* bnc(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bnc %#4x",next_8);
  sprintf(buffer,"bnc %#4x",next_8);
  return buffer;
}

char* bnn(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bnn %#4x",next_8);
  sprintf(buffer,"bnn %#4x",next_8);
  return buffer;
}

char* bnov(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bnov %#4x",next_8);
  sprintf(buffer,"bnov %#4x",next_8);
  return buffer;
}

char* bnz(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bnov %#4x",next_8);
  sprintf(buffer,"bnov %#4x",next_8);
  return buffer;
}

char* bov(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("bov %#4x",next_8);
  sprintf(buffer,"bov %#4x",next_8);
  return buffer;
}

char* zero(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  if(next_8 == 0x08)
  {
    printf("TBLRD*");
    sprintf(buffer,"TBLRD*");
  }
  else if(next_8 == 0x09)
  {
    printf("TBLRD*+");
    sprintf(buffer,"TBLRD*+");
  }
  else if(next_8 == 0x0A)
  {
    printf("TBLRD*-");
    sprintf(buffer,"TBLRD*-");
  }
  else if(next_8 == 0x0B)
  {
    printf("TBLRD+*");
    sprintf(buffer,"TBLRD+*");
  }
  else if(next_8 == 0x0C)
  {
    printf("TBLWT*");
    sprintf(buffer,"TBLWT*");
  }
  else if(next_8 == 0x0D)
  {
    printf("TBLWT*+");
    sprintf(buffer,"TBLWT*+");
  }
  else if(next_8 == 0x0E)
  {
    printf("TBLWT*-");
    sprintf(buffer,"TBLWT*-");
  }
  else if(next_8 == 0x0F)
  {
    printf("TBLWT+*");
    sprintf(buffer,"TBLWT+*");
  }
  else if(next_8 == 0x04)
  {
    printf("clrwdt");
    sprintf(buffer,"clrwdt");
  }
  else if(next_8 == 0x07)
  {
    printf("daw");
    sprintf(buffer,"daw");
  }
  else if(next_8 == 0x00)
  {
    printf("nop");
    sprintf(buffer,"nop");
  }
  else if(next_8 == 0x06)
  {
    printf("pop");
    sprintf(buffer,"pop");
  }
  else if(next_8 == 0x05)
  {
    printf("push");
    sprintf(buffer,"push");
  }
  else if(next_8 == 0xFF)
  {
    printf("reset");
    sprintf(buffer,"reset");
  }
  else if(next_8 == 0x11 || next_8 == 0x10)
  {
    printf("retfie");
    sprintf(buffer,"retfie");
  }
  else if(next_8 == 0x12 || next_8 == 0x13)
  {
    printf("return");
    sprintf(buffer,"return");
  }
  else if(next_8 == 0x03)
  {
    printf("sleep");
    sprintf(buffer,"sleep");
  }
  else
  {
    printf("error , no such opcode to display");
    sprintf(buffer,"error , no such opcode to display");
  }
  return buffer;
}

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

int a(uint8_t code)
{
  uint8_t adcode = code & 0x01;
  if(adcode == 0x00)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int bbb(uint8_t code)
{
  uint8_t adcode = code & 0x0E;
  if(adcode == 0x00)
  {
    return 0;
  }
  else if( adcode == 0x02)
  {
    return 1;
  }
  else if( adcode == 0x04)
  {
    return 2;
  }
  else if( adcode == 0x06)
  {
    return 3;
  }
  else if( adcode == 0x08)
  {
    return 4;
  }
  else if(adcode == 0x0A)
  {
    return 5;
  }
  else if(adcode == 0x0C)
  {
    return 6;
  }
  else if(adcode == 0x0E)
  {
    return 7;
  }
}
