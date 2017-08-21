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

void test_mulwf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x02,0x55,0x03,0x88,0x03,0x5F,0x02,0x8A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST mulwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("mulwf 0x55 ACCESS\nmulwf 0x88 BANKED\nmulwf 0x5f BANKED\nmulwf 0x8a ACCESS\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_mullw(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x0D,0x55,0x0D,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST mulwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,2);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("mullw 0x55\nmullw 0x88\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
