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

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_given_movlw_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0xE9,0x77,0x0F,0x07,0x01,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movlw wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("addwf  0x25 WREG,ACCESSmovlw 0x66bra 0x015movff 0x058,0x188bsf  0x85 3,ACCESS",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0xE9, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_addlw_movlb_all_correct(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x0F,0x87,0x01,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST all correct :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    TEST_ASSERT_EQUAL(18, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_STRING("sublw 0x65\niorlw 0x88\nxorlw 0x10\nandlw 0x25\nretlw 0x66\nmullw 0x85\nmovlw 0x77\naddlw 0x87\nmovlb 0x7\n",result);
  } Catch(ex) {
    dumpException(ex);
  }
  //freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_mullw_movlw_movlb_addlw_but_movlb_wrong(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x0D,0x85,0x0E,0x77,0x01,0xFF,0x0F,0x07};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movlb wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display

    TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    TEST_ASSERT_EQUAL(16, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0xFF, ex->errorCode);
    dumpException(ex);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}

void test_sublw_iorlw_xorlw_andlw_retlw_movlb_mullw_movlw_addlw_but_movlb_wrong1(void)
{
  CEXCEPTION_T ex;
  uint8_t memory[]={0x08,0x65,0x09,0x88,0x0A,0x10,0x0B,0x25,0x0C,0x66,0x01,0x8F,0x0E,0x77,0x0F,0x07,0x01,0x01};
  uint8_t *codePtr = memory;
  printf("=============================================================================================");
  printf("\nTEST movlb wrong :\n");
  printf("OUTPUT:\n");
  printf("\n");
  Try {
    char* result = disassembleNBytes(&codePtr,9);           // the last value represent how many instruction we display
    //TEST_ASSERT_EQUAL_STRING("sublw 0x65iorlw 0x88xorlw 0x10andlw 0x25retlw 0x66mullw 0x85movlw 0x77addlw  0x7movlb 0x7",result);
  } Catch(ex) {
    dumpException(ex);
    TEST_ASSERT_EQUAL(12, codePtr - memory);               //compare number of bytes which been successfully been disassemble
    TEST_ASSERT_EQUAL_HEX(0x8F,ex->errorCode);
    //printf("Error instruction: 0x%2x",ex->errorCode);
  }
  freeException(ex);                // If at Try there all get the correct thing , we no need to free it.
}
