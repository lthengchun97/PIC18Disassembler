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

void test_subwf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x5C,0x55,0x5D,0x88,0x5E,0x66,0x5F,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST subwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("subwf 0x55 WREG,ACCESS\nsubwf 0x88 WREG,BANKED\nsubwf 0x66 f,ACCESS\nsubwf 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_subwfb(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x58,0x55,0x59,0x88,0x5A,0x66,0x5B,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST subwfb :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("subwfb 0x55 WREG,ACCESS\nsubwfb 0x88 WREG,BANKED\nsubwfb 0x66 f,ACCESS\nsubwfb 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_subfwb(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x54,0x55,0x55,0x88,0x56,0x66,0x57,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST subfwb :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("subfwb 0x55 WREG,ACCESS\nsubfwb 0x88 WREG,BANKED\nsubfwb 0x66 f,ACCESS\nsubfwb 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_sublw(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x55,0x08,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST sublw :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,2);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x55\nsublw 0x88\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
