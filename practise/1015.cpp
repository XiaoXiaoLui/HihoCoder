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
char pat[N];
char str[N];


void getNext(const char *s, int n, vector<int> &next)
{
	int i, j, pre, right, len;
	next.clear();
	next.insert(next.end(), n + 2, 0);
	
	next[0] = n;
	
	for (i = 1; i < n && s[i] == s[i - 1]; i++);
	next[1] = i - 1;
	
	pre = 1;
	for (i = 2; i < n; i++)
	{
		right = pre + next[pre] - 1;
		len = next[i - pre];
		if (i + len - 1 >= right)
		{
			j = right < i ? 0 : right - i + 1;
			for (; i + j < n && s[i + j] == s[j]; j++);
			
			next[i] = j;
			pre = i;
		}
		else
		{
			next[i] = len;
		}
	}
}

int exKmp(const char *str, const char *pat)
{
	int len1, len2, i, j, pre, right, len, res;
	vector<int> next;
	vector<int> ex;
	
	len1 = strlen(str);
	len2 = strlen(pat);
	getNext(pat, len2, next);
	
	ex.insert(ex.end(), len1 + 2, 0);
	for (i = 0; i < len1 && i < len2 && str[i] == pat[i]; i++);
	ex[0] = i;
	
	pre = 0;
	res = 0;
	for (i = 1; i < len1; i++)
	{
		right = pre + ex[pre] - 1;
		len = next[i - pre];
		if (i + len - 1 >= right)
		{
			j = right < i ? 0 : right - i + 1;
			for (; i + j < len1 && j < len2 && str[i + j] == pat[j]; j++);
			
			ex[i] = j;
			pre = i;
		}
		else
		{
			ex[i] = len;
		}
		
		if (ex[i] == len2)
		{
			res++;
		}
	}
	
	if (ex[0] == len2)
	{
		res++;
	}
	
	return res;
}

int kmp(const char *str, const char *pat)
{
	static int next[N];
	int i, j, len;
	next[0] = -1;
	for (i = 1, j = -1; pat[i]; i++)
	{
		for (; j != -1 && pat[j + 1] != pat[i]; j = next[j]);
		
		if (pat[j + 1] == pat[i])
		{
			j++;
		}
		next[i] = j;
	}
	
	len = i;
	int res = 0;
	for (i = 0, j = -1; str[i]; i++)
	{
		for (; j != -1 && pat[j + 1] != str[i]; j = next[j]);
		
		if (pat[j + 1] == str[i])
		{
			j++;
		}
		
		if (j == len - 1)
		{
			res++;
			j = next[j];
		}
	}
	
	return res;
}


int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, i;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s%s", pat, str);
		int ret = exKmp(str, pat);
		printf("%d\n", ret);
	}
	
	return 0;
}