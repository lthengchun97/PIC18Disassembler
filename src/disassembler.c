#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "CException.h"
#include "Exception.h"
#include <stdarg.h>

#define KB 1024

int codePtr[8*KB];
int memory[20*KB];

CheckIdentifier opcodeTable[256] = {

  [0x00]={zero, 2},
  [0x24]={addwf,2},
  [0x25]={addwf,2},
  [0x26]={addwf,2},
  [0x27]={addwf,2},
  [0x20]={addwfc,2},
  [0x21]={addwfc,2},
  [0x22]={addwfc,2},
  [0x23]={addwfc,2},
  [0x14]={andwf,2},
  [0x16]={andwf,2},
  [0x15]={andwf,2},
  [0x17]={andwf,2},
  [0x6B]={clrf,2},
  [0x6A]={clrf,2},
  [0x1C]={comf,2},
  [0x1D]={comf,2},
  [0x1E]={comf,2},
  [0x1F]={comf,2},
  [0x62]={cpfseq,2},
  [0x63]={cpfseq,2},
  [0x64]={cpfsgt,2},
  [0x65]={cpfsgt,2},
  [0x60]={cpfslt,2},
  [0x61]={cpfslt,2},
  [0x04]={decf,2},
  [0x05]={decf,2},
  [0x06]={decf,2},
  [0x07]={decf,2},
  [0x2C]={decfsz,2},
  [0x2D]={decfsz,2},
  [0x2E]={decfsz,2},
  [0x2F]={decfsz,2},
  [0x4C]={dcfsnz,2},
  [0x4D]={dcfsnz,2},
  [0x4E]={dcfsnz,2},
  [0x4F]={dcfsnz,2},
  [0x28]={incf,2},
  [0x29]={incf,2},
  [0x2A]={incf,2},
  [0x2B]={incf,2},
  [0x3C]={incfsz,2},
  [0x3D]={incfsz,2},
  [0x3E]={incfsz,2},
  [0x3F]={incfsz,2},
  [0x48]={infsnz,2},
  [0x49]={infsnz,2},
  [0x4A]={infsnz,2},
  [0x4B]={infsnz,2},
  [0x10]={iorwf,2},
  [0x11]={iorwf,2},
  [0x12]={iorwf,2},
  [0x13]={iorwf,2},
  [0x50]={movf,2},
  [0x51]={movf,2},
  [0x52]={movf,2},
  [0x53]={movf,2},
  [0x6E]={movwf,2},
  [0x6F]={movwf,2},
  [0x02]={mulwf,2},
  [0x03]={mulwf,2},
  [0x6C]={negf,2},
  [0x6D]={negf,2},
  [0x34]={rlcf,2},
  [0x35]={rlcf,2},
  [0x36]={rlcf,2},
  [0x37]={rlcf,2},
  [0x44]={rlncf,2},
  [0x45]={rlncf,2},
  [0x46]={rlncf,2},
  [0x47]={rlncf,2},
  [0x30]={rrcf,2},
  [0x31]={rrcf,2},
  [0x32]={rrcf,2},
  [0x33]={rrcf,2},
  [0x40]={rrncf,2},
  [0x41]={rrncf,2},
  [0x42]={rrncf,2},
  [0x43]={rrncf,2},
  [0x68]={setf,2},
  [0x69]={setf,2},
  [0x54]={subfwb,2},
  [0x55]={subfwb,2},
  [0x56]={subfwb,2},
  [0x57]={subfwb,2},
  [0x5C]={subwf,2},
  [0x5D]={subwf,2},
  [0x5E]={subwf,2},
  [0x5F]={subwf,2},
  [0x58]={subwfb,2},
  [0x59]={subwfb,2},
  [0x5A]={subwfb,2},
  [0x5B]={subwfb,2},
  [0x38]={swapf,2},
  [0x39]={swapf,2},
  [0x3A]={swapf,2},
  [0x3B]={swapf,2},
  [0x67]={tstfsz,2},
  [0x68]={tstfsz,2},
  [0x18]={xorwf,2},
  [0x19]={xorwf,2},
  [0x1A]={xorwf,2},
  [0x1B]={xorwf,2},
  [0x90]={bcf,2},
  [0x91]={bcf,2},
  [0x92]={bcf,2},
  [0x93]={bcf,2},
  [0x94]={bcf,2},
  [0x95]={bcf,2},
  [0x96]={bcf,2},
  [0x97]={bcf,2},
  [0x98]={bcf,2},
  [0x99]={bcf,2},
  [0x9A]={bcf,2},
  [0x9B]={bcf,2},
  [0x9C]={bcf,2},
  [0x9D]={bcf,2},
  [0x9E]={bcf,2},
  [0x9F]={bcf,2},
  [0x80]={bsf,2},
  [0x81]={bsf,2},
  [0x82]={bsf,2},
  [0x83]={bsf,2},
  [0x84]={bsf,2},
  [0x85]={bsf,2},
  [0x86]={bsf,2},
  [0x87]={bsf,2},
  [0x88]={bsf,2},
  [0x89]={bsf,2},
  [0x8A]={bsf,2},
  [0x8B]={bsf,2},
  [0x8C]={bsf,2},
  [0x8D]={bsf,2},
  [0x8E]={bsf,2},
  [0x8F]={bsf,2},
  [0xB0]={btfsc,2},
  [0xB1]={btfsc,2},
  [0xB2]={btfsc,2},
  [0xB3]={btfsc,2},
  [0xB4]={btfsc,2},
  [0xB5]={btfsc,2},
  [0xB6]={btfsc,2},
  [0xB7]={btfsc,2},
  [0xB8]={btfsc,2},
  [0xB9]={btfsc,2},
  [0xBA]={btfsc,2},
  [0xBB]={btfsc,2},
  [0xBC]={btfsc,2},
  [0xBD]={btfsc,2},
  [0xBE]={btfsc,2},
  [0xBF]={btfsc,2},
  [0xA0]={btfss,2},
  [0xA1]={btfss,2},
  [0xA2]={btfss,2},
  [0xA3]={btfss,2},
  [0xA4]={btfss,2},
  [0xA5]={btfss,2},
  [0xA6]={btfss,2},
  [0xA7]={btfss,2},
  [0xA8]={btfss,2},
  [0xA9]={btfss,2},
  [0xAA]={btfss,2},
  [0xAB]={btfss,2},
  [0xAC]={btfss,2},
  [0xAD]={btfss,2},
  [0xAE]={btfss,2},
  [0xAF]={btfss,2},
  [0x70]={btg,2},
  [0x71]={btg,2},
  [0x72]={btg,2},
  [0x73]={btg,2},
  [0x74]={btg,2},
  [0x75]={btg,2},
  [0x76]={btg,2},
  [0x77]={btg,2},
  [0x78]={btg,2},
  [0x79]={btg,2},
  [0x7A]={btg,2},
  [0x7B]={btg,2},
  [0x7C]={btg,2},
  [0x7D]={btg,2},
  [0x7E]={btg,2},
  [0x7F]={btg,2},
  [0xE1]={bnz,2},
  [0xE2]={bc,2},
  [0xE3]={bnc,2},
  [0xE4]={bov,2},
  [0xE5]={bnov,2},
  [0xE6]={bn,2},
  [0xE7]={bnn,2},
  [0x08]={sublw,2},
  [0x09]={iorlw,2},
  [0x0A]={xorlw,2},
  [0x0B]={andlw,2},
  [0x0C]={retlw,2},
  [0x0D]={mullw,2},
  [0x0E]={movlw,2},
  [0x0F]={addlw,2},
  [0x01]={movlb,2},
  [0xF0]={nop1,2},
  [0xF1]={nop1,2},
  [0xF2]={nop1,2},
  [0xF3]={nop1,2},
  [0xF4]={nop1,2},
  [0xF5]={nop1,2},
  [0xF6]={nop1,2},
  [0xF7]={nop1,2},
  [0xF8]={nop1,2},
  [0xF9]={nop1,2},
  [0xFA]={nop1,2},
  [0xFC]={nop1,2},
  [0xFD]={nop1,2},
  [0xFE]={nop1,2},
  [0xFF]={nop1,2},
  [0xEC]={call,4},
  [0xED]={call,4},
  [0xEF]={goto1,4},
  [0xEE]={lfsr,4},
  [0xD8]={rcall,2},
  [0xD9]={rcall,2},
  [0xDA]={rcall,2},
  [0xDB]={rcall,2},
  [0xDC]={rcall,2},
  [0xDD]={rcall,2},
  [0xDE]={rcall,2},
  [0xDF]={rcall,2},
  [0xC0]={movff,4},
  [0xC1]={movff,4},
  [0xC2]={movff,4},
  [0xC3]={movff,4},
  [0xC4]={movff,4},
  [0xC5]={movff,4},
  [0xC6]={movff,4},
  [0xC7]={movff,4},
  [0xC8]={movff,4},
  [0xC9]={movff,4},
  [0xCA]={movff,4},
  [0xCB]={movff,4},
  [0xCC]={movff,4},
  [0xCD]={movff,4},
  [0xCE]={movff,4},
  [0xCF]={movff,4},

};

/**
 * Disassemble many instruction only
 */

char* disassembleNBytes(uint8_t **codePtrPtr, int nBytes)
{
  uint8_t startCodePtr = codePtr[0];
  char *str;
  //str=malloc(1028);
  int i;
   for( i = 0 ; i < nBytes ; i++)
   {
    str = disassembler(codePtrPtr);
    *codePtrPtr += opcodeTable[upperByte].size;
    //sprintf(str,disassembler(codePtrPtr));
   }
   return str;
}



/**
 * Disassemble 1 instruction only
 */
char* disassembler(uint8_t **codePtrPtr)
{
  uint8_t *codePtr = *codePtrPtr;
  // codePtr use for checking the bytes
  if(opcodeTable[upperByte].size==4)
  {
  upperByte =codePtr[0];     // 1st byte
  next_8 =codePtr[1];        // 2nd byte
  next_16 =codePtr[2];       // 3rd byte
  next_32=codePtr[3];         // 4th byte
  }
  else
  {
    upperByte =codePtr[0];     // 1st byte
    next_8 =codePtr[1];        // 2nd byte
  }

  if(opcodeTable[upperByte].execute == 0)
  {
    char* buffer = malloc(1028);
    printf("Error!");
    // Invalid instruction. Cannot recognize 'xxxxx'.
    sprintf(buffer,"This opcode 0x%2x cannot be used",upperByte);
    return buffer;
    //Throw(createException("invalid opcode %2x",upperByte));
  }
  else
  {
    //printf("size of the instruction = %d\n",opcodeTable[upperByte].size );
    return opcodeTable[upperByte].execute(codePtr);
    *codePtrPtr += opcodeTable[upperByte].size;
  }
}

char* printError(uint8_t *code){
 CEXCEPTION_T ex;
 Try{
  }
  Catch(ex){
    dumpException(ex);
  }
}

char *movff(uint8_t *code)
{
  char *buffer;
  buffer = malloc(1028);
  upperByte = upperByte & 0x0F;
  uint8_t movff_test = (next_16 >> 4) & 0x0F;
  next_16 = next_16 & 0x0F;
  if(movff_test == 0xF)
  {
    sprintf(buffer,"movff %#4x%2x,%#4x%2x",upperByte,next_8,next_16,next_32);
    printf("%s \n",buffer);
  }
  else
  {
    sprintf(buffer,"invalid");
  }
  return buffer;
}

char *rcall(uint8_t *code)
{
  char *buffer;
  buffer = malloc(1028);
  upperByte = upperByte &0x07;
  sprintf(buffer,"rcall %#4x%2x",upperByte,next_8);
  printf("%s \n",buffer);
  return buffer;
}


char* call(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  next_16 = next_16 & 0xF0;
  if(next_16 == 0xF0)
    {
      sprintf(buffer,"call 0x%2x\nnop 0x%2x",next_8,next_32);
      printf("%s\n",buffer);
    }
  else
  {
    sprintf(buffer,"invalid");
  }
  return buffer;
}

char* goto1(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  next_16 = next_16 & 0xF0;
  if(next_16 == 0xF0)
    {
      sprintf(buffer,"goto 0x%2x\nnop 0x%2x",next_8,next_32);
      printf("%s\n",buffer);
    }
  else
  {
    sprintf(buffer,"invalid");
  }
  return buffer;
}

char* lfsr(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  next_16 = next_16 & 0xFF;
  //next_8 = next_8 >> 4;
  //next_8 = next_8 & 0x03;
  if(next_16 == 0xF0)
    {
      sprintf(buffer,"lfsr 0x%2x, 0x%2x",next_8,next_32);
      printf("%s\n",buffer);
    }
  else
  {
    sprintf(buffer,"invalid");
  }
  return buffer;
}

char* addwf (uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  int differentiate = ad(opcode);

  if(differentiate == 00)
  {
    printf("addwf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"addwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("addwf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"addwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("addwf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"addwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("addwf  0x%2x f,BANKED\n",next_8);
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
    printf("addwfc  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"addwfc  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("addwfc  0x%2x WREG,BANEKD\n",next_8);
    sprintf(buffer,"addwfc  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("addwfc  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"addwfc  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("addwfc  0x%2x f,BANKED\n",next_8);
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
    printf("andwf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"andwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("andwf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"andwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("andwf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"andwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("andwf  0x%2x f,BANKED\n",next_8);
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
    printf("clrf  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"clrf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("clrf  0x%2x BANKED\n",next_8);
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
    printf("comf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"comf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("comf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"comf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("comf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"comf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("comf  0x%2x f,BANKED\n",next_8);
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
    printf("cpfseq  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"cpfseq  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("cpfseq  0x%2x BANKED\n",next_8);
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
    printf("cpfsgt  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"cpfsgt  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("cpfsgt  0x%2x BANKED\n",next_8);
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
    printf("cpfslt  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"cpfslt  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("cpfslt  0x%2x BANKED\n",next_8);
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
    printf("decf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"decf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("decf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"decf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("decf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"decf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("decf  0x%2x f,BANKED\n",next_8);
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
    printf("decfsz  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"decfsz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("decfsz  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"decfsz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("decfsz  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"decfsz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("decfsz  0x%2x f,BANKED\n",next_8);
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
    printf("dcfsnz  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"dcfsnz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("dcfsnz  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"dcfsnz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("dcfsnz  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"dcfsnz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("dcfsnz  0x%2x f,BANKED\n",next_8);
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
    printf("incf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"incf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("incf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"incf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("incf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"incf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("incf  0x%2x f,BANKED\n",next_8);
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
    printf("incfsz  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"incfsz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("incfsz  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"incfsz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("incfsz  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"incfsz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("incfsz  0x%2x f,BANKED\n",next_8);
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
    printf("infsnz  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"infsnz  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("infsnz  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"infsnz  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("infsnz  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"infsnz  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("infsnz  0x%2x f,BANKED\n",next_8);
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
    printf("iorfwf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"iorwf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("iorwf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"iorwf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("iorwf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"iorwf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("iorwf  0x%2x f,BANKED\n",next_8);
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
    printf("movf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"movf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("movf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"movf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("movf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"movf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("movf  0x%2x f,BANKED\n",next_8);
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
    printf("movwf  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"movwf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("movwf  0x%2x BANKED\n",next_8);
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
    printf("mulwf  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"mulwf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 11)
  {
    printf("mulwf  0x%2x BANKED\n",next_8);
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
    printf("negf  0x%2x ACCESS\n",next_8);
    sprintf(buffer,"negf  0x%2x ACCESS",next_8);
  }
  else if (differentiate == 01)
  {
    printf("negf  0x%2x BANKED\n",next_8);
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
    printf("rlcf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"rlcf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rlcf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"rlcf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rlcf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"rlcf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rlcf  0x%2x f,BANKED\n",next_8);
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
    printf("rlncf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"rlncf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rlncf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"rlncf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rlncf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"rlncf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rlncf  0x%2x f,BANKED\n",next_8);
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
    printf("rrcf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"rrcf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rrcf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"rrcf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rrcf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"rrcf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rrcf  0x%2x f,BANKED\n",next_8);
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
    printf("rrncf  0x%2x WREG,ACCESS\n",next_8);
    sprintf(buffer,"rrncf  0x%2x WREG,ACCESS",next_8);
  }
  else if(differentiate == 01)
  {
    printf("rrncf  0x%2x WREG,BANKED\n",next_8);
    sprintf(buffer,"rrncf  0x%2x WREG,BANKED",next_8);
  }
  else if(differentiate == 10)
  {
    printf("rrncf  0x%2x f,ACCESS\n",next_8);
    sprintf(buffer,"rrncf  0x%2x f,ACCESS",next_8);
  }
  else
  {
    printf("rrncf  0x%2x f,BANKED\n",next_8);
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
    printf("setf  0x%2x ACCESS\n",next_8);
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
    //printf("error , no such opcode to display");
    sprintf(buffer,"error , no such opcode to display");
  }
  return buffer;
}

char* addlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("addlw %#4x",next_8);
  sprintf(buffer,"addlw %#4x",next_8);
  return buffer;
}

char* andlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("andlw %#4x",next_8);
  sprintf(buffer,"andlw %#4x",next_8);
  return buffer;
}

char* iorlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("iorlw %#4x",next_8);
  sprintf(buffer,"iorlw %#4x",next_8);
  return buffer;
}

char* movlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("movlw %#4x",next_8);
  sprintf(buffer,"movlw %#4x",next_8);
  return buffer;
}

char* mullw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("mullw %#4x",next_8);
  sprintf(buffer,"mullw %#4x",next_8);
  return buffer;
}

char* retlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("retlw %#4x",next_8);
  sprintf(buffer,"retlw %#4x",next_8);
  return buffer;
}

char* sublw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("sublw %#4x",next_8);
  sprintf(buffer,"sublw %#4x",next_8);
  return buffer;
}

char* xorlw(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  printf("xorlw %#4x",next_8);
  sprintf(buffer,"xorlw %#4x",next_8);
  return buffer;
}

char* movlb(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  thirdcode = (next_8 >> 4) & 0x0F;
  forthcode = next_8 & 0x0F;
  if(thirdcode == 0x0)
  {
    printf("movlb%#4x",forthcode);
    sprintf(buffer,"movlb%#4x",forthcode);
  }
  else
  {
    printf("error, no such opcode");
    sprintf(buffer,"error, no such opcode");
  }
  return buffer;
}

char* nop1(uint8_t *code)
{
  char *buffer;
  buffer = malloc(1028);
  printf("nop");
  sprintf(buffer,"nop");
  return buffer;
}

int ad(uint8_t code)
{
  uint8_t adcode = upperByte & 0x03;
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
  uint8_t adcode = upperByte & 0x01;
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
  uint8_t adcode = upperByte & 0x0E;
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
