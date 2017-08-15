#include "unity.h"
#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include <stdarg.h>
#include <string.h>
#include "error.h"
#include "Token.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_movff_subwfb_addwf_subwfb_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xC9,0x55,0xF5,0x88,0x59,0x66,0x59,0x77,0x59,0x68};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 1 :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("movff 0x955,0x588\nsubwfb 0x66 WREG,BANKED\nsubwfb 0x77 WREG,BANKED\nsubwfb 0x68 WREG,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_addwf_movlw_bra_movff_bsf_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x24,0x25,0x0E,0x66,0xD0,0x15,0xC0,0x58,0xF1,0x88,0x86,0x85};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 2 :\n");
  printf("OUTPUT:\n");
  //char* result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    //printf("%s",result);
    TEST_ASSERT_EQUAL_STRING("addwf 0x25 WREG,ACCESS\nmovlw 0x66\nbra 0x015\nmovff 0x058,0x188\nbsf  0x85 3,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }

  //freeException(ex);                // If at try there do the correct thing , we no need to free it.

}

void test_clrf_addlw_rcall_tblrt_lfsr_and_last_upperbyte_wrong(void)
{
  CEXCEPTION_T ex;
  //char* result;
  uint8_t memory[]={0x6B,0x70,0x0F,0x55,0xD8,0x66,0x00,0x09,0xEE,0x55,0xF0,0x15,0xE9,0x66};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 3 :\n");
  printf("OUTPUT:\n");
  //char* result = disassembleNBytes(&codePtr,6);          // the last value represent how many instruction we display
  printf("\n");
  Try {
    disassembleNBytes(&codePtr,6);
  } Catch(ex) {
    //TEST_ASSERT_EQUAL_STRING("movff  0x955, 0x588subwfb  0x66 WREG,BANKEDsubwfb  0x77 WREG,BANKEDsubwfb  0x68 WREG,BANKED",ex->msg);
    TEST_ASSERT_EQUAL(12, codePtr - memory);                //compare number of bytes which been successfully been disassembles
    TEST_ASSERT_EQUAL(0xE9, ex->errorCode);
    dumpException(ex);
  }

  freeException(ex);
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_given_movlw_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0xE9,0x77,0x0F,0x07,0x01,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 4 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("addwf  0x25 WREG,ACCESSmovlw 0x66bra 0x015movff 0x058,0x188bsf  0x85 3,ACCESS",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0xE9, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x0F,0x07,0x01,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 5 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x65\niorlw 0x88\nxorlw 0x10\nandlw 0x25\nretlw 0x66\nmullw 0x85\nmovlw 0x77\naddlw 0x 7\nmovlb 0x7\n",result);
  } Catch(ex) {
    dumpException(ex);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_but_movlb_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x0F,0x07,0x01,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 6 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x77, ex->errorCode);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_movlb_addlw_but_movlb_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x01,0xFF,0x0F,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 7 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display

    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0xFF, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_movlb_mullw_movlw_addlw_but_movlb_wrong1(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x01,0x8F,0x0E,0x77,0x0F,0x07,0x01,0x01};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 8 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x8F,ex->errorCode);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 9 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*\nTBLRD*+\nTBLRD*-\nTBLRD+*\nTBLWT*\nTBLWT*+\nTBLWT*-\nTBLWT+*\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_wrong_last_byte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x23};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 10 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x23, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_earlier_wrong_lowerbyte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x89,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 11 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x89,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_middle_wrong_lowerbyte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x78,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 12 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x78,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_long_memory_but_set_4_instruction_to_pass(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 13 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,4);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*\nTBLRD*+\nTBLRD*-\nTBLRD+*\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_only_one_instuction_word_using_disassembleNBytes_function(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x23,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 14 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,1);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(2, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("addwfc 0x24 f,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_only_one_instuction_word_and_wrong_using_disassembleNBytes_function(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xE8,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 15 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,1);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL_STRING("addwfc  0x24 f,BANKED",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(0, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0xE8,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_only_one_instuction_word_using_disassemble_function(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x18,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 16 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try{
  char* result = disassemble(&codePtr);
  printf("%s",result);
  TEST_ASSERT_EQUAL_STRING("xorwf 0x24 WREG,ACCESS",result);
  }Catch(ex) {
  dumpException(ex);
  }
  //freeException(ex);
}

void test_only_one_instuction_word_and_wrong_using_disassemble_function(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xE9,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 17 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try{
  char* result = disassemble(&codePtr);
  }Catch(ex) {
    TEST_ASSERT_EQUAL(0, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0xE9,ex->errorCode);
    dumpException(ex);
  }
  freeException(ex);
}

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x03};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 18 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("clrwdt \ndaw \nnop \npop \npush \nreset \nretfie \nreturn \nsleep \n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_given_middle_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0x7F,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x03};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 19 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x7F,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_given_lastbyte_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x78};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 20 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
  //  TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0x78,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bnz_bc_bnc_bov_bnov_bn_bnn_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xE1,0x66,0xE2,0x89,0xE3,0xF1,0xE4,0x5A,0xE5,0x4A,0xE6,0xEE,0xE7,0x9A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 21 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,7);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(14, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("bnov 0x66\nbc 0x89\nbnc 0xf1\nbov 0x5a\nbnov 0x4a\nbn 0xee\nbnn 0x9a\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bnz_bc_bnc_bov_bnov_bn_bnn_given_middle_wrong_instruction(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xE1,0x66,0xE2,0x89,0xE3,0xF1,0xE8,0x5A,0xE5,0x4A,0xE6,0xEE,0xE7,0x9A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 22 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,7);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("bnov 0x66bc 0x89bnc 0xf1bov 0x5abnov 0x4abn 0xeebnn 0x9a",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(6, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL(0xE8,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bnz_bc_bnc_bov_bnov_bn_bnn_given_last_upperByte_wrong_instruction(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xE1,0x66,0xE2,0x89,0xE3,0xF1,0xE4,0x5A,0xE5,0x4A,0xE6,0xEE,0xE9,0x9A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 23 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,7);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL_STRING("bnov 0x66bc 0x89bnc 0xf1bov 0x5abnov 0x4abn 0xeebnn 0x9a",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(12, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL(0xE9, ex->errorCode);               // 0xE9 will be the errorCode of this test function
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_0_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x90,0x55,0x80,0x86,0xB0,0x7F,0xA0,0x99,0x70,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 24 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 0,ACCESS\nbsf  0x86 0,ACCESS\nbstfsc  0x7f 0,ACCESS\nbtfss  0x99 0,ACCESS\nbtg  0x88 0,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_0_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x91,0x55,0x81,0x86,0xB1,0x7F,0xA1,0x99,0x71,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 25 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 0,BANKED\nbsf  0x86 0,BANKED\nbtfsc  0x7f 0,BANKED\nbtfss  0x99 0,BANKED\nbtg  0x88 0,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_1_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x92,0x55,0x82,0x86,0xB2,0x7F,0xA2,0x99,0x72,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 26 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 1,ACCESS\nbsf  0x86 1,ACCESS\nbstfsc  0x7f 1,ACCESS\nbtfss  0x99 1,ACCESS\nbtg  0x88 1,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_1_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x93,0x55,0x83,0x86,0xB3,0x7F,0xA3,0x99,0x73,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 27 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 1,BANKED\nbsf  0x86 1,BANKED\nbtfsc  0x7f 1,BANKED\nbtfss  0x99 1,BANKED\nbtg  0x88 1,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_2_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x94,0x55,0x84,0x86,0xB4,0x7F,0xA4,0x99,0x74,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 28 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 2,ACCESS\nbsf  0x86 2,ACCESS\nbstfsc  0x7f 2,ACCESS\nbtfss  0x99 2,ACCESS\nbtg  0x88 2,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_2_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x95,0x55,0x85,0x86,0xB5,0x7F,0xA5,0x99,0x75,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 29 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 2,BANKED\nbsf  0x86 2,BANKED\nbtfsc  0x7f 2,BANKED\nbtfss  0x99 2,BANKED\nbtg  0x88 2,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_3_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x96,0x55,0x86,0x86,0xB6,0x7F,0xA6,0x99,0x76,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 30 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 3,ACCESS\nbsf  0x86 3,ACCESS\nbstfsc  0x7f 3,ACCESS\nbtfss  0x99 3,ACCESS\nbtg  0x88 3,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_3_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x97,0x55,0x87,0x86,0xB7,0x7F,0xA7,0x99,0x77,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 31 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 3,BANKED\nbsf  0x86 3,BANKED\nbtfsc  0x7f 3,BANKED\nbtfss  0x99 3,BANKED\nbtg  0x88 3,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_4_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x98,0x55,0x88,0x86,0xB8,0x7F,0xA8,0x99,0x78,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 32 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 4,ACCESS\nbsf  0x86 4,ACCESS\nbstfsc  0x7f 4,ACCESS\nbtfss  0x99 4,ACCESS\nbtg  0x88 4,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_4_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x99,0x55,0x89,0x86,0xB9,0x7F,0xA9,0x99,0x79,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 33 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 4,BANKED\nbsf  0x86 4,BANKED\nbtfsc  0x7f 4,BANKED\nbtfss  0x99 4,BANKED\nbtg  0x88 4,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_5_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9A,0x55,0x8A,0x86,0xBA,0x7F,0xAA,0x99,0x7A,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 34 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 5,ACCESS\nbsf  0x86 5,ACCESS\nbstfsc  0x7f 5,ACCESS\nbtfss  0x99 5,ACCESS\nbtg  0x88 5,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_5_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9B,0x55,0x8B,0x86,0xBB,0x7F,0xAB,0x99,0x7B,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 35 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 5,BANKED\nbsf  0x86 5,BANKED\nbtfsc  0x7f 5,BANKED\nbtfss  0x99 5,BANKED\nbtg  0x88 5,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_6_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9C,0x55,0x8C,0x86,0xBC,0x7F,0xAC,0x99,0x7C,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 36 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 6,ACCESS\nbsf  0x86 6,ACCESS\nbstfsc  0x7f 6,ACCESS\nbtfss  0x99 6,ACCESS\nbtg  0x88 6,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_6_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9D,0x55,0x8D,0x86,0xBD,0x7F,0xAD,0x99,0x7D,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 37 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 6,BANKED\nbsf  0x86 6,BANKED\nbtfsc  0x7f 6,BANKED\nbtfss  0x99 6,BANKED\nbtg  0x88 6,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_7_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9E,0x55,0x8E,0x86,0xBE,0x7F,0xAE,0x99,0x7E,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 38 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 7,ACCESS\nbsf  0x86 7,ACCESS\nbstfsc  0x7f 7,ACCESS\nbtfss  0x99 7,ACCESS\nbtg  0x88 7,ACCESS\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_7_and_BANKED(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9F,0x55,0x8F,0x86,0xBF,0x7F,0xAF,0x99,0x7F,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 39 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 7,BANKED\nbsf  0x86 7,BANKED\nbtfsc  0x7f 7,BANKED\nbtfss  0x99 7,BANKED\nbtg  0x88 7,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_bcf_bsf_btfsc_btfss_btg_but_bsf_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x9F,0x55,0xE8,0x86,0xBF,0x7F,0xAF,0x99,0x7F,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 40 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("bcf  0x55 7,BANKED\nbsf  0x86 7,BANKED\nbtfsc  0x7f 7,BANKED\nbtfss  0x99 7,BANKED\nbtg  0x88 7,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(2, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL(0xE8,ex->errorCode);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_only_one_instuction_word_using_disassemble_function1(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x23,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 16 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try{
  char* result = disassemble(&codePtr);
  printf("%s",result);
  TEST_ASSERT_EQUAL_STRING("addwfc 0x24 f,BANKED",result);
  }Catch(ex) {
  dumpException(ex);
  }
  //freeException(ex);
}
