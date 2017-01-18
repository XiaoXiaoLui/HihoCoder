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

struct Dsu
{
	Dsu(int n)
	{
		for (int i = 0; i <= n; i++)
		{
			a.push_back(i);
		}
	}
	
	int find(int u)
	{
		if (a[u] == u)
		{
			return u;
		}
		return a[u] = find(a[u]);
	}
	
	void merge(int u, int v)
	{
		int pu = find(u);
		int pv = find(v);
		a[pu] = pv;
	}
private:
	vector<int> a;
};


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, op, num, u, v;
	string name1, name2;
	map<string, int> hash;
	
	cin >> n;
	num = 0;
	Dsu dsu(2 * n + 10);
	while (n--)
	{
		cin >> op >> name1 >> name2;
		if (hash.count(name1) == 0)
		{
			hash[name1] = ++num;
		}
		if (hash.count(name2) == 0)
		{
			hash[name2] = ++num;
		}
		
		u = hash[name1];
		v = hash[name2];
		
		if (op == 0)
		{
			dsu.merge(u, v);
		}
		else
		{
			int pu = dsu.find(u);
			int pv = dsu.find(v);
			if (pu == pv)
			{
				cout << "yes" << endl;
			}
			else
			{
				cout << "no" << endl;
			}
		}
	}
	
	return 0;
}