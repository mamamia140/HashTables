#include <stdio.h>
#include <stdlib.h>

typedef struct anan{
    int x;
    int y;
}ANAN;

int main(){
    ANAN anan;
    anan.x = 5;
    anan.y = 6;
    ANAN baban;
    baban.x = 7;
    baban.y = 8;
    ANAN* pointer = (ANAN*)malloc(sizeof(ANAN));
    free(pointer);
    pointer = &baban;
    printf("%d",pointer->y);
    return 0;
}