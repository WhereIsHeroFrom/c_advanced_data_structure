#include <stdio.h>
#include <string.h>

#define Base 1000
#define Capacity 3400

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

void BigInt_RemoveLeadingZeros(BigInt *bi) {
    // result = 000 000 000 000
    while(bi->size > 0 && bi->data[bi->size-1] == 0) {
        bi->size --;
    }
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
    BigInt_RemoveLeadingZeros(bi);
}

// 相当于讲 十进制数 转换成 Base
void BigInt_FromInt(BigInt* bi, int v) {
    bi->size = 0;
    while(v > 0) {
        bi->data[bi->size++] = v % Base;
        v /= Base;
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

int BigInt_Compare(const BigInt* a, const BigInt* b) {
    if(a->size != b->size) {
        return a->size > b->size ? 1 : -1;
    }
    for(int i = a->size-1; i >= 0; --i) {
        if(a->data[i] != b->data[i]) {
            return a->data[i] > b->data[i] ? 1 : -1;
        }
    }
    return 0;
}

void BigInt_Add(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInit_Init(result);
    int i, carry = 0;
    for (i = 0; i < a->size || i < b->size || carry > 0; ++i) {
        if(i < a->size) carry += a->data[i];
        if(i < b->size) carry += b->data[i];
        // carry = 1002
        // data[i] = 2
        // carry = 1
        result->data[i] = carry % Base;
        carry /= Base;
    }
    result->size = i;
    BigInt_RemoveLeadingZeros(result);
}

void BigInt_Sub(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInit_Init(result);
    int carry = 0;
    result->size = a->size;
    for(int i = 0; i < result->size; ++i) {
        result->data[i] = a->data[i] - carry;
        if(i < b->size) {
            result->data[i] -= b->data[i];
        }
        if( result->data[i] < 0) {
            carry = 1;
            result->data[i] += Base;
        }else {
            carry = 0;
        }
    }
    BigInt_RemoveLeadingZeros(result);
}

void BigInt_Mul(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInit_Init(result);
    result->size = a->size + b->size;
    for(int i = 0; i < a->size; ++i) {
        int carry = 0;
        for(int j = 0; j < b->size; ++j){
            result->data[i+j] += a->data[i] * b->data[j];
            if(result->data[i+j] >= Base) {
                carry = result->data[i+j] / Base;
                result->data[i+j] %= Base;
            }else {
                carry = 0;
            }
        }
        result->data[i + b->size] += carry;
    }
    // result = 000 000 000 000
    BigInt_RemoveLeadingZeros(result);
}

void BigInt_MulInt(const BigInt* a, int v, BigInt* result) {
    BigInt temp;
    BigInt_FromInt(&temp, v);
    BigInt_Mul(a, &temp, result);
}

void BigInt_Div(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInit_Init(result);
    BigInt carry;
    BigInit_Init(&carry);
    int left, right, mid;

    for(int i = a->size - 1; i >= 0; --i) {
        // carry = carry * Base + a->data[i]
        BigInt temp, carry2, sum;
        // temp = carry * Base
        BigInt_MulInt(&carry, Base, &temp);
        // sum  = temp + a->data[i]
        BigInt_FromInt(&carry2, a->data[i]);
        BigInt_Add(&temp, &carry2, &sum);
        // carry = sum
        BigInit_Copy(&carry, &sum);
        // b * left <= carry
        left = -1;
        right = Base;
        while(left + 1 < right) {
            mid = (left + right) >> 1;
            BigInt product;
            BigInt_MulInt(b, mid, &product);
            if(BigInt_Compare(&product, &carry) <= 0) {
                left = mid;
            }else {
                right = mid;
            }
        }
        // result->data[i] = left;
        result->data[i] = left;
        // carry -= b * left;
        BigInt product, diff;
        // prod = b * left
        BigInt_MulInt(b, left, &product);
        // carry = carry - prod
        BigInt_Sub(&carry, &product, &diff);
        BigInit_Copy(&carry, &diff);
    }
    result->size = a->size;
    BigInt_RemoveLeadingZeros(result);
}


char s1[10010], s2[100010];
BigInt a, b, res;

int main() {
    scanf("%s %s", s1, s2);
    BigInt_FromString(&a, s1);
    BigInt_FromString(&b, s2);
    if( BigInt_Compare(&a, &b) < 0 ) {
        printf("-");
        BigInt_Sub(&b, &a, &res);
    }else {
        BigInt_Sub(&a, &b, &res);
    }
    
    BigInt_Print(&res, '\n');
    return 0;
}
