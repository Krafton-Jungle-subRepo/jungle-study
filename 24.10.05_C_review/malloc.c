#include <stdio.h>
#include <stdlib.h>  // malloc, free

int main() {
    int* a = (int*)malloc(sizeof(int));  // int의 크기를 *a에 할당
    int* b = (int*)malloc(sizeof(int) * 5);  // 크기 5의 int형 배열 할당

    // 동적할당된 메모리 해제
    // 메모리 해제를 하지 않는다면??
    free(a);
    free(b);
}