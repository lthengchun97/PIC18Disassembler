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

void test_cpfseq_cpfsgt_cpfslt(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x62,0x55,0x63,0x88,0x64,0x66,0x65,0x77,0x60,0x77,0x61,0x9D};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST cpfseq,cpfsgt and cpfslt :\n");
  printf("OUTPUT:\n");
  printf("\n");

  Try {
    char *result = disassembleNBytes(&codePtr,6);          // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("cpfseq 0x55 ACCESS\ncpfseq 0x88 BANKED\ncpfsgt 0x66 ACCESS\ncpfsgt 0x77 BANKED\ncpfslt 0x77 ACCESS\ncpfslt 0x9d BANKED\n",result);

  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  // freeException(ex);
}
