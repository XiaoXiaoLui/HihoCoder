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

struct Info
{
    Info(){}
    Info(int a, int h, int r, bool d)
    {
        att = a;
        hp = h;
        restTime = r;
        defend = d;
    }
    
    
    int att;
    int hp;
    int restTime;
    bool defend;
};

void dfs(vector<Info> &people, int hp, bool hasDefend, int &ans)
{
    if (hp <= 0)
    {
        int sum = 0;
        for (auto &tmp : people)
        {
            if (tmp.hp > 0)
            {
                sum += tmp.restTime * tmp.att;   
            }
        }
        
        ans = max(ans, sum);
        return;
    }
    
    for (auto &tmp : people)
    {
        if (tmp.hp <= 0 || tmp.restTime == 0)
        {
            continue;
        }
        
        tmp.restTime--;
        if (tmp.defend)
        {
            tmp.defend = false;
            dfs(people, hasDefend ? hp : hp - tmp.att, false, ans);
            tmp.defend = true;
        }
        else
        {
            tmp.hp -= 8;
            dfs(people, hasDefend ? hp : hp - tmp.att, false, ans);
            tmp.hp += 8;
        }
        
        tmp.restTime++;
    }
}

void solve(int n)
{
    int i, j, pos, attack, hp, restTime;
    bool defend;
    string line;
    
    vector<Info> people;
    for (i = 1; i <= n; i++)
    {
        cin >> attack >> hp;
        restTime = 1;
        defend = false;
        if (getline(cin, line))
        {
            if (line.find('W') != string::npos)
            {
                restTime = 2;
            }
            if (line.find('D') != string::npos)
            {
                defend = true;
            }
        }
        
        people.push_back(Info(attack, hp, restTime, defend));
    }
    
    
    
    // simulate
    int ans = 0;
    dfs(people, 8, true, ans);
    
    printf("%d\n", ans);
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int n;
    while (cin >> n)
    {
        solve(n);
    }
	
	return 0;
}