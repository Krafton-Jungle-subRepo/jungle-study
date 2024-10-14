#include <stdio.h>

struct s1 {
    int a;
    int b;
};

typedef struct _S2 {
    int c;
    int d;
} s2;

int main() {
    struct s1 o1;
    o1.a = o1.b = 1;

    s2 o2;
    o2.c = o2.d = 2;

    // 구조체 element 접근 방법
    printf("%d, %d, %d, %d\n", o1.a, o1.b, o2.c, o2.d);

    s2* struct_ptr = &o2;
    // 구조체 pointer element 접근 방법
    printf("%d, %d\n", struct_ptr->c, struct_ptr->d);
}