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


bool cur[9][9];
bool input[9][9];
vector<vector<int> > allCase;

int ans;

bool valid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 9; j++)
		{
			if (input[i][j] && !cur[i][j])
			{
				return false;
			}
		}
	}
	
	return true;
}

void dfs(vector<int> &path, int visited)
{
	if (path.size() >= 4)
	{
		//allCase.push_back(path);	
		if (valid())
		{
			ans++;
		}
	}
	
	int a, b, mid;
	for (int i = 0; i < 9; i++)
	{
		if (visited >> i & 1)
		{
			continue;
		}
		
		int pre = path.back();
		a = min(pre, i);
		b = max(pre, i);
		
		mid = (a + b) / 2;
		/*
		if (pre == 8 && i == 6)
		{
			
			bool hasMid = false;
			for (int k = 0; k < path.size(); k++)
			{
				if (path[k] == mid)
				{
					hasMid = true;
					break;
				}
			}
			if (!hasMid && visited >> mid != 0)
			{
				int forDebug = 2;
			}
		}*/
		int state = 0;
		bool pre1, pre2;
		if (a + 6 == b ||
			a % 3 == 0 && a + 2 == b ||
			a == 0 && b == 8 ||
			a == 2 && b == 6)
		{
			if (!(visited >> mid & 1))
			{
				continue;
			}
			/*
			pre1 = cur[a][mid];
			pre2 = cur[mid][b];
			cur[a][mid] = cur[mid][a] = true;
			cur[mid][b] = cur[b][mid] = true;*/
		}
		else
		{
			/*
			pre1 = cur[a][b];
			cur[a][b] = cur[b][a] = true;
			state = 1;*/
		}
		
		pre1 = cur[a][b];
		cur[a][b] = cur[b][a] = true;
		path.push_back(i);
		dfs(path, visited | 1 << i);
		path.pop_back();
		
		/*
		if (state)
		{
			cur[a][b] = cur[b][a] = pre1;
		}
		else
		{
			cur[a][mid] = cur[mid][a] = pre1;
			cur[b][mid] = cur[mid][b] = pre2;
		}*/
		cur[a][b] = cur[b][a] = pre1;
	}
}


void solve()
{
	int n, u, v;
	memset(cur, 0, sizeof(cur));
	memset(input, 0, sizeof(input));
	
	vector<int> path;
	ans = 0;
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v;
		u--;
		v--;
		input[u][v] = input[v][u] = true;
	}
	
	for (int i = 0; i < 9; i++)
	{
		path.push_back(i);
		dfs(path, 1 << i);
		path.pop_back();
	}
	
	
	cout << ans << endl;
}

void print(vector<int> &a)
{
	for (auto tmp : a)
	{
		cout << tmp;
	}
	cout << endl;
}

int mid[9][9];
void check()
{
	int i, j;
	bool visited[9];
	fill_n((int*)mid, 9*9, -1);
	mid[0][2] = mid[2][0] = 1;
	mid[3][5] = mid[5][3] = 4;
	mid[6][8] = mid[8][6] = 7;
	mid[0][6] = mid[6][0] = 3;
	mid[1][7] = mid[7][1] = 4;
	mid[2][8] = mid[8][2] = 5;
	mid[0][8] = mid[8][0] = 4;
	mid[2][6] = mid[6][2] = 4;
	for (i = 0; i < allCase.size(); i++)
	{
		auto &cur = allCase[i];
		if (cur.size() < 4 || cur.size() > 9)
		{
			printf("size=%d: ", cur.size());
			print(cur);
			exit(1);
		}
		
		memset(visited, 0, sizeof(visited));
		int pre = cur[0];
		visited[pre] = true;
		for (j = 1; j < cur.size(); pre = cur[j], j++)
		{
			if (visited[cur[j]])
			{
				printf("visited %d: ", cur[j]);
				print(cur);
				exit(2);
			}
			visited[cur[j]] = true;
			int c = mid[cur[j]][pre];
			if (c != -1 && !visited[c])
			{
				printf("pre=%d, cur=%d, c=%d: ", pre, cur[j], c);
				print(cur);
				exit(3);
			}
		}
	}
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
	
	//check();
	
	return 0;
}