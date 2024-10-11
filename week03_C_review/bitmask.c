#include <stdio.h>

void printBinary(int t) {
    int i;
    for(i = 8; i > 0; i--) {
        if (t & (1 << i))
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main() {
    int mask = 0;
    mask = mask | (1 << 2);
    mask = mask | (1 << 4);
    mask = mask | (1 << 8);

    // boolean형 array [true, false, false, false, true, false, truem, false]
    printBinary(mask);
}