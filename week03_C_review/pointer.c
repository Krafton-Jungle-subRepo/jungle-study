#include <stdio.h>

void add1(int a) {
    a++;  // 값이 변하지 않음
}

void add2(int* a) {
    (*a) += 2;  // 값이 변함
}

int main() {
    int a = 1;
    add1(a);
    printf("%d\n", a);

    add2(&a);
    printf("%d\n", a);
}