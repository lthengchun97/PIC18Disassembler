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

void test_rlcf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x34,0x55,0x35,0x88,0x36,0x5F,0x37,0x8A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST rlcf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("rlcf 0x55 WREG,ACCESS\nrlcf 0x88 WREG,BANKED\nrlcf 0x5f f,ACCESS\nrlcf 0x8a f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_rlncf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x44,0x55,0x45,0x88,0x46,0x5F,0x47,0x8A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST rlncf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("rlncf 0x55 WREG,ACCESS\nrlncf 0x88 WREG,BANKED\nrlncf 0x5f f,ACCESS\nrlncf 0x8a f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_rrcf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x30,0x55,0x31,0x88,0x32,0x5F,0x33,0x8A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST rrcf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("rrcf 0x55 WREG,ACCESS\nrrcf 0x88 WREG,BANKED\nrrcf 0x5f f,ACCESS\nrrcf 0x8a f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}

void test_rrncf(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x40,0x55,0x41,0x88,0x42,0x5F,0x43,0x8A};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST rrncf :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,4);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("rrncf 0x55 WREG,ACCESS\nrrncf 0x88 WREG,BANKED\nrrncf 0x5f f,ACCESS\nrrncf 0x8a f,BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
