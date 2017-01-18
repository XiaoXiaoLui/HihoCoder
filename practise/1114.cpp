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
int a[N];
int ans[2][N];
bool valid[2];

void solve()
{
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    
    for (j = 0; j < 2; j++)
    {
        valid[j] = true;
        ans[j][0] = 0;
        ans[j][1] = j;
        for (i = 1; i <= n; i++)
        {
            ans[j][i + 1] = a[i] - ans[j][i - 1] - ans[j][i];
            if (ans[j][i + 1] != 0 && ans[j][i + 1] != 1 ||
                i == n && ans[j][i + 1] != 0)
            {
                valid[j] = false;
                break;
            }
        }
    }
    
    
    vector<int> bombPos;
    vector<int> safePos;
    if (valid[0] && valid[1])
    {
        for (i = 1; i <= n; i++)
        {
            if (ans[0][i] == ans[1][i])
            {
                if (ans[0][i])
                {
                    bombPos.push_back(i);
                }
                else
                {
                    safePos.push_back(i);
                }
            }
        }
    }
    else 
    {
        int *p = valid[0] ? (int*)&ans[0] : (int*)&ans[1];
        for (i = 1; i <= n; i++)
        {
            if (p[i])
            {
                bombPos.push_back(i);
            }
            else
            {
                safePos.push_back(i);
            }
        }
    }
    
    printf("%d ", bombPos.size());
    for (auto tmp : bombPos)
    {
        printf("%d ", tmp);
    }
    printf("\n%d ", safePos.size());
    for (auto tmp : safePos)
    {
        printf("%d ", tmp);
    }
    printf("\n");
    
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
	
	return 0;
}