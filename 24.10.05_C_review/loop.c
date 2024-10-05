#include <stdio.h>

int main() {
    int i;
    for(i = 0; i < 5; i++)
        printf("%d, ", i);
    printf("\n");
    
    for(i = 0; i < 5; ++i)
        printf("%d, ", i);
    printf("\n");

    i = 0;
    while(i++ < 5)
        printf("%d, ", i);
    printf("\n");

    i = 0;
    while(++i < 5)
        printf("%d, ", i);
    printf("\n");

    i = 0;
    do {
        printf("%d, ", i);
    } while(++i < 5);
    printf("\n");

    i = 2;
    switch(i) {
        case 1:
            printf("this is 1\n");
            break;
        case 2:
            printf("this is 2\n");
            break;
        case 3:
            printf("this is 3\n");
            break;
    }
}