#include <stdio.h>

enum week {
    monday,
    tuesday,
    wendsday,
    thursday,
    friday,
    saterday,
    sunday
};

int main() {
    enum week day;

    day = thursday;
    printf("%d\n", day);
}