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

void test_tblrd_tblwt(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST tblrd and tblwt :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*\nTBLRD*+\nTBLRD*-\nTBLRD+*\nTBLWT*\nTBLWT*+\nTBLWT*-\nTBLWT+*\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_wrong_last_byte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x23};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST tblwt and tblrd and lastbyte wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x23, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_earlier_wrong_lowerbyte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x89,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST tblwt and tblrd wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(4, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x89,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_middle_wrong_lowerbyte(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x78,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST tblrd and tblwt mid wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,8);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("TBLRD*TBLRD*+TBLRD*-TBLRD+*TBLWT*TBLWT*+TBLWT*-TBLWT+*",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x78,ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_tblrd_tblwt_given_long_memory_but_set_4_instruction_to_pass(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x00,0x08,0x00,0x09,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x0D,0x00,0x0E,0x00,0x0F};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST only pass 4 set tblrd and tblwt :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,4);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("TBLRD*\nTBLRD*+\nTBLRD*-\nTBLRD+*\n",result);
  } Catch(ex) {
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}
