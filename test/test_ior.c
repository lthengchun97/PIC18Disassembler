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

void test_iorwf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x10,0x55,0x11,0x88,0x12,0x66,0x13,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST iorwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("iorwf 0x55 WREG,ACCESS\niorwf 0x88 WREG,BANKED\niorwf 0x66 f,ACCESS\niorwf 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_iorlw(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x09,0x55,0x09,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST iorlw :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,2);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("iorlw 0x55\niorlw 0x88\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
