#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10001;

int top;
int Stack[MAXN];
bool vis[MAXN];

int dfn[MAXN], low[MAXN];
int Bcnt, Dindex;
vector<int> ve[MAXN];

void init() {
    Bcnt = Dindex = top = 0;
    memset(dfn, -1, sizeof dfn);
    memset(vis, false, sizeof vis);
    for (int i = 1; i < MAXN; ++i) ve[i].clear();
}

void tarjan(int u) {
    int v = 0;
    dfn[u] = low[u] = ++Dindex;
    vis[u] = true;
    Stack[++top] = u;
    int t = ve[u].size();
    for (int i = 0; i < t; ++i) {
        v = ve[u][i];
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        Bcnt++;
        do {
            v = Stack[top--];
            vis[v] = false;
        } while (u != v);
    }
} 

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (m == 0 && n == 0) break;
        init();
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            ve[a].push_back(b); 
        }
        for (int i = 1; i <= n; ++i) 
            if (dfn[i] == -1) tarjan(i);
        printf("%d\n",Bcnt);
    } 
    return 0;
}
