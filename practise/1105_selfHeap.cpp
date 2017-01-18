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

// left 2*i + 1, right 2*i + 2
template <class T, class Compare = less<T> >
class Heap
{
public:
    Heap(const Compare &cmp = Compare()) : mCmp(cmp) {}
    Heap(const Heap &other) : mCmp(other.mCmp), mTr(other.mTr){}
    
    void build(T *a, int n)
    {
        mTr.clear();
        mTr.insert(mTr.end(), a, a + n);
        
        int i = 0;
        for (i = parent(mTr.size() - 1); i >= 0; i = parent(i))
        {
            mTr[i] = mTr[left(i)];
            if (right(i) < mTr.size())
            {
                mTr[i] = max(mTr[i], mTr[right(i)], mCmp);
            }
        }
    }
    
    T top() const
    {
        return mTr[0];
    }
    
    void pop()
    {
        mTr[0] = mTr.back();
        mTr.pop_back();
        int nextIdx;
        for (int i = 0; left(i) < mTr.size(); )
        {
            nextIdx = left(i);
            if (right(i) < mTr.size() && mCmp(mTr[nextIdx], mTr[right(i)]))
            {
                nextIdx++;
            }
            
            if (mCmp(mTr[nextIdx], mTr[i]))
            {
                break;
            }
            
            swap(mTr[nextIdx], mTr[i]);
            i = nextIdx;
        }
    }
    
    void push(const T &x)
    {
        mTr.push_back(x);
        
        for (int i = mTr.size() - 1; i >= 1 && mCmp(mTr[parent(i)], mTr[i]); i = parent(i))
        {
            swap(mTr[parent(i)], mTr[i]);
        }
    }
    
private:
    vector<T> mTr;
    Compare mCmp;
    
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    
    int left(int i)
    {
        return 2*i + 1;
    }
    
    int right(int i)
    {
        return 2*i + 2;
    }
    
    int sibling(int i)
    {
        return (i & 1) ? i + 1 : i - 1;
    }
};

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
    int t, a;
    char type;
    cin >> t;
    
    Heap<int> heap;
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