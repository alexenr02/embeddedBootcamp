#include <stdint.h>
#include "dummy.h"

uint32_t sum( uint32_t a, uint32_t b )
{
    return a + b;
}

uint32_t sub( uint32_t a, uint32_t b )
{
    return a - b;
}

uint32_t mul( uint32_t a, uint32_t b )
{
    return a * b;
}

uint32_t subs;

uint32_t substraction( uint32_t a )
{
    return a - subs;
}