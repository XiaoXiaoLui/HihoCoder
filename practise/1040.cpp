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



int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	map<pii, vector<pii> > mm;
	
	int t, x1, y1, x2, y2, i, x0, y0;
	cin >> t;
	while (t--)
	{
		mm.clear();
		bool ok = true;
		for (i = 0; i < 4; i++)
		{
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 == x2 && y1 == y2)
			{
				ok = false;
			}
			mm[{x1, y1}].push_back({x2, y2});
			mm[{x2, y2}].push_back({x1, y1});
		}
		
		if (mm.size() != 4)
		{
			ok = false;
		}
		
		for (auto tmp : mm)
		{
			if (tmp.second.size() != 2)
			{
				ok = false;
				break;
			}
			
			x0 = tmp.first.first;
			y0 = tmp.first.second;
			x1 = tmp.second[0].first;
			y1 = tmp.second[0].second;
			x2 = tmp.second[1].first;
			y2 = tmp.second[1].second;
			
			ll pro = (ll)(x1 - x0) * (x2 - x0) + (ll)(y1 - y0) * (y2 - y0);
			if (pro)
			{
				ok = false;
				break;
			}
		}
		
		if (!ok)
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << "YES" << endl;
		}
		
	}
	return 0;
}