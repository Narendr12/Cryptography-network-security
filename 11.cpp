#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

double log2_factorial(int n) {
    double result = 0;
    for (int i = 1; i <= n; i++) {
        result += log2(i);
    }
    return result;
}

int main() {
    int keyLength = 25;
    double totalKeysLog2 = log2_factorial(keyLength);
    printf("Total possible keys (approx. in 2^x): 2^%.2f\n", totalKeysLog2);
    double effectiveKeysLog2 = totalKeysLog2 - log2(keyLength);
    printf("Effectively unique keys (approx. in 2^x): 2^%.2f\n", effectiveKeysLog2);
    return 0;
}

