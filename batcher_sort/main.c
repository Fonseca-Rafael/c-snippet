/**
 * @ref: Goemans, M - Lecture note 18.310
 * @link: https://math.mit.edu/~shor/18.310/batcher.pdf
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @note N must be power of 2
 */
#define N 8

static void compare(int* AL, int* AR)
{
    int aux;
    if(*AL >= *AR){
        aux = *AL;
        *AL  = *AR;
        *AR  = aux;
    }
}

/**
 * @fn      merge
 * @brief   merge
 * @note    originally the merge starts with odds but due C indexing 1 is not 
 *          the first position so here we start with evens 
 */
static void __merge(const int p0, const int pn, int* A)
{
    int i;
    int j;
    int m;
    int n;

    n = (pn - p0) + 1;
    m = n/2;

    // even sort;
    compare(A+p0, A+(p0+m));
    for(i=2; i<n-4; i+=2){
        for(j=i+2; j<n; j+=2){
            compare(A+p0+i, A+p0+j);
        }
    } 
    compare(A+p0+(n-4), A+(p0+(n-2)));
   
    // odd sort 
    compare(A+p0+1, A+(p0+m+1));
    for(i=3; i<n-3; i+=2){
        for(j=i+2; j<n; j+=2){
            compare(A+p0+i, A+p0+j);
        }
    } 
    compare(A+p0+(n-3), A+(p0+(n-1)));
    
    // final merge
    for(i=1; i<=n-2; i+=2){
        compare(A+p0+i, A+p0+i+1);
    }
}

/**
 * @fn      merge
 * @brief   merge
 * @note    originally the merge starts with odds but due C indexing 1 is not 
 *          the first position so here we start with evens 
 */
static void merge(const int p0, const int pn, int* A)
{
    int i;
    int j;

    // even sort;
    for(i=p0; i<=pn; i+=2){
        for(j=i+2; j<pn; j+=2){
            compare(A+i, A+j);
        }
    }
    
    // odds sort;
    for(i=p0+1; i<=pn; i+=2){
        for(j=i+2; j<=pn; j+=2){
            compare(A+i, A+j);
        }
    }
    
    // final merge
    for(i=p0+1; i<=pn-2; i+=2){
        compare(A+i, A+i+1);
    }
    
}

/**
 * @fn      sort
 * @brief   recursive sort
 */
static void sort(const int p0, const int pn, int* A)
{
    int m;
    int n;

    n = (pn - p0) + 1;
    m = n/2;
    
    if(m == 1){ 
        compare(A+p0, A+pn);
        return;
    }
    
    sort(p0, p0+(m-1), A);
    sort((p0+m), pn, A);
    
    __merge(p0, pn, A);
}

/**
 * @fn      main
 * @brief   entry point
 */
int main(int argc, char **argv)
{
    int idx;
   
    //int A[N] = {8, 20, 84, 31, 14, 84, 39, 48, 80, 72, 77, 72, 24, 84, 57, 66}; 
    int A[N] = {2, 7, 6, 3, 9, 4, 1, 8};
    // random initialization
    /*
    int A[N];
    
    srand(time(NULL));
    for(idx=0; idx<N; ++idx){
        A[idx] = rand() % 100 + 1;
    }
    */

    printf(" == original array:\n");
    for(idx=0; idx<N; ++idx){
        printf("%d ", A[idx]);
    }
    printf("\n");

    sort(0, N-1, A);
    
    printf(" == sorted array:\n");
    for(idx=0; idx<N; ++idx){
        printf("%d ", A[idx]);
    }
    printf("\n");

    return 0;
}
