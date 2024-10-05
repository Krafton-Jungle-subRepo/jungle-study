#include <stdio.h>

void changeString(char* s) {  // 배열은 포인터와 같음
    s[0] = 'A';
}

int main() {
    char s[10];
    scanf("%s", s);  
    // 9글자를 넘어가면 에러
    // 마지막 글자는 '\0'

    printf("%s\n", s);

    changeString(s);
    printf("%s\n", s);
}