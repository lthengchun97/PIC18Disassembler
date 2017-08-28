#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "CException.h"
#include "Exception.h"
#include <stdarg.h>
#include "string.h"

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
  [0xD0]={bra,2},
  [0xD1]={bra,2},
  [0xD2]={bra,2},
  [0xD3]={bra,2},
  [0xD4]={bra,2},
  [0xD5]={bra,2},
  [0xD6]={bra,2},
  [0xD7]={bra,2},
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

char* disassembleNBytes(uint8_t **codePtrPtr, int nCodes)
{
  char* str;
  char* buff = malloc(30*nCodes);
  str=malloc(30*nCodes);
  int i;
   for( i = 0 ; i < nCodes ; i++)
   {
    str = disassemble(codePtrPtr);
    strcat(str,"\n");
    printf("%s",str);
    if( i == 0)
      strcpy(buff,str);
    else
      strcat(buff,str);
   }
   return buff;
}

/**
 * Disassemble 1 instruction only
 */
char* disassemble(uint8_t **codePtrPtr)
{
  uint8_t *codePtr = *codePtrPtr;
  // codePtr use for checking the bytes
  if(opcodeTable[codePtr[0]].size==4)
  {
  upperByte=codePtr[0];     // 1st byte
  next_8=codePtr[1];        // 2nd byte
  next_16=codePtr[2];       // 3rd byte
  next_32=codePtr[3];         // 4th byte
  }
  else
  {
    upperByte =codePtr[0];     // 1st byte
    next_8 =codePtr[1];        // 2nd byte
  }

  if(opcodeTable[upperByte].execute == 0)                       // Once detect the wrong instruction, it will stop ...
  {
    throwException(upperByte,"\n Program stopped.Invalid upperByte opcode detected : 0x%2x",upperByte);
  }
  else                                                         // If the instruction can be find, it will continue here ...
  {
    char* buffer = malloc(1028);
    *codePtrPtr += opcodeTable[upperByte].size;               // The reason to uses this add the size of the word instruction is because in PIC18,
    return opcodeTable[upperByte].execute(codePtr);           // There are some opcode using 2 word instruction and 4 word instruction, so we need to
  }                                                           // increment the size so that when in checking the memory in main_test, it will know how
}                                                             // many of bytes it need to skip and do for the next word instruction.

char* composeFda(char* opcodeName, uint8_t fileReg,int dirAccessFlags)
{
  char* buffer = malloc(50);
  switch(dirAccessFlags){
    case 1:sprintf(buffer,"%s 0x%2x WREG,ACCESS",opcodeName,fileReg);
            break;
    case 2:sprintf(buffer,"%s 0x%2x WREG,BANKED",opcodeName,fileReg);
            break;
    case 3:sprintf(buffer,"%s 0x%2x f,ACCESS",opcodeName,fileReg);
            break;
    case 4:sprintf(buffer,"%s 0x%2x f,BANKED",opcodeName,fileReg);
            break;
  }
  return buffer;
}

char* composeFa(char* opcodeName, uint8_t fileReg,int dirAccessFlags)
{
  char* buffer = malloc(50);
  switch(dirAccessFlags){
    case 1:sprintf(buffer,"%s 0x%2x ACCESS",opcodeName,fileReg);
            break;
    case 2:sprintf(buffer,"%s 0x%2x BANKED",opcodeName,fileReg);
            break;
  }
  return buffer;
}

char* composeAb(char* opcodeName, uint8_t fileReg,int checkBflags,int dirAccessFlags)
{
  char* buffer = malloc(50);
  switch(dirAccessFlags){
    case 1:sprintf(buffer,"%s  %#4x %d,ACCESS",opcodeName,fileReg,checkBflags);
            break;
    case 2:sprintf(buffer,"%s  %#4x %d,BANKED",opcodeName,fileReg,checkBflags);
            break;
  }
  return buffer;
}

char* composeF(char* opcodeName, uint8_t fileReg)
{
  char* buffer = malloc(50);
  sprintf(buffer,"%s 0x%2x",opcodeName,fileReg);
  return buffer;
}

char *movff(uint8_t *code)
{
  char *buffer;
  buffer = malloc(30);
  upperByte = upperByte & 0x0F;
  uint8_t movff_test = (next_16 >> 4) & 0x0F;
  thirdcode = next_16 & 0x0F;
  if(movff_test == 0xF)
  {
    sprintf(buffer,"movff 0x%x%2x,0x%x%2x",upperByte,next_8,thirdcode,next_32);
  }
  else
  {
    throwException(next_16,"\n Program stopped.Invalid thirdByte opcode for special opcode movff (0x%2x)detected : 0x%2x",upperByte,next_16);
  }
  return buffer;
}

char *rcall(uint8_t *code)
{
  char *buffer;
  buffer = malloc(30);
  upperByte = upperByte &0x07;
  sprintf(buffer,"rcall 0x%x%2x",upperByte,next_8);
  return buffer;
}

char *bra(uint8_t *code)
{
  char *buffer;
  buffer = malloc(30);
  upperByte = upperByte &0x07;
  sprintf(buffer,"bra 0x%x%2x",upperByte,next_8);
  return buffer;
}

char* call(uint8_t *code)
{
  char* buffer;
  buffer = malloc(30);
  thirdcode = next_16 & 0xF0;
  if(thirdcode == 0xF0)
    {
      sprintf(buffer,"call 0x%2x\nnop 0x%2x",next_8,next_32 );
    }
  else
  {
    throwException(next_16, "\n Program stopped.Invalid thirdByte opcode for special opcode call (0x%2x) detected : 0x%2x",upperByte,next_16);
  }
  return buffer;
}

char* goto1(uint8_t *code)
{
  char* buffer;
  buffer = malloc(30);
  thirdcode = next_16 & 0xF0;
  if(thirdcode == 0xF0)
    {
      sprintf(buffer,"goto 0x%2x\nnop 0x%2x",next_8,next_32);
    }
  else
  {
    throwException(next_16, "\n Program stopped.Invalid thirdByte opcode for special opcode goto (0x%2x) detected : 0x%2x",upperByte,next_16);
  }
  return buffer;
}

char* lfsr(uint8_t *code)
{
  char* buffer;
  buffer = malloc(30);
  thirdcode = next_16 & 0xFF;
  if(thirdcode == 0xF0)
    {
      sprintf(buffer,"lfsr 0x%2x, 0x%2x",next_8,next_32);
    }
  else
  {
    throwException(next_16,"\n Program stopped.Invalid thirdByte opcode for special opcode lfsr (0x%2x) detected : 0x%2x",upperByte,next_16);
  }
  return buffer;
}

char* addwf (uint8_t *code)
{
  return composeFda("addwf",next_8,ad(code));
}

char* addwfc(uint8_t *code){
  return composeFda("addwfc",next_8,ad(code));
}

char* andwf(uint8_t *code){
  return composeFda("andwf",next_8,ad(code));
}

char* clrf(uint8_t *code){
  return composeFa("clrf",next_8,a(code));
}

char* comf(uint8_t *code)
{
  return composeFda("comf",next_8,ad(code));
}

char* cpfseq(uint8_t *code)
{
  return composeFa("cpfseq",next_8,a(code));
}

char* cpfsgt(uint8_t *code)
{
  return composeFa("cpfsgt",next_8,a(code));
}

char* cpfslt(uint8_t *code)
{
  return composeFa("cpfslt",next_8,a(code));
}

char* decf(uint8_t *code)
{
  return composeFda("decf",next_8,ad(code));
}

char* decfsz(uint8_t *code)
{
  return composeFda("decfsz",next_8,ad(code));
}

char* dcfsnz(uint8_t *code)
{
  return composeFda("dcfsnz",next_8,ad(code));
}

char* incf(uint8_t *code)
{
  return composeFda("incf",next_8,ad(code));
}

char* incfsz(uint8_t *code)
{
  return composeFda("incfsz",next_8,ad(code));
}

char* infsnz(uint8_t *code)
{
  return composeFda("infsnz",next_8,ad(code));
}

char* iorwf(uint8_t *code)
{
  return composeFda("iorwf",next_8,ad(code));
}

char* movf(uint8_t *code)
{
  return composeFda("movf",next_8,ad(code));
}

char* movwf(uint8_t *code)
{
  return composeFa("movwf",next_8,a(code));
}

char* mulwf(uint8_t *code)
{
  return composeFa("mulwf",next_8,a(code));
}

char* negf(uint8_t *code)
{
  return composeFa("negf",next_8,a(code));
}

char* rlcf(uint8_t *code)
{
  return composeFda("rlcf",next_8,ad(code));
}

char* rlncf(uint8_t *code)
{
  return composeFda("rlncf",next_8,ad(code));
}

char* rrcf(uint8_t *code)
{
  return composeFda("rrcf",next_8,ad(code));
}

char* rrncf(uint8_t *code)
{
  return composeFda("rrncf",next_8,ad(code));
}

char* setf(uint8_t *code)
{
  return composeFa("setf",next_8,a(code));
}

char* subfwb(uint8_t *code)
{
  return composeFda("subfwb",next_8,ad(code));
}

char* subwf(uint8_t *code)
{
  return composeFda("subwf",next_8,ad(code));
}

char* subwfb(uint8_t *code)
{
  return composeFda("subwfb",next_8,ad(code));
}

char* swapf(uint8_t *code)
{
  return composeFda("swapf",next_8,ad(code));
}

char* tstfsz(uint8_t *code)
{
  return composeFa("tstfsz",next_8,a(code));
}

char* xorwf(uint8_t *code)
{
  return composeFda("xorwf",next_8,ad(code));
}

char* bcf(uint8_t *code)
{
  return composeAb("bcf",next_8,bbb(code),a(code));
}

char* bsf(uint8_t *code)
{
  return composeAb("bsf",next_8,bbb(code),a(code));
}

char* btfsc(uint8_t *code)
{
  return composeAb("btfsc",next_8,bbb(code),a(code));
}


char* btfss(uint8_t *code)
{
  return composeAb("btfss",next_8,bbb(code),a(code));
}

char* btg(uint8_t *code)
{
  return composeAb("btg",next_8,bbb(code),a(code));
}

char* bc(uint8_t *code)
{
  return composeF("bc",next_8);
}

char* bn(uint8_t *code)
{
  return composeF("bn",next_8);
}

char* bnc(uint8_t *code)
{
  return composeF("bnc",next_8);
}

char* bnn(uint8_t *code)
{
  return composeF("bnn",next_8);
}

char* bnov(uint8_t *code)
{
  return composeF("bnov",next_8);
}

char* bnz(uint8_t *code)
{
  return composeF("bnov",next_8);
}

char* bov(uint8_t *code)
{
  return composeF("bov",next_8);
}

char* zero(uint8_t *code)
{
  char* buffer;
  buffer = malloc(20);
  if(next_8 == 0x08)
  {
    sprintf(buffer,"TBLRD*");
  }
  else if(next_8 == 0x09)
  {
    sprintf(buffer,"TBLRD*+");
  }
  else if(next_8 == 0x0A)
  {
    sprintf(buffer,"TBLRD*-");
  }
  else if(next_8 == 0x0B)
  {
    sprintf(buffer,"TBLRD+*");
  }
  else if(next_8 == 0x0C)
  {
    sprintf(buffer,"TBLWT*");
  }
  else if(next_8 == 0x0D)
  {
    sprintf(buffer,"TBLWT*+");
  }
  else if(next_8 == 0x0E)
  {
    sprintf(buffer,"TBLWT*-");
  }
  else if(next_8 == 0x0F)
  {
    sprintf(buffer,"TBLWT+*");
  }
  else if(next_8 == 0x04)
  {
    sprintf(buffer,"clrwdt ");
  }
  else if(next_8 == 0x07)
  {
    sprintf(buffer,"daw ");
  }
  else if(next_8 == 0x00)
  {
    sprintf(buffer,"nop ");
  }
  else if(next_8 == 0x06)
  {
    sprintf(buffer,"pop ");
  }
  else if(next_8 == 0x05)
  {
    sprintf(buffer,"push ");
  }
  else if(next_8 == 0xFF)
  {
    sprintf(buffer,"reset ");
  }
  else if(next_8 == 0x11 || next_8 == 0x10)
  {
    sprintf(buffer,"retfie ");
  }
  else if(next_8 == 0x12 || next_8 == 0x13)
  {
    sprintf(buffer,"return ");
  }
  else if(next_8 == 0x03)
  {
    sprintf(buffer,"sleep ");
  }
  else
  {
    throwException(next_8, "\n Program stopped.Invalid lowerByte opcode for special upperByte 0x00 detected : 0x%2x",next_8);
  }
  return buffer;
}

char* addlw(uint8_t *code)
{
  return composeF("addlw",next_8);
}

char* andlw(uint8_t *code)
{
  return composeF("andlw",next_8);
}

char* iorlw(uint8_t *code)
{
  return composeF("iorlw",next_8);
}

char* movlw(uint8_t *code)
{
  return composeF("movlw",next_8);
}

char* mullw(uint8_t *code)
{
  return composeF("mullw",next_8);
}

char* retlw(uint8_t *code)
{
  return composeF("retlw",next_8);
}

char* sublw(uint8_t *code)
{
  return composeF("sublw",next_8);
}

char* xorlw(uint8_t *code)
{
  return composeF("xorlw",next_8);
}

char* movlb(uint8_t *code)
{
  char* buffer;
  buffer = malloc(1028);
  thirdcode = (next_8 >> 4) & 0x0F;
  forthcode = next_8 & 0x0F;
  if(thirdcode == 0x0)
  {
    sprintf(buffer,"movlb%#4x",forthcode);
  }
  else
  {
    throwException(next_8, "\n Program stopped.Invalid lowerByte opcode for special upperByte %#04x (movlb) detected : 0x%2x",upperByte,next_8);
  }
  return buffer;
}

char* nop1(uint8_t *code)
{
  char *buffer;
  buffer = malloc(5);
  sprintf(buffer,"nop");
  return buffer;
}
/**
  This function is to check the status of the RAM and DESTINATION
  For RAM:
          a=0 :RAM location in Access RAM (BSR register is ignored)
          a=1 :RAM bank is specified by BSR register
  For DESTINATION:
          d=0 :store result in WREG
          d=1 :store result in file register f

  In most of the function, we knew that the arrange of RAM and DESTINATION
  status is , for example like :
                  movlw xxx d,a

  Thus, in this function , i made it for a = MSB and d = LSB and listed out
  all the possibility for the a and d.

  And this function can be called by the opcodeTable function to detect what
  it should be wrote in.
**/
int ad(uint8_t *code)
{
  uint8_t adcode = upperByte & 0x03;
  if(adcode == 0x00)
  {
    return 1;
  }
  else if( adcode == 0x01)
  {
    return 2;
  }
  else if( adcode == 0x02)
  {
    return 3;
  }
  else
  {
    return 4;
  }
}

/**
  In this function, we only find the a value for the opcode function,
  because it doesnt have the d value to do,whereas we can just ignore it.
**/
int a(uint8_t *code)
{
  uint8_t adcode = upperByte & 0x01;
  if(adcode == 0x00)
  {
    return 1;
  }
  else
  {
    return 2;
  }
}
/**
  This function is to find the bit address within an 8-bit file register
  for some certain opcode.
  It is from 0x00 to 0x0F.
**/
int bbb(uint8_t *code)
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
  else
    return 0;
}
