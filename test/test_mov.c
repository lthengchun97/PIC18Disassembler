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

void test_movff(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0xC9,0x55,0xF5,0x88,0xC9,0x66,0xF5,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movff :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,2);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("movff 0x955,0x588\nmovff 0x966,0x577\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_movf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x50,0x55,0x51,0x88,0x52,0x66,0x53,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("movf 0x55 WREG,ACCESS\nmovf 0x88 WREG,BANKED\nmovf 0x66 f,ACCESS\nmovf 0x77 f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_movwf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x6E,0x55,0x6F,0x88,0x6F,0x66,0x6E,0x77};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movwf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("movwf 0x55 ACCESS\nmovwf 0x88 BANKED\nmovwf 0x66 BANKED\nmovwf 0x77 ACCESS\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_movlw_movlb(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x0E,0x55,0x0E,0x88,0x01,0x07,0x01,0x08};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movlw and movlb :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("movlw 0x55\nmovlw 0x88\nmovlb 0x7\nmovlb 0x8\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
