#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>
#pragma once 
#include <iostream>
using namespace std;

#ifndef _point2d_
#define _point2d_
struct Point2D
{
	int x;
	int y;
};

typedef struct vector<Point2D> CPolygon;

#define CAN2	1.41425
#define INF 101
#define MAXMAP 100
#define PI 3.14159265359
#endif _point2d_

vector<int> getNumber(string line)
{
	vector<int> a;
	for (int i = 0; i < line.length(); i++)
	{
		int x = 0;
		while (line[i] >= '0' && line[i] <= '9')
		{
			x = x * 10 + (int)(line[i] - 48);
			i++;
		}
		a.push_back(x);
	}
	return a;
}

CPolygon getPoly(string line)
{
	CPolygon result;
	vector<int> a = getNumber(line);

	for (int i = 0; i < a.size(); i = i + 2)
	{
		Point2D tmp;
		tmp.x = a[i];
		tmp.y = a[i + 1];
		result.push_back(tmp);
	}
	return result;
}

float distance(Point2D a, Point2D b) 
{
	return sqrt((double)((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
}

int orientation(Point2D p, Point2D q, Point2D r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) 
		return 0;
	return (val > 0) ? 1 : 2;
}

bool onSegment(Point2D p, Point2D q, Point2D r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

bool operator == (Point2D a, Point2D b) 
{
	return (a.x == b.x && a.y == b.y);
}

bool isIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
{

	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (p1 == p2 || p1 == q2 || q1 == p2 || q1 == q2) return false;

	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	if (o4 == 0 && onSegment(p2, q1, q2)) return true;
	if (o1 != o2 && o3 != o4)
		return true;
	return false;
}

bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
{

	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (o1 == 0 && onSegment(p1, p2, q1)) 
		return true;
	if (o2 == 0 && onSegment(p1, q2, q1)) 
		return true;
	if (o3 == 0 && onSegment(p2, p1, q2)) 
		return true;
	if (o4 == 0 && onSegment(p2, q1, q2)) 
		return false;


	if (o1 != o2 && o3 != o4) 
		return true;

	return false;
}

class MAP
{
	Point2D start, goal;
	vector<CPolygon> list;

public:
	void xulyMap()
	{
	
		int maxTD = 1;
		if (start.x > maxTD) maxTD = start.x;
		if (start.y > maxTD) maxTD = start.y;
		if (goal.x > maxTD) maxTD = goal.x;
		if (goal.y > maxTD) maxTD = goal.y;

		for (int i = 0; i < list.size(); i++)
		{
			for (int j = 0; j < list[i].size(); j++)
			{
				if (list[i][j].x > maxTD) maxTD = list[i][j].x;
				if (list[i][j].y > maxTD) maxTD = list[i][j].y;
			}
		}
		int scale = 1;
		if (MAXMAP < maxTD)
		{
			scale = maxTD / MAXMAP;
		
			if (start.x >= scale) start.x /= scale;
			if (start.y >= scale) start.y /= scale;

			if (goal.x >= scale) goal.x /= scale;
			if (goal.y >= scale) goal.y /= scale;

			for (int i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list[i].size(); j++)
				{
					if (list[i][j].x >= scale) list[i][j].x /= scale;
					if (list[i][j].y >= scale) list[i][j].y /= scale;
				}
			}
		}

	}
	MAP(string name)
	{
		ifstream f;
		f.open(name);
		string line;

		getline(f, line);
		vector<int> a = getNumber(line);
		start.x = a[0];
		start.y = a[1];
		goal.x = a[2];
		goal.y = a[3];

		while (!f.eof())
		{
			getline(f, line);
			list.push_back(getPoly(line));
		}
		f.close();
		xulyMap();
	}
	Point2D getStart()
	{
		return start;
	}
	Point2D getGoal() {
		return goal;
	}
	vector<CPolygon> getList() {
		return list;
	}
	bool CheckSegment(Point2D a, Point2D b) 
	{
		for (int i = 0; i<list.size(); i++)
			for (int j = 0; j<list[i].size(); j++)
				if (isIntersect(a, b, list[i][j], list[i][(j + 1) % list[i].size()])) 
					return false;
		return true;
	}

	Point2D setVector(Point2D a, Point2D b) {
		Point2D c;
		c.x = b.x - a.x;
		c.y = b.y - a.y;
		return c;
	}

	float calculateAngle(Point2D vectora, Point2D vectorb) 
	{
		float t = (vectora.x*vectorb.x + vectora.y*vectorb.y);
		float m;
		m = sqrt(pow(vectora.x, 2) + pow(vectora.y, 2))*sqrt(pow(vectorb.x, 2) + pow(vectorb.y, 2));
		return acos(t / m);
	}

	bool checkPolygon(Point2D p, int k) 
	{
		int n = list[k].size();
		Point2D extreme = { INF, p.y };
		int count = 0, j = 0;
		do
		{
			int next = (j + 1) % n;
			if (doIntersect(list[k][j], list[k][next], p, extreme))
			{
				if (orientation(list[k][j], p, list[k][next]) == 0 && onSegment(list[k][j], p, list[k][next]))
					return false;
				count++;
			}
			j = next;
		} while (j != 0);

		Point2D extreme2 = { -INF, p.y };
		int count2 = 0; j = 0;
		do
		{
			int next = (j + 1) % n;
			if (doIntersect(list[k][j], list[k][next], p, extreme2))
			{
				if (orientation(list[k][j], p, list[k][next]) == 0 && onSegment(list[k][j], p, list[k][next]))
					return false;
				count2++;
			}
			j = next;
		} while (j != 0);
		if (count % 2 == 1 && count2 % 2 == 1) return false;
		else return true;
		/*Point2D vectora, vectorb;
		float sum = 0;
		int n = list[k].size();
		for (int i = 0; i < n - 1; i++)
		{
			vectora = setVector(list[k][i], p);
			vectorb = setVector(list[k][i + 1], p);
			sum = sum + calculateAngle(vectora, vectorb);
		}
		vectora = setVector(list[k][n - 1], p);
		vectorb = setVector(list[k][0], p);
		sum = sum + calculateAngle(vectora, vectorb);
		if (abs(sum - 2 * PI)<10)
			return true;
		else
			return false;*/
	}

	bool check(Point2D p) 
	{
		for (int i = 0; i<list.size(); i++)
			if (checkPolygon(p, i) == false) 
				return false;
		return true;
	}

	void movePolygon(int n, int m) 
	{
		if (n >= list.size()) 
			return;
		CPolygon p = list[n];
		CPolygon p1 = p;
		list.erase(list.begin() + n);
		int h, v;
		if (m == 0) {
			h = 0;
			v = 1;
		}
		else if (m == 1) {
			h = 0;
			v = -1;
		}
		else if (m == 2) {
			h = 1;
			v = 0;
		}
		else {
			h = -1;
			v = 0;
		}
		bool kiemtra = true;
		for (int i = 0; i<p.size(); i++) 
		{
			p[i].x += h;
			p[i].y += v;
			if ((p[i].x <0 || p[i].y < 0) || !check(p[i])) {
				kiemtra = false;
				break;
			}
		}
		if (!kiemtra) {
			list.push_back(p1);
			return;
		}
		list.push_back(p);
		if (!(check(start) && check(goal))) {
			list.pop_back();
			list.push_back(p1);
			return;
		}
		kiemtra = true;
		for (int i = 0; i<list.size() - 1; i++)
			for (int j = 0; j<list[i].size(); j++)
				if (!checkPolygon(list[i][j], list.size() - 1)) kiemtra = false;
		if (!kiemtra) {
			list.pop_back();
			list.push_back(p1);
		}
	}
	void move() {
		int n = list.size();
		srand(10*time(NULL));
		for (int i = 0; i < n; i++) {
			int m = rand() % 4;
			movePolygon(0, m);
		}
	}
};