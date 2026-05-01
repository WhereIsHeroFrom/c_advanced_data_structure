#include <stdio.h>
#include <string.h>

#define Base 1000
#define Capacity 1700

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

void BigInt_FromInt(BigInt* bi, int v) {
    bi->m_size = 0;
    while (v > 0) {
        bi->m_data[bi->m_size++] = v % Base;
        v /= Base;
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

void BigInt_MulInt(const BigInt* a, int v, BigInt* result) {
    BigInt temp;
    BigInt_FromInt(&temp, v);
    BigInt_Mul(a, &temp, result);
}

void BigInt_Div(const BigInt* a, const BigInt* b, BigInt* result) {
    BigInt_Init(result);
    BigInt carry;
    BigInt_Init(&carry);
    int left, right, mid;

    for (int i = a->m_size - 1; i >= 0; --i) {
        BigInt temp, carry2, sum;
        BigInt_MulInt(&carry, Base, &temp);
        BigInt_FromInt(&carry2, a->m_data[i]);
        BigInt_Add(&temp, &carry2, &sum);
        BigInt_Copy(&carry, &sum);

        left = -1;
        right = Base;
        while (left + 1 < right) {
            mid = (left + right) / 2;
            BigInt product;
            BigInt_MulInt(b, mid, &product);
            if (BigInt_Compare(&product, &carry) <= 0) {
                left = mid;
            } else {
                right = mid;
            }
        }

        result->m_data[i] = left;
        BigInt product, diff;
        BigInt_MulInt(b, left, &product);
        BigInt_Sub(&carry, &product, &diff);
        BigInt_Copy(&carry, &diff);
    }

    result->m_size = a->m_size;
    while (result->m_size > 0 && result->m_data[result->m_size - 1] == 0) {
        result->m_size--;
    }
}

int main() {
    char s1[5010], s2[5010];
    while (scanf("%s %s", s1, s2) != EOF) {
        BigInt a, b, res;
        BigInt_Init(&a);
        BigInt_Init(&b);
        BigInt_FromString(&a, s1);
        BigInt_FromString(&b, s2);
        BigInt_Div(&a, &b, &res);
        BigInt_Print(&res, '\n');
    }
    return 0;
}
