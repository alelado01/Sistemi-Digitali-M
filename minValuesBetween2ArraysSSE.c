#include <stdio.h>
#include <immintrin.h>
#include <math.h>

int main()
{
  
    short A[8] __attribute__((aligned(16)));
    short B[8] __attribute__((aligned(16)));
    __m128i *p_A = (__m128i*) A;
    __m128i *p_B = (__m128i*) B;
    
    for(int i=0; i<8; i++)
    {
      A[i]=(rand() %127)+1;
      B[i]=(rand() %127)+1;
    }
    for(int i=0; i<8; i++)
    {
      printf("%d\t", A[i]);
      printf("%d\n", B[i]);
    }
    
    __m128i mask = _mm_cmplt_epi16(*p_A, *p_B);
    
    __m128i minA = _mm_and_si128(*p_A, mask);
    short minA_array[8] __attribute__((aligned(16)));
    _mm_store_si128((__m128i*)minA_array, minA);
    printf("\nmin A:\n");
     for(int i=0; i<8; i++)
    {
      printf("\n%d\n", minA_array[i]);
    }
    
    __m128i minB = _mm_andnot_si128(mask, *p_B);
     short minB_array[8] __attribute__((aligned(16)));
    _mm_store_si128((__m128i*)minB_array, minB);
    printf("\nmin B:\n");
     for(int i=0; i<8; i++)
    {
      printf("\n%d\n", minB_array[i]);
    }
    
    __m128i dst = _mm_or_si128(minA, minB);
    
    short dstArray[8] __attribute__((aligned(16)));
    _mm_store_si128((__m128i*)dstArray, dst);
    printf("\nmin totale:\n");
    for(int i=0; i<8; i++)
    {
      printf("\n%d\n", dstArray[i]);
    }
    return 0;
}

