#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1f

typedef long long int64;

int array[100000];

/**
*
*   i  / 32   对应具体数组元素
*   i % 32  对应具体数组元素的bit位
*   i >> SHIFT == i /  32
*   i &  MASK   == i % 32
*   (32) = (100000)
*
**/

void set(int64 i)
{
    array[i >> SHIFT ] |= ( 1 << ( i & MASK));
}

void clear(int64 i)
{
    array[i >> SHIFT ] &= ~( 1 << ( i & MASK)); 
}

int test(int64 i)
{
    return array[ i >> SHIFT] & ( 1 << ( i & MASK));
}
