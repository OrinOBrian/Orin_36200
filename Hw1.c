#include <stdio.h>
#include <windows.h>

void funct(int);

int main(){
   LARGE_INTEGER start, end, frequency;
   int num;

    printf("Enter # of iterations: ");
    scanf("%d", &num);

    QueryPerformanceFrequency(&frequency);
    
    QueryPerformanceCounter(&start);
    
    funct(num);
    
    QueryPerformanceCounter(&end);
    
    double T = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
    
 printf("%f nanoseconds",T);
}

void funct(int n){
  int sum=0;
    for(int i =0;i<n;i++)
        sum++;
    
}