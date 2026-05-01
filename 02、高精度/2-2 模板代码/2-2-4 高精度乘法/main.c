#include <stdio.h>
#include <string.h>

#define Base 1000
#define Capacity 100

typedef struct {
    int m_data[Capacity];
    int m_size;
} BigInt;

void BigInt_Init(BigInt* bi) {
    bi->m_size = 0;
    memset(bi->m_data, 0, sizeof(bi->m_data));
}

void BigInt_Copy(BigInt* dest, const BigInt* src) {
    dest->m_size = src->m_size;
    memcpy(dest->m_data, src->m_data, sizeof(src->m_data));
}

void BigInt_FromString(BigInt* bi, const char s[]) {
    int b = 1;
    bi->m_size = 0;
    bi->m_data[bi->m_size] = 0;
    for (int i = strlen(s) - 1; i >= 0; --i) {
        bi->m_data[bi->m_size] += (s[i] - '0') * b;
        b *= 10;
        if (b >= Base) {
            b = 1;
            bi->m_size++;
            bi->m_data[bi->m_size] = 0;
        }
    }
    if (bi->m_data[bi->m_size] > 0) {
        bi->m_size++;
    }
}

void BigInt_Print(const BigInt* bi, char end) {
    if (bi->m_size == 0) {
        printf("0");
    } else {
        printf("%d", bi->m_data[bi->m_size - 1]);
        for (int i = bi->m_size - 2; i >= 0; --i) {
            for (int j = Base / 10; j > 0; j /= 10) {
                printf("%d", (bi->m_data[i] / j) % 10);
            }
        }
    }
    printf("%c", end);
}

int BigInt_Compare(const BigInt* a, const BigInt* b) {
    if (a->m_size != b->m_size) {
        return a->m_size > b->m_size ? 1 : -1;
    }
    for (int i = a->m_size - 1; i >= 0; --i) {
        if (a->m_data[i] != b->m_data[i]) {
            return a->m_data[i] > b->m_data[i] ? 1 : -1;
        }
    }
    return 0;
}

void BigInt_Add(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInt_Init(result);
    int i, carry = 0;
    for (i = 0; i < a->m_size || i < b->m_size || carry > 0; i++) {
        if (i < a->m_size) carry += a->m_data[i];
        if (i < b->m_size) carry += b->m_data[i];
        result->m_data[i] = carry % Base;
        carry /= Base;
    }
    result->m_size = i;
}

void BigInt_Sub(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInt_Init(result);
    int carry = 0;
    result->m_size = a->m_size;
    for (int i = 0; i < result->m_size; ++i) {
        result->m_data[i] = a->m_data[i] - carry;
        if (i < b->m_size) {
            result->m_data[i] -= b->m_data[i];
        }
        if (result->m_data[i] < 0) {
            carry = 1;
            result->m_data[i] += Base;
        } else {
            carry = 0;
        }
    }
    while (result->m_size > 0 && result->m_data[result->m_size - 1] == 0) {
        result->m_size--;
    }
}

void BigInt_Mul(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInt_Init(result);
    result->m_size = a->m_size + b->m_size;
    for (int i = 0; i < result->m_size; ++i) {
        result->m_data[i] = 0;
    }
    for (int i = 0; i < a->m_size; ++i) {
        int carry = 0;
        for (int j = 0; j < b->m_size; ++j) {
            result->m_data[i + j] += a->m_data[i] * b->m_data[j] + carry;
            if (result->m_data[i + j] >= Base) {
                carry = result->m_data[i + j] / Base;
                result->m_data[i + j] %= Base;
            } else {
                carry = 0;
            }
        }
        result->m_data[i + b->m_size] += carry;
    }
    while (result->m_size > 0 && result->m_data[result->m_size - 1] == 0) {
        result->m_size--;
    }
}

int main() {
    char s1[100], s2[100];
    while (scanf("%s %s", s1, s2) != EOF) {
        BigInt a, b, res;
        BigInt_Init(&a);
        BigInt_Init(&b);
        BigInt_FromString(&a, s1);
        BigInt_FromString(&b, s2);
        BigInt_Mul(&a, &b, &res);
        BigInt_Print(&res, '\n');
    }
    return 0;
}
