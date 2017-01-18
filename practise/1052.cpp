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

int cnt[26];

void solve()
{
	int k, i, j, sum, maxCnt;
	string s;
	
	cin >> s;
	cin >> k;
	
	if (k == s.size())
	{
		cout << 0 << endl;
		return;
	}
	
	int interLen = max(0, 2*k - (int)s.size());
	
	int offset = s.size() - k;
	int ans = 0;
	for (i = 0; i < k - interLen; i++)
	{
		memset(cnt, 0, sizeof(cnt));
		sum = 0;
		maxCnt = 0;
		for (j = i; j < s.size(); j += offset)
		{
			cnt[s[j] - 'A']++;
			sum++;
			maxCnt = max(maxCnt, cnt[s[j] - 'A']);
			
			if (j >= k)
			{
				break;
			}
		}

		ans += sum - maxCnt;
	}
	
	cout << ans << endl;
}

int main()
{
	USE_IOSTREAM;
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