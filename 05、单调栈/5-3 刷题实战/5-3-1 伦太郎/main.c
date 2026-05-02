/*
学生们的视线会被不比自己身高低的人挡住
           会被 >= 自己身高的人挡住
           只要 < 自己身高，就是可以看到的
对于 h[i] 往左扫描
找到第一个 >= h[i] 的数的位置
举个例子
   i     0   1 2 3 4 5 6 7
  h[i]  inf  2 6 5 4 4 3 5  

对于 h[7] 的值等于 5
而 h[3] 是第一个 >= 5 的数的位置
所以 ans[7] = 3
所以 7 号这个人能够看到的就是中间的这三个人
7号能够看到的人数 = 7 - ans[7] - 1
*/


#include <stdio.h>

/////////////////////////////单调栈模板/////////////////////////////
#define type int
#define maxn 100001
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

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    findFirstMeetOnLeft(&stk, n, h, ans, cmpGE);
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        ret += i - ans[i] - 1;
    }
    printf("%d\n", ret);
    return 0;
}