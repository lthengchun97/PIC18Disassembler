#include "unity.h"
#include "disassembler.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_addwf(void)
{
  char result = dissamble(0x2400);  
  TEST_ASSERT_EQUAL_STRING("addwf WREG,ACCESS",result);
}
