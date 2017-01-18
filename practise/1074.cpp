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
pii minSt[N][22];
pii maxSt[N][22];
int lg[N];
bool use[N];

pii queryMin(int left, int right)
{
	int len = right - left + 1;
	int k = lg[len];
	
	return min(minSt[left][k], minSt[right - (1 << k) + 1][k]);
}

pii queryMax(int left, int right)
{
	int len = right - left + 1;
	int k = lg[len];
	return max(maxSt[left][k], maxSt[right - (1 << k) + 1][k]);
}

void solve(int left, int right)
{
	use[left] = use[right] = true;
	if (left == right)
	{
		return;
	}
	
	int low, high;
	vector<int> mid;
	low = min(a[left], a[right]);
	high = max(a[left], a[right]);
	pii minValue = queryMin(left, right);
	pii maxValue = queryMax(left, right);
	
	if (minValue.first < low)
	{
		mid.push_back(minValue.second);
	}
	
	if (maxValue.first > high)
	{
		mid.push_back(maxValue.second);
	}
	
	sort(mid.begin(), mid.end());
	if (mid.size() == 1)
	{
		solve(left, mid[0]);
		solve(mid[0], right);
	}
	else if (mid.size() == 2)
	{
		solve(left, mid[0]);
		solve(mid[0], mid[1]);
		solve(mid[1], right);
	}
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, i, j;
	cin >> n;
	for (i = 1; i <= n ; i++)
	{
		cin >> a[i];
		minSt[i][0] = {a[i], i};
		maxSt[i][0] = {a[i], i};
	}
	
	lg[1] = 0;
	for (i = 2; i < N; i++)
	{
		lg[i] = lg[i >> 1] + 1;
	}
	
	for (j = 1; j <= lg[n]; j++)
	{
		int len = 1 << j;
		for (i = 1; i + len - 1<= n; i++)
		{
			minSt[i][j] = min(minSt[i][j - 1], minSt[i + len / 2][j - 1]);
			maxSt[i][j] = max(maxSt[i][j - 1], maxSt[i + len / 2][j - 1]);
		}
	}
	
	solve(1, n);
	vector<int> ans;
	for (i = 1; i <= n; i++)
	{
		if (use[i])
		{
			ans.push_back(i);
		}
	}
	cout << ans.size() << endl;
	for (i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
	
	return 0;
}