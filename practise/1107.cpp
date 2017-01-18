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

struct Trie
{
    Trie()
    {
        newNode();
        mCount[0] = 1000;
    }
    
    void addString(const char *str)
    {
        int i, u;
        for (i = 0, u = 0; str[i]; i++)
        {
            int idx = str[i] - 'a';
            if (!mTr[u][idx])
            {
                mTr[u][idx] = newNode();
            }
            u = mTr[u][idx];
            mCount[u]++;
        }
    }
    
    int dfs(int u)
    {
        if (mCount[u] <= 5)
        {
            return 1;    
        }
        
        int res = 0;
        for (int i = 0; i < CHARSET; i++)
        {
            if (mTr[u][i])
            {
                res += dfs(mTr[u][i]);
            }
        }
        
        return res;
    }

private:
    int newNode()
    {
        mTr.push_back(vector<int>(CHARSET, 0));
        mCount.push_back(0);
        
        return mTr.size() - 1;
    }
    
    const static int CHARSET = 26;
    vector<vector<int> > mTr;
    vector<int> mCount;
};

const int N = 2e6 + 100;
char s[N];

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int t;
    scanf("%d", &t);
    Trie tr;
    while (t--)
    {
        scanf("%s", s);
        tr.addString(s);
    }
    
    int ret = tr.dfs(0);
    printf("%d\n", ret);
    
	return 0;
}