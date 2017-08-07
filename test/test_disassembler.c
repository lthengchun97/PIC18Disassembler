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

void test_movff_expect_wrong(void)
{
  CEXCEPTION_T ex = NULL;
  uint8_t memory[]={0xC9,0x55,0xF5,0x88,0x9A,0x66,0x25,0x77};
  char* show= "0xC9,0x55,0xF5,0x88,0xE9,0x66,0x25,0x77";
  uint8_t *codePtr = memory;
  //char* strBuffer = malloc(strlen(result) + 1);
  //strcpy(strBuffer, result);
  //TEST_ASSERT_EQUAL_STRING("addwf  0x59 WREG,BANKED",strBuffer);
  //TEST_ASSERT_EQUAL(8, codePtr - memory);               //compare number of bytes
  //TEST_ASSERT_EQUAL(8, opcodeTable[upperByte].size);
  //TEST_ASSERT_EQUAL(4,codePtr);
  OperatorToken token = {
   .type = TOKEN_OPERATOR_TYPE,
   .startColumn = 20,
   .length = 4,
   .originalStr = show,
   .str = "0xE9",
 };
  Try {
    throwException(ERR_INVALID_OPERAND, (void *)&token,                     \
                   "Invalid opecode, opcode of %s cannot be usee",      \
                    token.str);
  } Catch(ex) {
//    dumpException(ex);
    dumpErrorMessage(ex, 1);
  }
  freeException(ex);
  printf("OUTPUT:\n");
  char* result = disassembleNBytes(&codePtr,3);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 WREG,BANKED",result);
  free(result);
}

void dumpErrorMessage(CEXCEPTION_T ex, int lineNo) {
  Token *token = (Token *)ex->data;
  int i = token->length - 1;
  if(i < 0) i = 0;

  printf("Error %d:\n", lineNo);
  printf("%s\n", ex->msg);
  printf("%s\n", token->originalStr);
  printf("%*s", token->startColumn + 1, "^");
  while(i--)
    printf("~");
  putchar('\n');
}
/*
void test_addwf_expect_wrong_given_correct_identifier_and_wrong_value(void)
{
  uint8_t memory[]={0xE8,0x69};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 WREG,BANKED",result);
  free(result);
}

void test_addwf_expect_wrong_given_wrong_identifier_and_correct_value(void)
{
  uint8_t memory[]={0x24,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_wrong_given_wrong_identifier_correct_value(void)
{
  uint8_t memory[]={0x22,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_correct_given_correct_identifier_correct_value(void)
{
  uint8_t memory[]={0x23,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_wrong_given_correct_identifier_wrong_value(void)
{
  uint8_t memory[]={0x23,0x80};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_andwf_expect_correct(void)
{
  uint8_t memory[]={0x16,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("andwf  0x59 f,ACCESS",result);
  free(result);
}

void test_clrf_expect_correct(void)
{
  uint8_t memory[]={0x6A,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_clrf_expect_wrong(void)
{
  uint8_t memory[]={0x6B,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_comf_expect_correct(void)
{
  uint8_t memory[]={0x1C,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_comf_expect_wrong(void)
{
  uint8_t memory[]={0x1F,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 f,ACCESS",result);
  free(result);
}

void test_cpfseq_expect_correct(void)
{
  uint8_t memory[]={0x62,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfseq_expect_wrong(void)
{
  uint8_t memory[]={0x63,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_correct(void)
{
  uint8_t memory[]={0x64,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_wrong(void)
{
  uint8_t memory[]={0x6E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_correct(void)
{
  uint8_t memory[]={0x60,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_wrong(void)
{
  uint8_t memory[]={0x61,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_decf_expect_correct(void)
{
  uint8_t memory[]={0x04,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_decf_expect_wrong(void)
{
  uint8_t memory[]={0x07,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_correct(void)
{
  uint8_t memory[]={0x2E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_wrong(void)
{
  uint8_t memory[]={0x2D,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_correct(void)
{
  uint8_t memory[]={0x4D,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 WREG,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_wrong(void)
{
  uint8_t memory[]={0x4E,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 f,BANKED",result);
  free(result);
}

void test_incf_expect_correct(void)
{
  uint8_t memory[]={0x29,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 WREG,BANKED",result);
  free(result);
}

void test_incf_expect_wrong(void)
{
  uint8_t memory[]={0x2A,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 f,BANKED",result);
  free(result);
}

void test_btg_expect_wrong(void)
{
  uint8_t memory[]={0x86,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("btg  0x59 6,ACCESS",result);
  free(result);
}

void test_bc_expect_wrong(void)
{
  uint8_t memory[]={0x44,0x59};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("bc  0x59",result);
  free(result);
}

void test_tblrd_expect_wrong(void)
{
  uint8_t memory[]={0x00,0xFF};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("TBLRD*",result);
  free(result);
}

void test_addlw_expect_correct(void)
{
  uint8_t memory[]={0x0F,0x58};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("addlw 0x58",result);
  free(result);
}

void test_movlb_expect_correct(void)
{
  uint8_t memory[]={0x01,0x0F};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("movlb 0xf",result);
  free(result);
}

void test_nop2_expect_correct(void)
{
  uint8_t memory[]={0xFF,0xFF};
  uint8_t *codePtr = memory;
  char* result = disassembler(&codePtr);
  TEST_ASSERT_EQUAL_STRING("nop",result);
  free(result);
}
*/
