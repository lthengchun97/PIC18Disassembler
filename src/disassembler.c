#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>

checkidentifier opcodeTable[256] = {
  [0x24]={addwf,0,0},
  [0x25]={addwf,0,1},
  [0x26]={addwf,1,0},
  [0x27]={addwf,1,1}

};


  char * disassembler (uint32_t code)
{
  int opcode = code >> 8;
  return NULL;
}

int addwf (uint8_t *code){
  uint8_t next_8 = *code & 0x00ff;
  if(a==0 && d==0)
    printf("addwf %d WREG,ACCESS",next_8);
  if(a==0 && d==1)
    printf("addwf %d WREG,f",next_8);
  if(a==1 && d==0)
    printf("addwf %d BANKED,ACCESS",next_8);
  else
    printf("addwf %d BANKED,f",next_8);
  return 0;
};
