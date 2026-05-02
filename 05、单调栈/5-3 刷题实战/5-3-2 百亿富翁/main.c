
#include <stdio.h>

/////////////////////////////单调栈模板/////////////////////////////
#define type int
#define maxn 700001
#define inf 2000000000
typedef int (* cmp_t)(type a, type b);

typedef struct {
    int data[maxn];
    int top;
} MonotonicStack;

// <  单调递增栈(栈底->栈顶)：inf 1 2 3 4 5
int cmpLT(type a, type b) {
    return a < b;
}
// <= 单调不减栈(栈底->栈顶)：inf 2 2 3 3 4
int cmpLE(type a, type b) {
    return a <= b;
}
// >  单调递减栈(栈底->栈顶)：inf 6 5 4 3 2
int cmpGT(type a, type b) {
    return a > b;
}
// >= 单调不增栈(栈底->栈顶): inf 6 6 5 4 3
int cmpGE(type a, type b) {
    return a >= b;
}

// ans[i] 代表从 i 往左找，找到的第一个满足 cmp(h[x], h[i]) 的下标 x
void findFirstMeetOnLeft(MonotonicStack* stk, 
    int n, type h[], int ans[], cmp_t cmp) {
    h[0] = inf;
    stk->top = 0;
    stk->data[stk->top++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (!cmp(h[stk->data[stk->top - 1]], h[i])) {
            stk->top--;
        }
        ans[i] = stk->data[stk->top - 1];
        stk->data[stk->top++] = i;
    }
}
/////////////////////////////单调栈模板/////////////////////////////

MonotonicStack stk;
type h[maxn];
int ans[maxn];



void reverseArray(int n, int arr[]) {
    for (int i = 1; i <= n / 2; ++i) {
        int tmp = arr[i];
        arr[i] = arr[n + 1 - i];
        arr[n + 1 - i] = tmp;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    findFirstMeetOnLeft(&stk, n, h, ans, cmpGT);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) ans[i] = -1;
        printf("%d ", ans[i]);
    }
    printf("\n");
    reverseArray(n, h);
    findFirstMeetOnLeft(&stk, n, h, ans, cmpGT);
    reverseArray(n, ans);
    reverseArray(n, h);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) ans[i] = -1;
        else ans[i] = (n + 1) - ans[i];
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}