#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


void bucle1(float *A, float *B, float *C, int X, int T)
{
  for (int t=0; t<T; t++) 
  {
    for (int x=0; x<X; x++)
    {
      if (x!=t)
        C[x*T+t] = A[x]*B[t];
      else
        C[x*T+t] = 0.0f;
    }
  }
}


void bucle2(float *A, float *B, float *C, int X, int T)
{
  for (int t=0; t<T; t++) 
  {
    float Max = C[t];    
    for (int x=0; x<X; x++)
    {
      if (C[x*T+t] > Max)
        Max = C[x*T+t];
    }
    B[t]= Max;
  }
}

int main(int argc, char **argv) 
{
  int X= 2000, T= 500000;
  float *A, *B, *C;

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
    T2 = func2 ( A, X, T1 );
    T1 = func1 ( A, B, X, T1 );
    R += T1+T2;
    float *tmp= A; A=B; B=C; C=tmp; // rotate vectors
  }

  free(B); free(C);

  B = (float *) malloc (T*sizeof(float));
  C = (float *) malloc (X*T*sizeof(float));

  init ( A, X, 2.65f );
  init ( B, T, 0.53f );

  bucle1 (A, B, C, X, T);
  bucle2 (A, B, C, X, T);

  printf("***********************\nR= %e, T1= %e, T2= %e, ", R, T1, T2);
  printf("CheckSum(B) = %e\n", checkSUM( B, T ));

  free(A); free(B); free(C);
}
