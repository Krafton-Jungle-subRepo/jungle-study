#include <stdio.h>

extern int a;  // 변수 선언
void printInt(int a);  // 함수의 선언(함수 프로토타입)

int main() {
    int a; // 변수 정의
    scanf("%d", &a);
    printInt(a);
}

void printInt(int a) {  // 함수 정의
    printf("%d\n", a);
}