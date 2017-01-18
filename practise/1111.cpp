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

const int N = 1e6 + 100;
const ll MOD = 1e9 + 7;

// preCal[i], number of different partitions : partition i equal elements to order pairs
// preCal[n] = 2^(n/2) * C(n, 2) * C(n - 2, 2) *... / Permutation(n / 2)
// preCal[n] = 2*preCal[n - 2] * C(n, 2) / (n / 2) = preCal[n - 2] * (n - 1)
ll preCal[N];

void solve()
{
    int n, i, w;
    scanf("%d", &n);
    multiset<ll> S;
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &w);
        S.insert(w);
    }
    
    ll res = 1;
    while (S.size() > 1)
    {
        ll w = *S.begin();
        int num = S.count(w);
        if (num == 1)
        {
            S.erase(S.begin());
            ll v = *S.begin();
            num = S.count(v);
           
            S.erase(S.begin());
            S.insert(w + v);
            
            res = res * num * 2 % MOD;
            continue;
        }
        
        res = res * preCal[num] % MOD;
        S.erase(w);
        for (i = 1; i <= num / 2; i++)
        {
            S.insert(2 * w);
        }
        
        if (num & 1)
        {
            S.insert(w);
        }
    }
    
    printf("%lld\n", res);
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int i = 0;
    preCal[0] = preCal[1] = 1;
    for (i = 2; i < N; i++)
    {
        preCal[i] = preCal[i - 2] * (((ll)i * (i - 1)) / (i / 2)) % MOD;
    }
    
    int t;
    scanf("%d", &t);
    
    while (t--)
    {
        solve();
    }
	
	return 0;
}