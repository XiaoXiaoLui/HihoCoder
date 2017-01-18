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

int solve(int i, int n)
{
    i--;
    while (i)
    {
        if (i % 4 == 1 || i % 4 == 2)
        {
            return n;
        }
        
        i /= 4;
        n--;
    }
    return 0;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int i, n, t;
    cin >> t;
    while (t--)
    {
        cin >> i >> n;
        int ret = solve(i, n);
        cout << ret << endl;
    }
	
	return 0;
}