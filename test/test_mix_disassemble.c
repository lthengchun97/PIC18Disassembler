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
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
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
  uint8_t memory[]={0x6B,0x70,0x0F,0x55,0xD8,0x66,0x00,0x09,0xEE,0x55,0xF0,0x15,0xE9,0x66};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 3 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    disassembleNBytes(&codePtr,6);
  } Catch(ex) {
    //TEST_ASSERT_EQUAL_STRING("movff  0x955, 0x588subwfb  0x66 WREG,BANKEDsubwfb  0x77 WREG,BANKEDsubwfb  0x68 WREG,BANKED",ex->msg);
    TEST_ASSERT_EQUAL(12, codePtr - memory);                //compare number of bytes which been successfully been disassembles
    TEST_ASSERT_EQUAL_HEX(0xE9, ex->errorCode);
    dumpException(ex);
  }

  freeException(ex);
}

void test_only_one_instuction_word_using_disassembleNBytes_function(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x23,0x24};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 4 :\n");
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
  printf("\nTEST 5 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,1);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL_STRING("addwfc  0x24 f,BANKED",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(0, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0xE8,ex->errorCode);
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
  printf("\nTEST 6 :\n");
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
  printf("\nTEST 7 :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try{
  char* result = disassemble(&codePtr);
  }Catch(ex) {
    TEST_ASSERT_EQUAL(0, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0xE9,ex->errorCode);
    dumpException(ex);
  }
  freeException(ex);
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
    TEST_ASSERT_EQUAL_HEX(0xE8,ex->errorCode);
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
    //TEST_ASSERT_EQUAL_STRING("bnov 0x66bc 0x89bnc 0xf1bov 0x5abnov 0x4abn 0xeebnn 0x9a",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(12, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_HEX(0xE9, ex->errorCode);               // 0xE9 will be the errorCode of this test function
    //printf("Error instruction: 0x%2x",ex->errorCode);
    }
    freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}
