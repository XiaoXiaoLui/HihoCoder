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

struct Trie
{
	Trie()
	{
		createNode();
	}
	
	void add(const string &s)
	{
		int u = 0;
		for (int i = 0; i < s.size(); i++)
		{
			info[u]++;
			int &v = tr[u][s[i] - 'a'];
			if (!v)
			{
				v = createNode();
			}
			u = v;
		}
		info[u]++;
	}
	
	int find(const string &s)
	{
		int u = 0;
		for (int i = 0; i < s.size(); i++)
		{
			u = tr[u][s[i] - 'a'];
			if (!u)
			{
				break;
			}
		}
		
		if (!u)
		{
			return 0;
		}
		else
		{
			return info[u];
		}
	}
private:
	int createNode()
	{
		tr.push_back(vector<int>(M, 0));
		info.push_back(0);
		return tr.size() - 1;
	}
	
	vector<vector<int> > tr;
	vector<int> info;
	const static int M = 26;
};

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, m, i;
	string s;
	cin >> n;
	Trie tr;
	for (i = 1; i <= n; i++)
	{
		cin >> s;
		tr.add(s);
	}
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> s;
		int ret = tr.find(s);
		cout << ret << endl;
	}
	
	return 0;
}