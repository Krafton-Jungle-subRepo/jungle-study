#include <stdio.h>
#include <stdlib.h>

int main() {

    // example 1)
    printf("========================================\n");
    printf("example 1\n\n");

    int temp;
    int* pointer = &temp;
    printf("int pointer: %d\n", pointer);
    printf("char pointer: %d\n", (char*)pointer);
    printf("========================================\n");

    printf("\n\n");

    // example 2)
    printf("========================================\n");
    printf("example 2\n\n");

    int var = 5;
    int* single_pointer = &var;
    int** double_pointer = &single_pointer;
    int*** triple_pointer = &double_pointer;

    triple_pointer = single_pointer;

    printf("single_pointer: %d\n", single_pointer);
    printf("double_pointer: %d\n", double_pointer);
    printf("triple_pointer: %d\n", triple_pointer);
    printf("\n");
    printf("var = %d, *triple_pointer = %d\n", var, *triple_pointer);
    printf("========================================\n");

    printf("\n\n");

    // example 3)
    printf("========================================\n");
    printf("exmaple 3\n\n");

    int* int_pointer;
    long long int* long_pointer;
    char* char_pointer;
    printf("int pointer: %d, %d\n", int_pointer, int_pointer + 1);
    printf("long pointer: %d, %d\n", long_pointer, long_pointer + 1);
    printf("char pointer: %d, %d\n", char_pointer, char_pointer + 1);
    printf("========================================\n");

    printf("\n\n");

    // example 4)
    printf("========================================\n");
    printf("example 4\n\n");

    long int l = 10;
    void* void_pointer = l;
    printf("void pointer: %d\n", void_pointer);
    printf("========================================\n");

    printf("\n\n");

    // example 5)
    printf("========================================\n");
    printf("example 5\n\n");
    
    struct s1 {
        long int li1;
        void* vp1;
    };

    struct s2 {
        void* vp2;
        long int li2;
    };

    struct s1* s = (struct s1*)malloc(sizeof(struct s1));
    ((struct s2*)s)->li2 = 10;
    printf("s1->vp1: %d\n", s->vp1);
    free(s);
    printf("========================================\n");
}