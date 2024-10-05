#include <stdio.h>

void printA() {
    // static 변수 선언
    // 최초 1회 초기화, 프로그램이 끝날때까지 메모리에 유지
    static int t = 10;
    printf("%d\n", t);
    t++;
    return;
}

int main() {
    int i;
    for(i = 0; i < 5; i++)
        printA();
    
    const int const_val = 5;
    // const_val = 7;  // 컴파일 에러
}