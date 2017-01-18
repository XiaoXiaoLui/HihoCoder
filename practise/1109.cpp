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

const int N = 1e5 + 100;
const int INF = 2e9;

vector<pii> graph[N];
int d[N];
int used[N];

int prim(int n)
{
    set<pii> S;
    fill_n(d, N, INF);
    memset(used, 0, sizeof(used));
    
    d[1] = 0;
    S.insert({0, 1});
    
    int res = 0;
    while (!S.empty())
    {
        int u = S.begin()->second;
        S.erase(S.begin());
        
        res += d[u];
        used[u] = true;
        for (auto e : graph[u])
        {
            int v = e.first;
            int w = e.second;
            if (used[v])
            {
                continue;
            }
            
            if (w < d[v])
            {
                auto iter = S.find({d[v], v});
                if (iter != S.end())
                {
                    S.erase(iter);
                }
                
                d[v] = w;
                S.insert({d[v], v});
            }
        }
    }
    
    return res;
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int n, m, i, u, v, w;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
	
    int ret = prim(n);
    printf("%d\n", ret);
    
	return 0;
}