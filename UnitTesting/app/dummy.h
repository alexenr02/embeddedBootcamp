#ifndef __DUMMY_H__
#define __DUMMY_H__

uint32_t sum( uint32_t a, uint32_t b );
uint32_t sub( uint32_t a, uint32_t b );
uint32_t mul( uint32_t a, uint32_t b );

static inline uint32_t increment( uint32_t a )
{
    return a + 1;
}

#endif // __DUMMY_H_