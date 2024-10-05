#include <stdio.h>

int t;  // 전역변수 선언, 0으로 초기화
void printA(int a) {
    printf("%d\n", a);
}

int main() {
    t = 5;
    printA(t);

    // printf("%d\n", a);  // 컴파일 에러
}