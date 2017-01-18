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


int cur[9];
int input[9];
int mid[9][9];
bool visited[9];
int ans;

bool valid()
{
	for (int i = 0; i < 9; i++)
	{
		if ((input[i] & cur[i]) != input[i])
		{
			return false;
		}
	}
	
	return true;
}

void dfs(vector<int> &path)
{
	if (path.size() >= 4)
	{
		//allCase.push_back(path);	
		if (valid())
		{
			ans++;
		}
	}
	
	int c, preState1, preState2;
	for (int i = 0; i < 9; i++)
	{
		if (visited[i])
		{
			continue;
		}
		
		int pre = path.back();
		
		c = mid[pre][i];

		if (c != -1 && !visited[c])
		{
			continue;
		}
		
		
		preState1 = cur[pre];
		preState2 = cur[i];
		cur[i] |= 1 << pre;
		cur[pre] |= 1 << i;
		visited[i] = true;
		path.push_back(i);
		
		dfs(path);
		
		path.pop_back();
		visited[i] = false;
		cur[pre] = preState1;
		cur[i] = preState2;
	}
}


void solve()
{
	int n, u, v;
	memset(cur, 0, sizeof(cur));
	memset(input, 0, sizeof(input));
	memset(visited, 0, sizeof(visited));
	
	vector<int> path;
	ans = 0;
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v;
		u--;
		v--;
		input[u] |= 1 << v;
		input[v] |= 1 << u;
	}
	
	for (int i = 0; i < 9; i++)
	{
		path.push_back(i);
		visited[i] = true;
		dfs(path);
		visited[i] = false;
		path.pop_back();
	}
	
	
	cout << ans << endl;
}


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	fill_n((int*)mid, 9*9, -1);
	mid[0][2] = mid[2][0] = 1;
	mid[3][5] = mid[5][3] = 4;
	mid[6][8] = mid[8][6] = 7;
	mid[0][6] = mid[6][0] = 3;
	mid[1][7] = mid[7][1] = 4;
	mid[2][8] = mid[8][2] = 5;
	mid[0][8] = mid[8][0] = 4;
	mid[2][6] = mid[6][2] = 4;
	
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	
	return 0;
}