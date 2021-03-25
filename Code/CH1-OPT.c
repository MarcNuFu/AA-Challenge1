#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xmmintrin.h>

//Tiempo de ejecucion:  4,327948547 seconds time elapsed
//Computador: aolin13.uab.es


void init ( float *U, int X, float V )
{
  float pi2 = 3.14159265f / X;
  for (int x=0; x<X; x++)
    U[x]= sin(x * pi2)*V;
}

float checkSUM ( float *In, int X )
{
  float S= 0;
  for (int x=0; x<X; x++)
    S = S + In[x];
  return S;
}

float func1( float *A, float *B, int X, float L)
{
  float T = L;
  for (int x=0; x<X; x++)
  {
    T = (T-A[x])*B[x];
  }
  return T;
}

float func2( float *A, int X, float L)
{
  float T = L;
  for (int x=0; x<X; x++)
  {
    T = (T-A[x])*A[x]+L;
  }
  return T;
}

float func( float *A, float *B, int X, float L, float *T2)
{
  float T1 = L;
  float T2temp = L;
  for (int x=0; x<X; x++)
  {
    T1 = (T1-A[x])*B[x];
    T2temp = (T2temp-A[x])*A[x]+L;
  }
  
  (*T2) = T2temp;
  return T1;
}


void bucle1(float *A, float *B, float *C, int X, int T)
{
  for (int x=0; x<X; x++)
  {
    for (int t=0; t<T; t++) 
    {
      C[x*T+t] = A[x]*B[t];
    }
    C[x*T+x] = 0.0f;
  }
}


void bucle2(float *A, float *B, float *C, int X, int T)
{
  for (int t=0; t<T; t++) 
  {
    B[t]= C[t];
  }

  for (int x=1; x<X; x++)
  {    
    for (int t=0; t<T; t++) 
    {
      if (C[x*T+t] > B[t])
        B[t] = C[x*T+t];
    }
  }
}

void bucle(float *A, float *B, float *MAX, int X, int T)
{
  float temp, tempMax;
  
  MAX[0] = 0;
  for (int t=1; t<T; t++) 
  {
    MAX[t]= A[0]*B[t];
  }
  
  for (int x=1; x<X; x++)
  {    
   
    for (int t=0; t<T; t++) 
    {
      temp = (x!=t ? A[x]*B[t] : 0.0f);
      
      if (temp > MAX[t])
        MAX[t] = temp;
    }
  }
  
}

int main(int argc, char **argv) 
{
  int X= 2000, T= 500000;
  float *A, *B, *C, *MAX;

  // get runtime arguments 
  if (argc>1) { X  = atoi(argv[1]); }
  if (argc>2) { T  = atoi(argv[2]); }

  A = (float *) malloc (X*sizeof(float));
  B = (float *) malloc (X*sizeof(float));
  C = (float *) malloc (X*sizeof(float));
  printf("AA. RETO1. X=%d, T=%d\n", X, T);

  init ( A, X, 0.65f );
  init ( B, X, 0.23f );
  init ( C, X, 0.83f );
  
  float R=0.0, T1=1.0f, T2=1.0f;

  for (int t=0; t<T; t++) 
  {
    
    T1 = func ( A, B, X, T1, &T2 );
    R += T1+T2;
    float *tmp= A; A=B; B=C; C=tmp; // rotate vectors
  }

  free(B); free(C);

  B = (float *) malloc (T*sizeof(float));
  MAX = (float *) malloc (T*sizeof(float));
  C = (float *) malloc (X*T*sizeof(float));

  init ( A, X, 2.65f );
  init ( B, T, 0.53f );

  bucle (A, B, MAX, X, T);

  printf("***********************\nR= %e, T1= %e, T2= %e, ", R, T1, T2);
  printf("CheckSum(B) = %e\n", checkSUM( MAX, T ));

  free(A); free(B); free(C); free(MAX);
}
