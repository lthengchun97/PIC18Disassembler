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

void test_andwf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x14,0x55,0x15,0x88,0x16,0x66,0x17};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST addwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("andwf 0x55 WREG,ACCESS\nandwf 0x88 WREG,BANKED\nandwf 0x66 f,ACCESS\nandwf 0x 0 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_andlw(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x0B,0x55,0x0B,0x88};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST addwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,2);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("andlw 0x55\nandlw 0x88\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
