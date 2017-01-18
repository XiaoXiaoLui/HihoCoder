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

char a[150][150];
int n, m;
int d[150][150];
bool visit[150][150];

const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int i, j, k;
	cin >> n >> m;
	memset(a, '#', sizeof(a));
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			cin >> a[i][j];
		}
	}
	
	pii start;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (a[i][j] == 'H')
			{
				start = {i, j};
				d[i][j] = 0;
				visit[i][j] = true;
			}
		}
	}
	
	queue<pii> Q;
	Q.push(start);
	
	while (!Q.empty())
	{
		auto pos = Q.front();
		Q.pop();
		for (k = 0; k < 4; k++)
		{
			i = pos.first + DIR[k][0];
			j = pos.second + DIR[k][1];
			
			if ((a[i][j] == '.' || a[i][j] == 'S') && !visit[i][j])
			{
				d[i][j] = d[pos.first][pos.second] + 1;
				visit[i][j] = true;
				if (a[i][j] == '.')
				{
					Q.push({i, j});
				}
			}
		}
	}
	
	int ans = 1e9;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (a[i][j] == 'S' && visit[i][j])
			{
				for (k = 0; k < 4; k++)
				{
					int nextI = i + DIR[k][0];
					int nextJ = j + DIR[k][1];
					if (a[nextI][nextJ] == 'S' && visit[nextI][nextJ])
					{
						ans = min(ans, d[i][j] + d[nextI][nextJ]);
					}
				}
			}
			
		}
	}
	
	if (ans < 1e9)
	{
		cout << ans << endl;
	}
	else
	{
		cout <<  "Hi and Ho will not have lunch." << endl;
	}
	
	return 0;
}