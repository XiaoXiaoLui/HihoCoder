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

#define pii pair<int, int>
#define mp make_pair

typedef long long ll;


int dfs(int a, int b, string &res)
{
	if (a == 0)
	{
		return 0;
	}
	else if (b == 0)
	{
		return 1;
	}
	
	if (a <= b)
	{
		res.push_back('1');
		return dfs(a, b - a, res);
	}
	else
	{
		res.push_back('0');
		return dfs(a - b, b, res);
	}
}

pii gcd(int a, int b)
{
	int c;
	int cnt = 0;
	while (b)
	{
		c = b;
		cnt += a / b;
		b = a % b;
		a = c;
	}
	
	return {a, cnt};
}

void solve(int n, string &res)
{
	int tryNum;
	pii tmp;
	
	int mid = max(1, (int) (0.618 *n));
	for (int i = 0; true; i++)
	{
		bool ok = false;
		if (mid - i >= 1)
		{
			tryNum = mid - i;
			tmp = gcd(tryNum, n);
			if (tmp.first == 1 && tmp.second <= 60)
			{
				ok = true;
			}
		}
		
		if (!ok && mid + i < n)
		{
			tryNum = mid + i;
			tmp = gcd(tryNum, n);
			if (tmp.first == 1 &&  tmp.second <= 60)
			{
				ok = true;
			}
		}
		
		if (!ok)
		{
			continue;
		}
		
		res.clear();
		int ret = dfs(tryNum, n, res);
		reverse(res.begin(), res.end());
		if (ret)
		{
			for (int i = 0; i < res.size(); i++)
			{
				if (res[i] == '0')
				{
					res[i] = '1';
				}
				else
				{
					res[i] = '0';
				}
			}
		}
		break;
	}
}


int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, t;
	string s;
	cin >> t;
	while (t--)
	{
		cin >> n;
		solve(n, s);
		cout << s << endl;
	}
	
	return 0;
}