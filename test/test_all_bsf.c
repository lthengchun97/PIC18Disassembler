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

void test_bcf_bsf_btfsc_btfss_btg_all_correct_all_give_0_and_ACCESS(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x90,0x55,0x80,0x86,0xB0,0x7F,0xA0,0x99,0x70,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST 0,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 0,ACCESS\nbsf  0x86 0,ACCESS\nbtfsc  0x7f 0,ACCESS\nbtfss  0x99 0,ACCESS\nbtg  0x88 0,ACCESS\n",result);
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
  printf("\nTEST 0,BANKED :\n");
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
  printf("\nTEST 1,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 1,ACCESS\nbsf  0x86 1,ACCESS\nbtfsc  0x7f 1,ACCESS\nbtfss  0x99 1,ACCESS\nbtg  0x88 1,ACCESS\n",result);
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
  printf("\nTEST 1,BANKED :\n");
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
  printf("\nTEST 2,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 2,ACCESS\nbsf  0x86 2,ACCESS\nbtfsc  0x7f 2,ACCESS\nbtfss  0x99 2,ACCESS\nbtg  0x88 2,ACCESS\n",result);
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
  printf("\nTEST 2,BANKED :\n");
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
  printf("\nTEST 3,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 3,ACCESS\nbsf  0x86 3,ACCESS\nbtfsc  0x7f 3,ACCESS\nbtfss  0x99 3,ACCESS\nbtg  0x88 3,ACCESS\n",result);
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
  printf("\nTEST 3,BANKED :\n");
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
  printf("\nTEST 4,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 4,ACCESS\nbsf  0x86 4,ACCESS\nbtfsc  0x7f 4,ACCESS\nbtfss  0x99 4,ACCESS\nbtg  0x88 4,ACCESS\n",result);
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
  printf("\nTEST 4,BANKED :\n");
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
  printf("\nTEST 5,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 5,ACCESS\nbsf  0x86 5,ACCESS\nbtfsc  0x7f 5,ACCESS\nbtfss  0x99 5,ACCESS\nbtg  0x88 5,ACCESS\n",result);
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
  printf("\nTEST 5,BANKED :\n");
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
  printf("\nTEST 6,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 6,ACCESS\nbsf  0x86 6,ACCESS\nbtfsc  0x7f 6,ACCESS\nbtfss  0x99 6,ACCESS\nbtg  0x88 6,ACCESS\n",result);
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
  printf("\nTEST 6,BANKED :\n");
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
  printf("\nTEST 7,ACCESS :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_STRING("bcf  0x55 7,ACCESS\nbsf  0x86 7,ACCESS\nbtfsc  0x7f 7,ACCESS\nbtfss  0x99 7,ACCESS\nbtg  0x88 7,ACCESS\n",result);
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
  printf("\nTEST 7,BANKED :\n");
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
  printf("\nTEST bsf wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,5);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("bcf  0x55 7,BANKED\nbsf  0x86 7,BANKED\nbtfsc  0x7f 7,BANKED\nbtfss  0x99 7,BANKED\nbtg  0x88 7,BANKED\n",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(2, codePtr - memory);              // in this test only 12 bytes will be run.
    TEST_ASSERT_EQUAL_HEX(0xE8,ex->errorCode);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
    freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}
