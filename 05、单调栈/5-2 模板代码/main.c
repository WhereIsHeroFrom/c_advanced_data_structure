#include <stdio.h>

/////////////////////////////单调栈模板/////////////////////////////
#define maxn 100001
#define type int
#define inf 2000000000

typedef struct {
    int data[maxn];
    int top;
} MonotonicStack;

MonotonicStack stk;
// <  单调递增栈(栈底->栈顶)：inf 1 2 3 4 5
// <= 单调不减栈(栈底->栈顶)：inf 2 2 3 3 4
// >  单调递减栈(栈底->栈顶)：inf 6 5 4 3 2
// >= 单调不增栈(栈底->栈顶): inf 6 6 5 4 3
int cmp(int a, int b) {
    return a > b;
}

// ans[i] 代表从 i 往左找，找到的第一个满足 cmp(h[x], h[i]) 的下标 x
void findFirstMeetOnLeft(int n, type h[], int ans[]) {
    h[0] = inf;
    stk.top = 0;
    stk.data[stk.top++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (!cmp(h[stk.data[stk.top - 1]], h[i])) {
            stk.top--;
        }
        ans[i] = stk.data[stk.top - 1];
        stk.data[stk.top++] = i;
    }
}
/////////////////////////////单调栈模板/////////////////////////////

type h[maxn];
int ans[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    findFirstMeetOnLeft(n, h, ans);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}

/*
10
2 1 4 2 1 1 3 3 2 2
0 1 0 3 4 4 3 3 8 8
*/