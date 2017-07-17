#include "unity.h"
#include "disassembler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void setUp(void)
{
}

void tearDown(void)
{
}

void test_addwf_expect_correct_given_correct_identifier_and_correct_value(void)
{
  char* result = disassembler(0x2559);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 WREG,BANKED",result);
  free(result);
}

void test_addwf_expect_wrong_given_correct_identifier_and_wrong_value(void)
{
  char* result = disassembler(0x2569);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 WREG,BANKED",result);
  free(result);
}

void test_addwf_expect_wrong_given_wrong_identifier_and_correct_value(void)
{
  char* result = disassembler(0x2459);
  TEST_ASSERT_EQUAL_STRING("addwf  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_wrong_given_wrong_identifier_correct_value(void)
{
  char* result = disassembler(0x2259);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_correct_given_correct_identifier_correct_value(void)
{
  char* result = disassembler(0x2359);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_addwfc_expect_wrong_given_correct_identifier_wrong_value(void)
{
  char* result = disassembler(0x2380);
  TEST_ASSERT_EQUAL_STRING("addwfc  0x59 f,BANKED",result);
  free(result);
}

void test_andwf_expect_correct(void)
{
  char* result = disassembler(0x1659);
  TEST_ASSERT_EQUAL_STRING("andwf  0x59 f,ACCESS",result);
  free(result);
}

void test_clrf_expect_correct(void)
{
  char* result = disassembler(0x6A59);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_clrf_expect_wrong(void)
{
  char* result = disassembler(0x6B59);
  TEST_ASSERT_EQUAL_STRING("clrf  0x59 ACCESS",result);
  free(result);
}

void test_comf_expect_correct(void)
{
  char* result = disassembler(0x1C59);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_comf_expect_wrong(void)
{
  char* result = disassembler(0x1F59);
  TEST_ASSERT_EQUAL_STRING("comf  0x59 f,ACCESS",result);
  free(result);
}

void test_cpfseq_expect_correct(void)
{
  char* result = disassembler(0x6259);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfseq_expect_wrong(void)
{
  char* result = disassembler(0x6359);
  TEST_ASSERT_EQUAL_STRING("cpfseq  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_correct(void)
{
  char* result = disassembler(0x6459);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfsgt_expect_wrong(void)
{
  char* result = disassembler(0x6E59);
  TEST_ASSERT_EQUAL_STRING("cpfsgt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_correct(void)
{
  char* result = disassembler(0x6059);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_cpfslt_expect_wrong(void)
{
  char* result = disassembler(0x6159);
  TEST_ASSERT_EQUAL_STRING("cpfslt  0x59 ACCESS",result);
  free(result);
}

void test_decf_expect_correct(void)
{
  char* result = disassembler(0x0459);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 WREG,ACCESS",result);
  free(result);
}

void test_decf_expect_wrong(void)
{
  char* result = disassembler(0x0759);
  TEST_ASSERT_EQUAL_STRING("decf  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_correct(void)
{
  char* result = disassembler(0x2E59);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,ACCESS",result);
  free(result);
}

void test_decfsz_expect_wrong(void)
{
  char* result = disassembler(0x2D59);
  TEST_ASSERT_EQUAL_STRING("decfsz  0x59 f,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_correct(void)
{
  char* result = disassembler(0x4D59);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 WREG,BANKED",result);
  free(result);
}

void test_dcfsnz_expect_wrong(void)
{
  char* result = disassembler(0x4E59);
  TEST_ASSERT_EQUAL_STRING("dcfsnz  0x59 f,BANKED",result);
  free(result);
}

void test_incf_expect_correct(void)
{
  char* result = disassembler(0x2959);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 WREG,BANKED",result);
  free(result);
}

void test_incf_expect_wrong(void)
{
  char* result = disassembler(0x2A59);
  TEST_ASSERT_EQUAL_STRING("incf  0x59 f,BANKED",result);
  free(result);
}

void test_btg_expect_wrong(void)
{
  char* result = disassembler(0x8659);
  TEST_ASSERT_EQUAL_STRING("btg  0x59 6,ACCESS",result);
  free(result);
}

void test_bc_expect_wrong(void)
{
  char* result = disassembler(0x4439);
  TEST_ASSERT_EQUAL_STRING("bc 0x59",result);
  free(result);
}

void test_tblrd_expect_wrong(void)
{
  char* result = disassembler(0x00ff);
  TEST_ASSERT_EQUAL_STRING("TBLRD*",result);
  free(result);
}
