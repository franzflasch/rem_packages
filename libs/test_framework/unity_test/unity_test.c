#include "unity.h"
#include <stdio.h>

int unity_custom_putc(int x)
{
	return putchar(x);
}

void unity_custom_flush(void)
{
	fflush(stdout); 
}

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    printf("Hallo test_function_should_doBlahAndBlah");
}

void test_function_should_doAlsoDoBlah(void) {
    printf("Hallo test_function_should_doAlsoDoBlah");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}
