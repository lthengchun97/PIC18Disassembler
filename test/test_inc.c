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

void test_incf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x28,0x55,0x29,0x88,0x2A,0x66,0x2B,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST incf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("incf 0x55 WREG,ACCESS\nincf 0x88 WREG,BANKED\nincf 0x66 f,ACCESS\nincf 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_incfsz(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x3C,0x55,0x3D,0x88,0x3E,0x66,0x3F,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST incfsz :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("incfsz 0x55 WREG,ACCESS\nincfsz 0x88 WREG,BANKED\nincfsz 0x66 f,ACCESS\nincfsz 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_infsnz(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x48,0x55,0x49,0x88,0x4A,0x66,0x4B,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST infsnz :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("infsnz 0x55 WREG,ACCESS\ninfsnz 0x88 WREG,BANKED\ninfsnz 0x66 f,ACCESS\ninfsnz 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
