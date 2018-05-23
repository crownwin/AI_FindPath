#include <stack>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;


struct p_queue
{
	int edge;
	int cost;
};

struct astar_queue
{
	int edge;
	int cost;
	int h;
	int f;
};

int addPQueue(queue<p_queue> &pq, p_queue cur)
{
	int result = 1, added = 0;
	vector<p_queue> a;
	while (!pq.empty())
	{
		a.push_back(pq.front()); pq.pop();
	}

	for (int i = 0; i < a.size(); i++)
		if (cur.edge == a[i].edge)
		{
			if (cur.cost < a[i].cost) {
				a[i].cost = cur.cost;
				added = 1;
			}
			else
				result = 0;
		}

	if (!added && result)
	{
		for (int i = 0; i < a.size(); i++)
			if (cur.cost < a[i].cost) {
				a.insert(a.begin() + i, 1, cur);
				break;
				added = 1;
			}
		if (!added)
			a.push_back(cur);
	}

	for (int i = 0; i < a.size(); i++)
		pq.push(a[i]);
	return result;
}

int addPQueue(queue<astar_queue> &aq, astar_queue cur)
{
	int result = 1, added = 0;
	vector<astar_queue> a;
	while (!aq.empty())
	{
		a.push_back(aq.front()); aq.pop();
	}

	for (int i = 0; i < a.size(); i++)
		if (cur.edge == a[i].edge)
		{
			if (cur.f < a[i].f) {
				a[i].f = cur.f;
				added = 1;
			}
			else
				result = 0;
		}

	if (!added && result)
	{
		for (int i = 0; i < a.size(); i++)
			if (cur.f < a[i].f) {
				a.insert(a.begin() + i, 1, cur);
				added = 1;
				break;
			}
		if (!added)
			a.push_back(cur);
	}

	for (int i = 0; i < a.size(); i++)
		aq.push(a[i]);

	return result;
}

int dfs(int **a, int n, int start, int end, vector<int> & ttd, vector<int>& dd)
{
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		pre[i] = -1;

	stack<int> s;
	s.push(start);

	while (!s.empty())
	{
		int top = s.top();
		s.pop();

		if (visited[top] == false)
		{
			ttd.push_back(top);

			if (top == end)
				break;
			
			visited[top] = true;

			for (int i = n - 1; i >= 0; i--)
				if (a[top][i] > 0 && visited[i] == false)
				{
					s.push(i);
					pre[i] = top;
				}
		}
	}

	delete[]visited;

	if (pre[end] == -1 && start != end)
		return 0;

	dd.push_back(end);

	while (pre[end] != -1)
	{
		dd.insert(dd.begin(), pre[end]);
		end = pre[end];
	}

	return 1;
}

int bfs(int **a, int n, int start, int end, vector<int>& ttd, vector<int>& dd)
{
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		pre[i] = -1;

	queue<int> q;
	q.push(start);

	while (!q.empty())
	{
		int front = q.front();
		q.pop();
		
		ttd.push_back(front);
		if (front == end)
			break;

		visited[front] = true;

		for(int i = 0; i < n; i++)
			if (a[front][i] > 0 && visited[i] == false)
			{
				q.push(i);
				pre[i] = front;
				visited[i] = true;
			}
	}

	delete[]visited;

	if (pre[end] == -1 && start != end)
		return 0;

	dd.push_back(end);

	while (pre[end] != -1)
	{
		dd.insert(dd.begin(), pre[end]);
		end = pre[end];
	}

	return 1;
}

int ucs(int **a, int n, int start, int end, vector<int>& ttd, vector<int>& dd)
{
	p_queue curPQ;
	curPQ.edge = start;
	curPQ.cost = 0;

	queue<p_queue> pq;
	pq.push(curPQ);

	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		pre[i] = -1;

	while (!pq.empty())
	{
		p_queue pfront = pq.front();
		pq.pop();
		
		int front = pfront.edge;
		ttd.push_back(front);
		visited[front] = true;

		if (front == end)
			break;

		for (int i = 0; i < n; i++)
			if (a[front][i] > 0 && visited[i] == false)
			{
				p_queue tmp;
				tmp.edge = i;
				tmp.cost = pfront.cost + a[front][i];

				if (addPQueue(pq, tmp))
					pre[i] = front;
			}
	}

	if (pre[end] == -1 && start != end)
		return 0;

	dd.push_back(end);

	while (pre[end] != -1)
	{
		dd.insert(dd.begin(), pre[end]);
		end = pre[end];
	}

	return 1;
}

int gbfs(int **a, int *h, int n, int start, int end, vector<int>& ttd, vector<int>& dd)
{
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		pre[i] = -1;

	stack<int> s;
	s.push(start);

	while (!s.empty())
	{
		int top = s.top();
		s.pop();
	
		if (visited[top] == false)
		{
			ttd.push_back(top);
		
			if (top == end)
				break;

			visited[top] = true;

			vector<int> sa; sa.resize(0);
			for (int i = 0; i < n; i++)
				if (a[top][i] > 0)
					sa.push_back(i);

			for (int i = 0; i < sa.size() - 1; i++)
				for (int j = i + 1; j < sa.size(); j++)
					if (h[sa[i]] > h[sa[j]])
					{
						int tmp = sa[i];
						sa[i] = sa[j];
						sa[j] = tmp;
					}


			for (int i = sa.size()-1; i >=0; i--)
				if (visited[sa[i]] == false)
				{
					s.push(sa[i]);
					pre[sa[i]] = top;
				}
		}
	}

	delete[]visited;

	if (pre[end] == -1 && start != end)
		return 0;

	dd.push_back(end);

	while (pre[end] != -1)
	{
		dd.insert(dd.begin(), pre[end]);
		end = pre[end];
	}

	return 1;
}

int astar(int **a, int *h, int n, int start, int end, vector<int>& ttd, vector<int>& dd)
{
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		pre[i] = -1;

	astar_queue afirst;
	afirst.edge = start;
	afirst.cost = 0;
	afirst.h = h[start];
	afirst.f = afirst.cost + afirst.h;

	queue<astar_queue> aq;
	aq.push(afirst);
	
	while (!aq.empty())
	{
		astar_queue qfront = aq.front();
		int front = qfront.edge;
		aq.pop();

		visited[front] = true;

		ttd.push_back(front);

		if (front == end)
			break;

		for (int i = 0; i < n; i++)
		{
			if (a[front][i] > 0 && visited[i] == false)
			{
				astar_queue nqueue;
				nqueue.edge = i;
				nqueue.cost = qfront.cost + a[front][i];
				nqueue.h = h[i];
				nqueue.f = nqueue.h + nqueue.cost;

				if (addPQueue(aq, nqueue))
					pre[i] = front;
			}
		}

	}

	delete[]visited;

	if (pre[end] == -1 && start != end)
		return 0;

	dd.push_back(end);

	while (pre[end] != -1)
	{
		dd.insert(dd.begin(), pre[end]);
		end = pre[end];
	}

	return 1;
}