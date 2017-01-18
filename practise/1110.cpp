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

void solve(const string &s)
{
    int i;
    
    int cnt = 0;
    bool ok = true;
    for (i = 0; i < s.size() && ok; i++)
    {
        switch (s[i])
        {
            case '0':
            case '1':
            break;
            case '*':
            if (i == 0 || s[i - 1] == '(' || s[i - 1] == '|')
            {
                ok = false;
            }
            break;
            case '|':
            if (i == 0 || s[i - 1] == '(' || s[i - 1] == '|'
                || i == s.size() - 1 || s[i + 1] == ')' || s[i + 1] == '*' || s[i + 1] == '|')
            {
                ok = false;
            }
            break;
            case '(':
            cnt++;
            break;
            case ')':
            cnt--;
            if (cnt < 0 || s[i - 1] == '(')
            {
                ok = false;
            }
            break;
            default:
            ok = false;
            break;
        }
    }
    
    if (cnt > 0)
    {
        ok = false;
    }
    if (ok)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    string s;
    while (cin >> s)
    {
        solve(s);
    }
	
	return 0;
}