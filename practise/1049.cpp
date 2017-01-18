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

string preOrder;
string inOrder;
string postOrder;
int pos[200];

void solve(int l1, int r1, int l2, int r2)
{
	if (l1 > r1)
	{
		return;
	}
	
	int mid = pos[preOrder[l1]];
	int leftLen = mid - l2;
	int rightLen = r2 - mid;
	solve(l1 + 1, l1 + leftLen, l2, mid - 1);
	solve(l1 + leftLen + 1, r1, mid + 1, r2);
	
	postOrder.push_back(preOrder[l1]);
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	cin >> preOrder >> inOrder;
	for (int i = 0; i < inOrder.size(); i++)
	{
		pos[inOrder[i]] = i;
	}
	
	solve(0, preOrder.size() - 1, 0, inOrder.size() - 1);
	
	cout << postOrder << endl;
	
	return 0;
}