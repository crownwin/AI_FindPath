#pragma once
#include <iostream>
#include <vector>
#include "map.h"
using namespace std;

#ifndef _point2d_
#define _point2d_
struct Point2D
{
	int x;
	int y;
};

typedef struct vector<Point2D> CPolygon;

#endif _point2d_

#define MAX		200

#ifndef _Queue
#define _Queue
#define MAXQ 50000

class Queue 
{
	Point2D* Arr;
	int begin, end;
public:
	Queue() 
	{
		Arr = new Point2D[MAXQ];
		begin = end = 0;
	}
	~Queue() 
	{
		if (Arr) delete[] Arr;
	}
	bool isEmpty() 
	{
		return begin == end;
	}
	bool isFull() 
	{
		return end == (begin - 1);
	}
	Point2D Push(Point2D a) 
	{
		Arr[end] = a;
		end++;
		if (end >= MAXQ) end = end%MAXQ;
		return a;
	}
	Point2D Pop() 
	{
		Point2D t = Arr[begin];
		begin++;
		begin = begin%MAXQ;
		return t;
	}
	bool Find(Point2D a) 
	{
		if (begin <= end)
		{
			for (int i = begin; i<end; i++)
				if (Arr[i].x == a.x && Arr[i].y == a.y) 
					return true;
			return false;
		}
		else 
		{
			for (int i = begin; i<MAXQ; i++)
				if (Arr[i].x == a.x && Arr[i].y == a.y) 
					return true;
			for (int i = 0; i<end; i++)
				if (Arr[i].x == a.x && Arr[i].y == a.y) 
					return true;
			return false;

		}
	}
	int Size() 
	{
		return (end - begin + MAXQ) % MAXQ;
	}
	void Clear()
	{
		begin = 0;
		end = 0;
	}
};
#endif


#ifndef _PriorityQueue
#define _PriorityQueue
#define MAXPQ 50000
struct Edge 
{
	Point2D p;
	float weight;
};

class PQueue
{
private:
	Edge *Arr;
	int end;
public:
	PQueue() 
	{
		Arr = new Edge[MAXPQ];
		end = 0;
	}
	~PQueue() 
	{
		if (Arr) delete[] Arr;
	}
	bool isEmpty() 
	{
		return end == 0;
	}
	bool isFull() 
	{
		return end == MAXPQ;
	}
	bool Push(Point2D a, float m) 
	{
		if (this->isFull()) return false;
		int i = end;
		for (i; i >= 0 && Arr[i - 1].weight>m; i--)
			Arr[i] = Arr[i - 1];
		Arr[i].p = a;
		Arr[i].weight = m;
		end++;
		return true;
	}
	Edge Pop() 
	{
		Edge k;
		k.weight = -1;
		if (this->isEmpty()) 
			return k;
		Edge t = Arr[0];
		for (int i = 0; i<end - 1; i++)
			Arr[i] = Arr[i + 1];
		end--;
		return t;
	}
	int getweight(int a) 
	{ 
		return Arr[a].weight; 
	}
	bool Find(Edge a) 
	{
		for (int i = 0; i<end; i++)
			if (Arr[i].p.x == a.p.x && Arr[i].p.y == a.p.y) 
				return true;
		return false;
	}
	int Find(Point2D a) 
	{
		for (int i = 0; i<end; i++)
			if (Arr[i].p.x == a.x && Arr[i].p.y == a.y)
				return i;
		return -1;
	}
	void update(Point2D p, float newWeight) 
	{
		int a = Find(p);
		if (a >= end || a == -1) 
			return;
		else
			Arr[a].weight = newWeight;
		
		for (int i = 0; i<end; i++)
			for (int j = i + 1; j<end; j++)
				if (Arr[i].weight>Arr[j].weight)
				{
					Edge temp = Arr[i];
					Arr[i] = Arr[j];
					Arr[j] = temp;
				}
	}
	int Size() 
	{
		return end;
	}
	void Clear() 
	{
		end = 0;
	}


};
#endif

class ASTAR
{
	Point2D s, g;
	bool check; 
	Queue edgeTraversed;
	PQueue traverse;
	Point2D pre[MAX][MAX];
public:
	ASTAR() {};

	void init() 
	{
		check = false;
		edgeTraversed.Clear();
		traverse.Clear();
	}

	void search(MAP map) 
	{
		if (traverse.isEmpty()) 
			return;
		Edge begin = traverse.Pop();
		if (!edgeTraversed.Find(begin.p)) 
			edgeTraversed.Push(begin.p);
		if (begin.p.x == g.x && begin.p.y == g.y) 
		{
			check = true;
			return;
		}
		Point2D p1;
		int dx[] = { 1,1,1,0,0,-1,-1,-1 };
		int dy[] = { -1,0,1,-1,1,-1,0,1 };
		for (int i = 0; i < 8; i++) {
			p1.x = begin.p.x + dx[i];
			p1.y = begin.p.y + dy[i];
			int ddd = sqrt(abs(dx[i]) + abs(dy[i]));
			if (map.check(p1) && map.CheckSegment(begin.p, p1)) 
			{
				if (traverse.Find(p1) == -1 && !edgeTraversed.Find(p1)) 
				{
					traverse.Push(p1, begin.weight + ddd + distance(p1, g) - distance(begin.p, g));
					pre[p1.x][p1.y] = begin.p;
				}
				else if (traverse.Find(p1) != -1 && !edgeTraversed.Find(p1)) 
				{
					if (begin.weight + ddd + distance(p1, g) - distance(begin.p, g) < traverse.getweight(traverse.Find(p1))) 
					{
						traverse.update(p1, begin.weight + ddd + distance(p1, g) - distance(begin.p, g));
						pre[p1.x][p1.y] = begin.p;
					}
				}
			}
		}
		search(map);
	}
	vector<Point2D> find(MAP map)
	{
		init();
		vector<Point2D> kq;
		s = map.getStart();
		g = map.getGoal();
		traverse.Push(s, distance(s, g));
		Point2D sp;
		sp.x = -10001;
		sp.y = -10001;
		pre[s.x][s.y] = sp;
		search(map);
		if (check) 
		{
			Point2D k = g;
			while (!(k.x == sp.x && k.y == sp.y)) 
			{
				kq.push_back(k);
				k = pre[k.x][k.y];
			}
		}
		return kq;
	}

};