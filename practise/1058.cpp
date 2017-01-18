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
#include <assert.h>

using namespace std;

#define USE_IOSTREAM \
{\
	ios::sync_with_stdio(false);\
	cin.tie(0);\
	cout.tie(0);\
}

#define pii pair<int, int>
#define mp make_pair

#define ASSERT assert

typedef long long ll;


struct Node
{
	Node(const char initCh = 'A')
	{
		size = 1;
		ch = initCh;
		parent = left = right = 0;
		
		lazyAdd = lazySet = lazyCmd4 = false;
		addValue = cmd4Offset = cmd4Cnt = 0;
		setValue = 'A';
	}
	
	int leftSize()
	{
		if (left)
		{
			return left->size;
		}
		return 0;
	}
	
	int rightSize()
	{
		if (right)
		{
			return right->size;
		}
		return 0;
	}
	
	void up()
	{
		size = leftSize() + rightSize() + 1;
	}
	
	// lazy propagate
	void down()
	{
		// notice the order, first set then add, since set operation erase all previous changes
		if (lazySet)
		{
			if (left)
			{
				left->ch = setValue;
				left->setValue = setValue;
				left->lazySet = true;
				left->lazyAdd = left->lazyCmd4 = false;
				left->addValue = left->cmd4Cnt = left->cmd4Offset = 0;
			}
			if (right)
			{
				right->ch = setValue;
				right->setValue = setValue;
				right->lazySet = true;
				right->lazyAdd = right->lazyCmd4 = false;
				right->addValue = right->cmd4Cnt = right->cmd4Offset = 0;
			}
		}
		
		if (lazyAdd)
		{
			if (left)
			{
				left->plus(addValue);
				left->addValue += addValue;
				left->lazyAdd = true;
			}
			if (right)
			{
				right->plus(addValue);
				right->addValue += addValue;
				right->lazyAdd = true;
			}
		}
		
		if (lazyCmd4)
		{
			if (left)
			{
				left->plus(cmd4Offset + cmd4Cnt * left->leftSize());
				left->cmd4Offset += cmd4Offset;
				left->cmd4Cnt += cmd4Cnt;
				left->lazyCmd4 = true;
			}
			if (right)
			{
				int offset = cmd4Offset + (leftSize() + 1) * cmd4Cnt;
				right->plus(offset + cmd4Cnt * right->leftSize());
				right->cmd4Offset += offset;
				right->cmd4Cnt += cmd4Cnt;
				right->lazyCmd4 = true;
			}
		}
		
		
		lazyAdd = lazySet = lazyCmd4 = false;
		addValue = cmd4Offset = cmd4Cnt = 0;
	}
	
	void plus(int num)
	{
		ch = ((ch - 'A') + num) % 26 + 'A';
	}
	
	// basic info
	int size;
	char ch;
	Node *left;
	Node *right;
	Node *parent;
	
	// lazy propagation info
	bool lazyAdd;
	bool lazySet;
	bool lazyCmd4;
	
	int addValue;
	char setValue;
	int cmd4Offset;
	int cmd4Cnt;
};

struct SplayTree
{
	SplayTree()
	{
		// create left bound and right bound
		mRoot = getNode('A');
		Node *x = getNode('A');
		x->parent = mRoot;
		mRoot->left = x;
		mRoot->size = 2;
	}
	
	~SplayTree()
	{
		deleteTree(mRoot);
		mRoot = 0;
	}
	
	void build(char *s)
	{
		for (int i = 0; s[i]; i++)
		{
			insert(i, s[i]);
		}
	}
	
	void getResult(char *s)
	{
		int n = mRoot->size - 2;
		for (int i = 1; i <= n; i++)
		{
			find(i, 0);
			s[i - 1] = mRoot->ch;
		}
		s[n] = '\0';
	}
	
	void insert(int k, char ch)
	{
		ASSERT(k >= 0 && k <= mRoot->size - 2);
		
		find(k, 0);
		find(k + 1, mRoot);
		
		Node *y = mRoot->right;
		Node *x = getNode(ch);
		x->parent = y;
		y->left = x;
		
		splay(x, 0);
	}
	
	void setValue(int i, int j, char setValue)
	{
		ASSERT(i <= j && i >= 1 && i <= mRoot->size - 2 && j >= 1 && j <= mRoot->size - 2);
		
		find(i - 1, 0);
		find(j + 1, mRoot);
		
		Node *y = mRoot->right;
		Node *x = y->left;
		
		x->ch = setValue;
		x->setValue = setValue;
		x->lazySet = true;
		x->lazyAdd = x->lazyCmd4 = false;
		x->addValue = x->cmd4Cnt = x->cmd4Offset = 0;
		
		splay(x, 0);
	}
	
	void addValue(int i, int j, int k)
	{
		ASSERT(i <= j && i >= 1 && i <= mRoot->size - 2 && j >= 1 && j <= mRoot->size - 2);
		k %= 26;
		
		find(i - 1, 0);
		find(j + 1, mRoot);
		
		Node *y = mRoot->right;
		Node *x = y->left;
		x->plus(k);
		x->lazyAdd = true;
		x->addValue += k;
		
		splay(x, 0);
	}
	
	void move2Back(int k)
	{
		ASSERT(k >= 1 && k <= mRoot->size - 2);
		
		if (k == mRoot->size - 2)
		{
			return;
		}
		
		find(0, 0);
		find(mRoot->size - 1, mRoot);
		
		Node *y = mRoot->right;
		find(k, y);
		
		Node *x = y->left;
		Node *z = x->right;
		x->right = 0;
		z->parent = 0;
		find(1, y);
		x = y->left;
		x->left = z;
		z->parent = x;
		
		splay(z, 0);
	}
	
	void cmd4(int i, int j)
	{
		ASSERT(i <= j && i >= 1 && i <= mRoot->size - 2 && j >= 1 && j <= mRoot->size - 2);
		
		find(i - 1, 0);
		find(j + 1, mRoot);
		
		Node *y = mRoot->right;
		Node *x = y->left;
		x->plus(1 + x->leftSize());
		x->cmd4Offset += 1;
		x->cmd4Cnt += 1;
		x->lazyCmd4 = true;
		
		splay(x, 0);
	}
	
	
private:

	void find(int k, Node *y)
	{
		ASSERT(k >= 0 && k <= mRoot->size - 1);
		k++;
		
		Node *x = mRoot;
		while (true)
		{
			x->down();
			if (k <= x->leftSize())
			{
				x = x->left;
			}
			else if (k == x->leftSize() + 1)
			{
				break;
			}
			else
			{
				k -= x->leftSize() + 1;
				x = x->right;
			}
		}
		
		splay(x, y);
	}
	
	void splay(Node *x, Node *y)
	{
		x->down();
		while (x->parent != y)
		{
			if (x->parent->parent == y)
			{
				if (x == x->parent->left)
				{
					rightRotate(x->parent);
				}
				else if (x == x->parent->right)
				{
					leftRoate(x->parent);
				}
			}
			else
			{
				if (x->parent == x->parent->parent->left)
				{
					if (x == x->parent->left)
					{
						rightRotate(x->parent->parent);
						rightRotate(x->parent);
					}
					else
					{
						leftRoate(x->parent);
						rightRotate(x->parent);
					}
				}
				else
				{
					if (x == x->parent->right)
					{
						leftRoate(x->parent->parent);
						leftRoate(x->parent);
					}
					else
					{
						rightRotate(x->parent);
						leftRoate(x->parent);
					}
				}
			}
		}
		
		x->up();
	}
	
	void leftRoate(Node *x)
	{
		ASSERT(x && x->right);
		
		Node *y = x->right;
		replace(x, y);
		x->parent = y;
		x->right = y->left;
		
		if (y->left)
		{
			y->left->parent = x;
		}
		y->left = x;
		
		x->up();
		y->up();
	}
	
	void rightRotate(Node *x)
	{
		ASSERT(x && x->left);
		
		Node *y = x->left;
		replace(x, y);
		x->parent = y;
		x->left = y->right;
		
		if (y->right)
		{
			y->right->parent = x;
		}
		y->right = x;
		
		x->up();
		y->up();
	}
	
	// y replace x
	void replace(Node *x, Node *y)
	{
		ASSERT(x);
		
		if (y)
		{
			y->parent = x->parent;
		}
		
		if (x == mRoot)
		{
			mRoot = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}

	void deleteTree(Node *x)
	{
		if (!x)
		{
			return;
		}
		deleteTree(x->left);
		deleteTree(x->right);
		putNode(x);
	}
	
	Node* getNode(const char initCh)
	{
		Node* x = new Node(initCh);
		return x;
	}
	
	void putNode(Node *x)
	{
		delete x;
	}
	
	
	Node *mRoot;
};

const int N = 5e4 + 100;
char s[N];
char ans[N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i;
	cin >> n >> m;
	cin >> s;
	
	SplayTree tr;
	tr.build(s);
	
	string noUse;
	char ch;
	int left, right, k, cmd;
	while (m--)
	{
		cin >> noUse >> cmd;
		if (cmd == 1)
		{
			cin >> left >> right >> ch;
			tr.setValue(left, right, ch);
		}
		else if (cmd == 2)
		{
			cin >> left >> right >> k;
			tr.addValue(left, right, k);
		}
		else if (cmd == 3)
		{
			cin >> k;
			tr.move2Back(k);
		}
		else 
		{
			cin >> left >> right;
			tr.cmd4(left, right);
		}
	}
	
	tr.getResult(ans);
	cout << ans << endl;
	
	return 0;
}