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

const int N = 300;
vector<int> out[N];
vector<int> in[N];
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
    int i;
    for (i = 2; i <= 2*n; i++)
    {
        if (!visit[i])
        {
            dfs1(i);
        }
    }
    
    int u;
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
        visit[i] = false;
        com[i] = 0;
    }
    path.clear();
}

int getVertex(const char *str)
{
    int u = atoi(str + 1) * 2;
    if (str[0] == 'h')
    {
        u++;
    }
    return u;
}

void add(int u, int v)
{
    out[u ^ 1].push_back(v);
    in[v].push_back(u ^ 1);
    out[v ^ 1].push_back(u);
    in[u].push_back(v ^ 1);
}

void solve()
{
    init();
    int n, m, u, v, i;
    scanf("%d%d", &n, &m);
    
    char str[10];
    for (i = 1; i <= m; i++)
    {
        scanf("%s", str);
        u = getVertex(str);
        scanf("%s", str);
        v = getVertex(str);
        add(u, v);
    }
    
    targin(n);
    
    bool ok = true;
    for (i = 1; i <= n; i++)
    {
        if (com[2*i] == com[2*i + 1])
        {
            ok = false;
            break;
        }
    }
    
    if (ok)
    {
        printf("GOOD\n");
    }
    else
    {
        printf("BAD\n");
    }
}

int main()
{
	USE_IOSTREAM;
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