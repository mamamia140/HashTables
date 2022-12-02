#include <stdio.h>

int main() {
    int var =100;
    char int_str[20];

    sprintf(int_str, "%d", var);
    printf("Var: %s", int_str);
    return 0;
}