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

void test_addwf(void)
{
  char* result = disassembler(0x2456);
  TEST_ASSERT_EQUAL_STRING("addwf  0x57 WREG,ACCESS",result);
  free(result);
}
