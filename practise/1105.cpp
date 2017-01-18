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


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int t, a;
    char type;
    cin >> t;
    
   priority_queue<int, vector<int>, less<int> > heap;
    while (t--)
    {
        cin >> type;
        if (type == 'A')
        {
            cin >> a;
            heap.push(a);
        }
        else
        {
            cout << heap.top() << endl;
            heap.pop();
        }
    }
	
	return 0;
}