// include stdc++.h slows down compilation much.
//#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

#define USE_IOSTREAM \
{\
	ios::sync_with_stdio(false);\
	cin.tie(0);\
	cout.tie(0);\
}

#define pii pair<int, int>
#define mp make_pair

typedef long long ll;

const int N = 2e4 + 100;

vector<int> in[N];
vector<int> out[N];
bool visit[N];
int com[N];
vector<int> path;


void dfs1(int u)
{
    visit[u] = true;
    for (auto v : out[u])
    {
        if (!visit[v])
        {
            dfs1(v);
        }
    }
    
    path.push_back(u);
}

void dfs2(int u, int c)
{
    com[u] = c;
    for (auto v : in[u])
    {
        if (!com[v])
        {
            dfs2(v, c);
        }
    }
}

void targin(int n)
{
    int i, u, v;
    for (u = 1; u <= 2*n; u++)
    {
        if (!visit[u])
        {
            dfs1(u);
        }
    }
    
    int c = 0;
    for (i = path.size() - 1; i >= 0; i--)
    {
        u = path[i];
        if (!com[u])
        {
            dfs2(u, ++c);
        }
    }
}

void init()
{
    int i;
    for (i = 0; i < N; i++)
    {
        in[i].clear();
        out[i].clear();
    }
    path.clear();
    
    memset(visit, 0, sizeof(visit));
    memset(com, 0, sizeof(com));
}

void addEdge(int u, int v)
{
    out[u].push_back(v);
    in[v].push_back(u);
}

void add(int u, int v, int s)
{
    u = 2*u + s;
    v = 2*v + s;
    
    addEdge(u, v ^ 1);
    addEdge(v, u ^ 1);
}

void solve()
{
    init();
    int n, m, i, u, v, s;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &s);
        add(u, v, s);
    }
    
    targin(n);
    for (i = 1; i <= n; i++)
    {
        if (com[2*i] == com[2*i + 1])
        {
            printf("No\n");
            return;
        }
    }
    
    printf("Yes\n");
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
	
	return 0;
}