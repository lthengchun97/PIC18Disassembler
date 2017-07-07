#include "disassembler.h"

char * dissamble (uint32_h code)
{
  typedef struct Opcode Opcode;
  
  int opcode = code >> 8;
  
  struct code{
    int (*execute)(uint8_t *code); 
    int a;
    int d;
  };
  
  int addwf (uint8_t *code){
    if(a==0 && d==0)
      printf("addwf WREG,ACCESS");
    if(a==0 && d==1)
      printf("addwf WREG,f");
    if(a==1 && d==0)
      printf("addwf BANKED,ACCESS");
    else
      printf("addwf BANKED,f");
    return 0;
  };
  
  Opcode opcodeTable[256] = {  
    [0x24]={addwf,0,0},
    [0x25]={addwf,0,1},
    [0x26]={addwf,1,0},
    [0x27]={addwf,1,1},
  
  };
}
