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
#include <cstring>

using namespace std;

#define USE_IOSTREAM \
{\
	ios::sync_with_stdio(false);\
	cin.tie(0);\
	cout.tie(0);\
}

typedef long long ll;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair



const ll MOD = 1e9 + 7;

// dp[i][sum][greater]
static pll dp[30][300][2];

vector<int> numToVec(ll maxNumber)
{
	vector<int> res;
	res.push_back(0); // just to make 1 base array
	do
	{
		res.push_back(maxNumber % 10);
		maxNumber /= 10;
	} while (maxNumber);
	
	//reverse(res.begin(), res.end());
	return res;
}

ll solve(ll maxNumber, int fx)
{
	if (maxNumber <= 0)
	{
		return 0;
	}
	
	const static int OFFSET = 150;

	memset(dp, 0, sizeof(dp));
	vector<int> vec = numToVec(maxNumber);
	
	int i, j, k, r, nr;
	ll exp = 1;
	dp[0][0 + OFFSET][0].second = 1;
	ll ans = 0;
	for (i = 1; i < vec.size(); i++, exp = exp * 10 % MOD)
	{
		for (j = -100; j <= 100; j++)
		{
			for (r = 0; r < 2; r++)
			{
				for (k = 0; k <= 9; k++)
				{
					int nextJ = -j + k;
					nr = k == vec[i] ? r : k > vec[i];
					pll &cur = dp[i][nextJ + OFFSET][nr];
					pll &pre = dp[i - 1][j + OFFSET][r];
					cur.second = (cur.second + pre.second) % MOD;
					cur.first = (cur.first + pre.first + exp * pre.second % MOD * k) % MOD;
					
					if (k != 0 && fx == nextJ)
					{
						if (!nr || i + 1 < vec.size())
						{
							ans = (ans + pre.first +  exp * pre.second % MOD * k) % MOD;
						}
					}
				}
			}
		}
	}
	
	
	return ans;
}

ll testFun(ll maxNumber, int fx)
{
	ll ans = 0;
	for (ll i = 0; i <= maxNumber; i++)
	{
		ll tmp = i;
		int cnt = 0;
		int sum = 0;
		int mul = 1;
		while (tmp)
		{
			sum += tmp % 10 * mul;
			tmp /= 10;
			cnt++;
			mul *= -1;
		}
		if (cnt % 2 == 0)
		{
			sum *= -1;
		}
		
		if (fx == sum)
		{
			ans = (ans + i) % MOD;
		}
	}
	
	return ans;
}

void test()
{
	const ll M = 1e4;
	ll l, r;
	int fx;
	for (int i = 0; i < 1e5; i++)
	{
		r = rand() % M + 1;
		l = rand() % r;
		fx = rand() % 100;
		if (rand() % 2)
		{
			fx *= -1;
		}
		
		ll ret1 = (testFun(r, fx) - testFun(l - 1, fx) + MOD) % MOD;
		ll ret2 = (solve(r, fx) - solve(l - 1, fx) + MOD) % MOD;
		if (ret1 != ret2)
		{
			printf("i=%d, l=%lld, r=%lld, fx=%d, ret1=%lld, ret2=%lld\n", i, l, r, fx, ret1, ret2);
			exit(1);
		}
	}
	exit(2);
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	//test();
	
	ll l, r, k;
	cin >> l >> r >> k;
	ll ans = solve(r, k);
	if (l > 0)
	{
		ans = (ans - solve(l - 1, k) + MOD) % MOD;
	}
	cout << ans << endl;
	
	return 0;
}