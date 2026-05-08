#include <stdio.h>
#include <string.h>

#define Base 1000
#define Capacity 100

typedef struct {
    int data[Capacity];
    int size;
}BigInt;

void BigInit_Init(BigInt* bi) {
    bi->size = 0;
    memset(bi->data, 0, sizeof(bi->data));
}

void BigInit_Copy(BigInt* dest, const BigInt* src) {
    dest->size = src->size;
    memcpy(dest->data, src->data, sizeof(src->data));
}

void BigInt_FromString(BigInt* bi, const char s[]) {
    int b = 1;  // 1 10 100 1000 1 10 100 1000
    bi->size = 0;
    bi->data[ bi->size ] = 0;
    // 012 345 678
    //  2   1   0
    // size = 3
    for(int i = strlen(s)-1; i >= 0; --i) {
       bi->data[bi->size] +=  (s[i]-'0') * b;
       b *= 10;
       if(b >= Base) {
           b = 1;
           bi->size++;
           bi->data[bi->size] = 0;
       }
    }
    if(bi->data[bi->size] > 0) {
        bi->size++;
    }
}

void BigInt_Print(const BigInt* bi, char end) {
    if(bi->size == 0) {
        printf("0");
    }else {
        printf("%d", bi->data[bi->size-1]);
        for(int i = bi->size-2; i >= 0; --i) {
            for(int j = Base/10; j > 0; j /= 10) {
                // 100 10 1
                printf("%d", bi->data[i]/j % 10);
            }
        }
    }
    printf("%c", end);
}

char s[10010];
BigInt b;
int main() {
    scanf("%s", s);
    BigInit_Init(&b);
    BigInt_FromString(&b, s);
    BigInt_Print(&b, '\n');
    return 0;
}
