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

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x03};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST zero firstbyte correct :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("clrwdt \ndaw \nnop \npop \npush \nreset \nretfie \nreturn \nsleep \n",result);
  } Catch(ex) {
    dumpException(ex);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_given_middle_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0x7F,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x03};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST zero firstbyte wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x7F,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_clrwdt_daw_nop_pop_push_reset_retfie_return_sleep_given_lastbyte_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x04,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0xFF,0x00,0x11,0x00,0x13,0x00,0x78};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST zero firstbyte wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
  //  TEST_ASSERT_EQUAL_STRING("clrwdt daw nop pop push reset retfie return sleep ",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x78,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}
