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

const int INF = 1e9;


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, m, i;
	cin >> n >> m;
	string webStr;
	bool bInSet;
	set<pair<int, string>, greater<pair<int, string> > > S;
	map<string, int> dict;
	for (i = 1; i <= n; i++)
	{
		cin >> webStr;
		bInSet = false;
		auto iter = S.find({dict[webStr], webStr});
		if (iter != S.end() && iter->second == webStr)
		{
			S.erase(iter);
			bInSet = true;
		}
		
		if (S.size() >= m)
		{
			S.erase(--S.end());
		}
		
		S.insert({i, webStr});
		dict[webStr] = i;
		
		if (bInSet)
		{
			cout << "Cache" << endl;
		}
		else
		{
			cout << "Internet" << endl;
		}
	}
	
	return 0;
}