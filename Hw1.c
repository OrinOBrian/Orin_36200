#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>

void funct(int);

int main() {
    LARGE_INTEGER start, end, frequency;
    int num, testn;
    char b = 'c'; // Initialize b to a character other than 'q'
    double sum;

    while (b == 'c') { // Change condition to check for 'q'
        printf("Enter # of iterations: ");
        scanf("%d", &num);
        printf("Enter # of Tests: ");
        scanf("%d", &testn);
        
        sum=0.0;
        if (testn > 0) {
            for (int i = 0; i < testn; i++) {
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&start);
                funct(num);
                QueryPerformanceCounter(&end);
                
                double T = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
                sum += T;
            }
            printf("%f Average time nanoseconds\n", sum/testn);
            printf("Press 'c' to continue or 'q' to quit: "); // Update prompt
            scanf(" %c", &b); // Space before %c to ignore previous newline character
        } else {
            break;
        }
        if(num>100000)
            break;
    }

    return 0; // Return from main
}

void funct(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            sum++;
    }
}