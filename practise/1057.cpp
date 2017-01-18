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
#include <stack>

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

int getTime(const string &str)
{
	if (str.size() != 8 || !isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) || !isdigit(str[4]) || !isdigit(str[6]) || !isdigit(str[7])
		|| str[2] != ':' || str[5] != ':')
	{
		return false;
	}
	
	int hour, minute, second;
	hour = (str[0] - '0') * 10 + str[1] - '0';
	minute = (str[3] - '0') * 10 + str[4] - '0';
	second = (str[6] - '0') * 10 + str[7] - '0';
	
	if (hour > 60 || minute > 60 || second > 60)
	{
		return false;
	}
	
	int curTime = hour * 3600 + minute * 60 + second;
	
	return curTime;
}

string time2Str(int curTime)
{
	static char s[40];
	int hour, minute, second;
	second = curTime % 60;
	curTime /= 60;
	minute = curTime % 60;
	hour = curTime / 60;
	
	sprintf(s, "%02d:%02d:%02d", hour, minute, second);
	
	return string(s);
}

bool read(string &funName, int &curTime, bool &bStart)
{
	string timeStr, startStr;
	cin >> funName >> timeStr >> startStr;
	
	curTime = getTime(timeStr);
	if (curTime < 0)
	{
		return false;
	}
	
	if (startStr == "START")
	{
		bStart = true;
	}
	else if (startStr == "END")
	{
		bStart = false;
	}
	else
	{
		return false;
	}
	
	return true;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	map<string, int> timeMap;
	stack<pair<string, int> > S;
	int n;
	vector<string> ans;
	set<string> startSet;
	
	cin >> n;
	string funName;
	int curTime, startTime, endTime;
	bool bStart;
	bool ret;
	int preTime = 0;
	while (n--)
	{
		ret = read(funName, curTime, bStart);
		if (!ret)
		{
			break;
		}
		
		if (!S.empty() && curTime < preTime)
		{
			ret = false;
			break;
		}
		preTime = curTime;
		
		if (bStart)
		{
			if (startSet.count(funName) > 0)
			{
				ret = false;
				break;
			}
			
			startSet.insert(funName);
			ans.push_back(funName);
			S.push({funName, curTime});
		}
		else
		{
			if (S.empty() || S.top().first != funName)
			{
				ret = false;
				break;
			}
			
			startTime = S.top().second;
			S.pop();
			
			timeMap[funName] = curTime - startTime;
		}
	}
	
	if (!S.empty())
	{
		ret = false;
	}
	
	if (!ret)
	{
		cout << "Incorrect performance log" << endl;
	}
	else
	{
		for (int i = 0; i < ans.size(); i++)
		{
			cout << ans[i] << " " << time2Str(timeMap[ans[i]]) << endl;
		}
	}
	
	return 0;
}