// include stdc++.h slows down compilation much.
//#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
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

// Aho-Corosick
struct Trie
{
	Trie()
	{
		createNode();
	}
	
	void add(const string &s)
	{
		int u, i;
		for (i = 0, u = 0; i < s.size(); i++)
		{
			if (!tr[u][s[i] - 'a'])
			{
				tr[u][s[i] - 'a'] = createNode();
			}
			u = tr[u][s[i] - 'a'];
		}
		info[u] = 1;
	}
	
	void build()
	{
		queue<int> Q;
		Q.push(0);
		
		int u, v;
		while (!Q.empty())
		{
			u = Q.front();
			Q.pop();
			for (int i = 0; i < M; i++)
			{
				v = tr[u][i];
				if (v)
				{
					if (u)
					{
						next[v] = tr[next[u]][i];
					}
					Q.push(v);
				}
				else
				{
					tr[u][i] = tr[next[u]][i];
				}
			}
		}
	}
	
	bool find(const string &s)
	{
		int u = 0;
		for (int i = 0; i < s.size(); i++)
		{
			u = tr[u][s[i] - 'a'];
			if (info[u])
			{
				return true;
			}
		}
		return false;
	}
	
private:
	int createNode()
	{
		tr.push_back(vector<int>(M, 0));
		next.push_back(0);
		info.push_back(0);
		return info.size() - 1;
	}
	vector<vector<int> > tr;
	vector<int> next;
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
	Trie tr;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> s;
		tr.add(s);
	}
	
	cin >> s;
	
	tr.build();
	bool ret = tr.find(s);
	if (ret)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	return 0;
}