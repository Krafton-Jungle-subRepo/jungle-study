#include <stdio.h>

union NumberType {
    int int_val;
    char char_val;
};

int main() {
    union NumberType numbers = { 10 };
    printf("%d\n", numbers.int_val);

    numbers.char_val = 65;
    printf("%d\n", numbers.int_val);
    printf("%c\n", numbers.char_val);
}