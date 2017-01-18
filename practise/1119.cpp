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

const int N = 206;
const int UNKNOWN = -1;
const int BOMB = -2;
const int SAFE = -3;

int a[N][N];
int ans[N][N];

const int DIR[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}

bool valid(int i, int j, int n, int m)
{
    return (i > 0 && i <= n && j > 0 && j <= m);
}

int countUnknown(int i, int j, int n, int m)
{
    int ii, jj, k;
    for (k = 0; k < 8; k ++)
    {
        ii = i + DIR[k][0];
        jj = j + DIR[k][1];
    }
}

void solve()
{
    int i, j, ii, jj, k, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            ans[i][j] = a[i][j];
        }
    }
    
    // rule 1
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (a[i][j] == 0)
            {
                for (k = 0; k < 8; k++)
                {
                    ii = i + DIR[k][0];
                    jj = j + DIR[j][0];
                    if (valid(ii, jj, n, m))
                    {
                        ans[ii][jj] = SAFE;
                    }
                }
            }
        }
    }
    
    // rule 2
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            
        }
    }
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