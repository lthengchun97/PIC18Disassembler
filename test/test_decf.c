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

void test_decf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x04,0x55,0x05,0x88,0x06,0x66,0x07,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST decf:\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("decf 0x55 WREG,ACCESS\ndecf 0x88 WREG,BANKED\ndecf 0x66 f,ACCESS\ndecf 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_decfsz(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x2C,0x55,0x2D,0x88,0x2E,0x66,0x2F,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST decfsz:\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("decfsz 0x55 WREG,ACCESS\ndecfsz 0x88 WREG,BANKED\ndecfsz 0x66 f,ACCESS\ndecfsz 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_dcfsnz(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x4C,0x55,0x4D,0x88,0x4E,0x66,0x4F,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST dcfsnz:\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("dcfsnz 0x55 WREG,ACCESS\ndcfsnz 0x88 WREG,BANKED\ndcfsnz 0x66 f,ACCESS\ndcfsnz 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
