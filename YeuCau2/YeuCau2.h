#pragma once

#include "resource.h"
#include<gdiplus.h>
using namespace Gdiplus; 
#pragma comment (lib, "Gdiplus.lib")

#include <math.h>
#include "map.h"
#include "astar.h"

MAP map("map.txt");

#define SPEED 5
#define MOVING 10

vector<Point2D> findAstar(MAP &map)
{
	ASTAR astar;

	return astar.find(map);
}

void drawPath(MAP &map, HDC hdc)
{
	int SCALE = 4;

	vector<CPolygon> list = map.getList();
	Graphics graphics(hdc);
	Pen penPoLy(Color(255, 0, 0, 255));
	for (int j = 0; j < list.size(); j++)
	{
		int n = list[j].size();
		Point* a = new Point[n];
		for (int i = 0; i < n; i++)
		{
			a[i].X = list[j][i].x * SCALE;
			a[i].Y = list[j][i].y * SCALE;
		}

		graphics.DrawPolygon(&penPoLy, a, n);

		Point s, g;
		s.X = map.getStart().x * SCALE;
		s.Y = map.getStart().y * SCALE;
		g.X = map.getGoal().x * SCALE;
		g.Y = map.getGoal().y * SCALE;
		delete[]a;
	}
	vector<Point2D> path = findAstar(map);

	ofstream f;
	f.open("output.txt");
	
	if (path.size() != 0)
	{
		
		f << "length of path is: ";
		float length = 0;
		for (int i = 0; i < path.size() - 1; i++)
			length += distance(path[i], path[i + 1]);
		f << length;
		
		int n = path.size();
		Point* a = new Point[n];
		for (int i = 0; i < n; i++)
		{
			a[i].X = path[i].x * SCALE;
			a[i].Y = path[i].y * SCALE;
		}
		Pen penLine(Color(255, 255, 0, 0));
		for (int i = 0; i < n - 1; i++)
			graphics.DrawLine(&penLine, a[i], a[i + 1]);
		delete[]a;
	}
	else
		f << "No existed Path.";

	f.close();
}