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

const int N = 1e6 + 100;
const ll LINF = 1e17;

int c0[N];
int c1[N];
vector<pii> graph[N];
bool needVisit[N];

// fp[vertex][hasCar]
ll fp[N][2];

// fc[vertex][hasCar][hasCarBack]  hasCarBack valid only when hasCar = 1
ll fc[N][2][2]; 

void dfs(int u, int pre)
{
	int i, v, minIdx = 0;
	ll sum, minDiffCar10, minDiffNoCar, minDiffCarPath, minDiff1, minDiff2;
	sum = 0;
	minDiffCar10 = minDiffNoCar = minDiffCarPath = minDiff1 = minDiff2 = LINF;
	bool isLeaf = true;
	for (i = 0; i < graph[u].size(); i++)
	{
		v = graph[u][i].first;
		if (v != pre)
		{
			dfs(v, u);
			needVisit[u] |= needVisit[v];
			
			if (needVisit[v])
			{
				isLeaf = false;
				int idx = graph[u][i].second;
				ll tmp = fc[v][0][0] + 2*c0[idx];
				fc[u][0][0] += tmp;
				minDiffNoCar = min(minDiffNoCar, -tmp + c0[idx] + fp[v][0]);
				
				tmp = min(fc[v][1][1] + 2*c1[idx], fc[v][0][0] + 2*c0[idx]);
				sum += tmp;
				minDiffCar10 = min(minDiffCar10, -tmp + c0[idx] + c1[idx] + min(fc[v][1][1], fc[v][1][0]));
				
				minDiffCarPath = min(minDiffCarPath, -tmp + min(c0[idx] + fp[v][0], c1[idx] + fp[v][1]));
				
				ll tmpDiff = -tmp + c0[idx] + fp[v][0];
				if (tmpDiff < minDiff1)
				{
					minDiff2 = minDiff1;
					minDiff1 = tmpDiff;
					minIdx = i;
				}
				else if (tmpDiff < minDiff2)
				{
					minDiff2 = tmpDiff;
				}
			}
		}
	}
	
	if (isLeaf)
	{
		return;
	}
	
	fc[u][1][1] = sum;
	fc[u][1][0] = sum + minDiffCar10;
	
	fp[u][0] = fc[u][0][0] + minDiffNoCar;
	fp[u][1] = sum + minDiffCarPath;
	
	// there are another case updating fp[u][1], the last 2 situation : drive to v1 and walk back to u, walk to v2.
	ll bestDiff = LINF;
	for (i = 0; i < graph[u].size(); i++)
	{
		v = graph[u][i].first;
		if (v != pre && needVisit[v])
		{
			int idx = graph[u][i].second;
			ll tmp = min(fc[v][1][1] + 2*c1[idx], fc[v][0][0] + 2*c0[idx]);
			ll tmpDiff = -tmp + c0[idx] + c1[idx] + min(fc[v][1][1], fc[v][1][0]);
			
			if (i != minIdx)
			{
				bestDiff = min(bestDiff, tmpDiff + minDiff1);
			}
			else
			{
				bestDiff = min(bestDiff, tmpDiff + minDiff2);
			}
		}
	}
	
	fp[u][1] = min(fp[u][1], sum + bestDiff);
}


int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, u, v, i;
	scanf("%d", &n);
	for (i = 1; i < n; i++)
	{
		scanf("%d%d%d%d", &u, &v, &c0[i], &c1[i]);
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}
	scanf("%d", &m);
	for (i = 1; i <= m; i++)
	{
		scanf("%d", &u);
		needVisit[u] = true;
	}
	
	dfs(1, 0);
	printf("%lld\n", fp[1][1]);
	
	return 0;
}