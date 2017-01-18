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

void rotate(int &rowNum, int &colNum, int &left, int &top, int &right, int &bottom)
{
	int tmp = left;
	left = rowNum - bottom;
	bottom = right;
	right = rowNum - top;
	top = tmp;
	swap(rowNum, colNum);
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	int ans = 0;
	int rowNum, colNum, left, top, right, bottom, L, i, j, sub, w, h;
	cin >> rowNum >> colNum >> L;
	cin >> left >> right >> top >> bottom;
	for (int k = 0; k < 4; k++)
	{
		for (i = 1; i <= rowNum && 2*i + 2 <= L; i++)
		{
			for (j = 1; j <= colNum && 2*(i + j) <= L; j++)
			{
				int len = 2*(i + j);
				if (i > top && i <= bottom && j > right)
				{
					len += 2 * (i - top);
				}
				else if (i > bottom && j > left && j <= right)
				{
					len += 2 * (j - left);
				}
				if (len > L)
				{
					continue;
				}
			
			
				h = max(0, min(i, bottom) - top);
				w = max(0, min(j, right) - left);

				ans = max(ans, i * j - h * w);
			}
			
		}
		rotate(rowNum, colNum, left, top, right, bottom);
	}
	
	cout << ans << endl;
	return 0;
}