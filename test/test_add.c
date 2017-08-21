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

void test_addwf(void)
{
CEXCEPTION_T ex;
uint8_t memory[]={0x25,0x55,0x26,0x88,0x27,0x66,0x24,0x77,0x24,0x68};
uint8_t *codePtr = memory;
printf("=============================================================================================");
printf("\nTEST addwf :\n");
printf("OUTPUT:\n");
printf("\n");

Try {
  char *result = disassembleNBytes(&codePtr,5);          // the last value represent how many instruction we display
  TEST_ASSERT_EQUAL(10, codePtr - memory);               //compare number of bytes which been successfully been disassemble
  TEST_ASSERT_EQUAL_STRING("addwf 0x55 WREG,BANKED\naddwf 0x88 f,ACCESS\naddwf 0x66 f,BANKED\naddwf 0x77 WREG,ACCESS\naddwf 0x68 WREG,ACCESS\n",result);

} Catch(ex) {
  dumpException(ex);
  //printf("Error instruction: 0x%2x",ex->errorCode);
}
// freeException(ex);
}

void test_addlw(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x0F,0x55,0x0F,0x88,0x0F,0x66,0x0F,0x77,0x0F,0x68};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST addlw :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,5);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("addlw 0x55\naddlw 0x88\naddlw 0x66\naddlw 0x77\naddlw 0x68\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_addwfc(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x20,0x55,0x21,0x88,0x22,0x66,0x23,0x77,0x22,0x68};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST addwfc :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,5);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(10, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("addwfc 0x55 WREG,ACCESS\naddwfc 0x88 WREG,BANKED\naddwfc 0x66 f,ACCESS\naddwfc 0x77 f,BANKED\naddwfc 0x68 f,ACCESS\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
