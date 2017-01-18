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

struct Node
{
    void set(int value)
    {
        mul = value;
        prefixSum = value;
        suffixSum = value;
        sum = value;
    }
    int sum;
    int prefixSum;
    int suffixSum;
    int mul;
};


const int N = 1 << 17;
const int MOD = 10007;

Node tr[2 * N];
int a[N];


void up(Node &res,  Node left, Node right)
{
    res.mul = (left.mul * right.mul) % MOD;
    res.prefixSum = (left.prefixSum + left.mul * right.prefixSum) % MOD;
    res.suffixSum = (right.suffixSum + right.mul * left.suffixSum) % MOD;
    res.sum = (left.sum  + right.sum + left.suffixSum * right.prefixSum) % MOD;
}

void build(int n)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (i < n)
        {
           tr[i + N].set(0);
        }
        else
        {
            tr[i + N].set(1);
        }
    }
    
    for (i = N - 1; i >= 1; i--)
    {
        up(tr[i], tr[2*i], tr[2*i + 1]);
    }
}

void update(int pos, int value)
{
    value %= MOD;
    int i = pos + N;
    tr[i].set(value);
    for (i /= 2; i >= 1; i /= 2)
    {
        up(tr[i], tr[2*i], tr[2*i + 1]);
    }
}

int query(int left, int right)
{
    int l, r;
    Node leftStat;
    Node rightStat;
    leftStat.set(0);
    rightStat.set(0);
    
    for (l = left + N, r = right + N + 1; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
        {
            up(leftStat, leftStat, tr[l++]);
        }
        
        if (r & 1)
        {
            up(rightStat, tr[--r], rightStat);
        }
    }
    
    Node res;
    up(res, leftStat, rightStat);
    
    return res.sum;
}

int main()
{
	//USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, qNum, pos, value;
    scanf("%d%d", &n, &qNum);
    build(n);
    for (int i = 0; i < qNum; i++)
    {
        scanf("%d%d", &pos, &value);
        pos--;
        update(pos, value);
        
        int ret = query(0, n - 1);
        printf("%d\n", ret);
    }
    
    
	return 0;
}