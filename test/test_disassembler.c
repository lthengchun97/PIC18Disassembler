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
    printf("%s",result);
    TEST_ASSERT_EQUAL_STRING("movff 0x955,0x588subwfb  0x66 WREG,BANKEDsubwfb  0x77 WREG,BANKEDsubwfb  0x68 WREG,BANKED",result);

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
    printf("%s",result);
    TEST_ASSERT_EQUAL_STRING("addwf  0x25 WREG,ACCESSmovlw 0x66bra 0x015movff 0x058,0x188bsf  0x85 3,ACCESS",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }

  //freeException(ex);                // If at try there do the correct thing , we no need to free it.

}

void test_clrf_addlw_rcall_tblrt_lfsr_and_last_upperbyte_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x6B,0x70,0x0F,0x55,0xD8,0x66,0x00,0x09,0xEE,0x55,0xF0,0x15,0xE9,0x66};
  uint8_t *codePtr = memory;
  uint8_t *codeMem = memory;
  printf("=============================================================================================");
  printf("\nTEST 3 :\n");
  printf("OUTPUT:\n");
  //char* result = disassembleNBytes(&codePtr,6);          // the last value represent how many instruction we display
  printf("\n");
  //TEST_ASSERT_EQUAL(10, codePtr - memory);               //compare number of bytes which been successfully been disassembles
  Try {
    char *result=disassembleNBytes(&codePtr,6);
    printf("%s",result);
    //TEST_ASSERT_EQUAL_STRING("movff  0x955, 0x588subwfb  0x66 WREG,BANKEDsubwfb  0x77 WREG,BANKEDsubwfb  0x68 WREG,BANKED",result);
  } Catch(ex) {
    //char *result=disassembleNBytes(&codeMem,6);
    //printf("%s",result);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }

  freeException(ex);
}

void test_sublw_iorlw_xorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_given_movlw_wrong(void)
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
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("addwf  0x25 WREG,ACCESSmovlw 0x66bra 0x015movff 0x058,0x188bsf  0x85 3,ACCESS",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_all_correct(void)
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
    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_but_movlb_wrong(void)
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
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}


void test_sublw_iorlw_xorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_but_movlb_wrong1(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x0F,0x07,0x01,0xFF};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 7 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_xorlw_andlw_retlw_movlb_mullw_movlw_addlw_but_movlb_wrong1(void)
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
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
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
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
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
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
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
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
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
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
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
    TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*",result);
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
    TEST_ASSERT_EQUAL_STRING("addwfc  0x24 f,BANKED",result);
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
    TEST_ASSERT_EQUAL(2, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("addwfc  0x24 f,BANKED",result);
  } Catch(ex) {
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
  TEST_ASSERT_EQUAL_STRING("xorwf  0x24 WREG,ACCESS",result);
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
  TEST_ASSERT_EQUAL_STRING("xorwf  0x24 WREG,ACCESS",result);
  }Catch(ex) {
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
    TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
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
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
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
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
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
    TEST_ASSERT_EQUAL_STRING("bnov 0x66bc 0x89bnc 0xf1bov 0x5abnov 0x4abn 0xeebnn 0x9a",result);
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
    TEST_ASSERT_EQUAL(14, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("bnov 0x66bc 0x89bnc 0xf1bov 0x5abnov 0x4abn 0xeebnn 0x9a",result);
  } Catch(ex) {
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
  printf("\nTEST 22 :\n");
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
/*
void test_clrf_expect_correct(void)
{
  uint8_t memory[]={0x6A,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_clrf_expect_wrong(void)
{
  uint8_t memory[]={0x6B,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_comf_expect_correct(void)
{
  uint8_t memory[]={0x1C,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_comf_expect_wrong(void)
{
  uint8_t memory[]={0x1F,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 f,ACCESS",result);
  free(result);
}

void test_cpfseq_expect_correct(void)
{
  uint8_t memory[]={0x62,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfseq_expect_wrong(void)
{
  uint8_t memory[]={0x63,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_correct(void)
{
  uint8_t memory[]={0x64,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_wrong(void)
{
  uint8_t memory[]={0x6E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_correct(void)
{
  uint8_t memory[]={0x60,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_wrong(void)
{
  uint8_t memory[]={0x61,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_decf_expect_correct(void)
{
  uint8_t memory[]={0x04,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_decf_expect_wrong(void)
{
  uint8_t memory[]={0x07,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_correct(void)
{
  uint8_t memory[]={0x2E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_wrong(void)
{
  uint8_t memory[]={0x2D,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_correct(void)
{
  uint8_t memory[]={0x4D,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 WREG,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_wrong(void)
{
  uint8_t memory[]={0x4E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 f,BANKED",result);
  free(result);
}

void test_incf_expect_correct(void)
{
  uint8_t memory[]={0x29,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 WREG,BANKED",result);
  free(result);
}

void test_incf_expect_wrong(void)
{
  uint8_t memory[]={0x2A,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 f,BANKED",result);
  free(result);
}

void test_btg_expect_wrong(void)
{
  uint8_t memory[]={0x86,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("btg  0x59 6,ACCESS",result);
  free(result);
}

void test_bc_expect_wrong(void)
{
  uint8_t memory[]={0x44,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("bc  0x59",result);
  free(result);
}

void test_tblrd_expect_wrong(void)
{
  uint8_t memory[]={0x00,0xFF};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("TBLRD*",result);
  free(result);
}

void test_addlw_expect_correct(void)
{
  uint8_t memory[]={0x0F,0x58};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addlw 0x58",result);
  free(result);
}

void test_movlb_expect_correct(void)
{
  uint8_t memory[]={0x01,0x0F};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("movlb 0xf",result);
  free(result);
}

void test_nop2_expect_correct(void)
{
  uint8_t memory[]={0xFF,0xFF};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("nop",result);
  free(result);
}
*/
