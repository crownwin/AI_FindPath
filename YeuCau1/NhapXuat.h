#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include <vector>
#include "searching.h"
using namespace std;

graph readData(string name)
{
	fstream f;
	f.open(name, ios::in);

	graph g;

	f >> g.N;

	f >> g.start >> g.end;

	g.adj = new int*[g.N];
	for (int i = 0; i < g.N; i++) 
	{
		g.adj[i] = new int[g.N];
		for (int j = 0; j <g.N; j++)
			f >> g.adj[i][j];
	}

	g.h = new int[g.N];
	for (int i = 0; i < g.N; i++)
		f >> g.h[i];

	f.close();

	return g;
}

void printResult(string name, int isExist, vector<int> ttd, vector<int> dd)
{
	fstream f;
	f.open(name, ios::out); 

	if (isExist)
	{
		for (int i = 0; i < ttd.size(); i++)
			f << ttd[i] << " ";
		
		f << endl;
		
		for (int i = 0; i < dd.size(); i++)
			f << dd[i] << " ";

	}

	f.close();
}

void printDFS(graph g, string name)
{
	vector<int> thuTuDuyet;
	vector<int> duongDi;
	int isExist = dfs(g.adj, g.N, g.start, g.end, thuTuDuyet, duongDi);
	printResult(name, isExist, thuTuDuyet, duongDi);
}

void printBFS(graph g, string name)
{
	vector<int> thuTuDuyet;
	vector<int> duongDi;
	int isExist = bfs(g.adj, g.N, g.start, g.end, thuTuDuyet, duongDi);
	printResult(name, isExist, thuTuDuyet, duongDi);
}

void printUCS(graph g, string name)
{
	vector<int> thuTuDuyet;
	vector<int> duongDi;
	int isExist = ucs(g.adj, g.N, g.start, g.end, thuTuDuyet, duongDi);
	printResult(name, isExist, thuTuDuyet, duongDi);
}

void printGreedy(graph g, string name)
{
	vector<int> thuTuDuyet;
	vector<int> duongDi;
	int isExist = gbfs(g.adj, g.h, g.N, g.start, g.end, thuTuDuyet, duongDi);
	printResult(name, isExist, thuTuDuyet, duongDi);
}

void printAStar(graph g, string name)
{
	vector<int> thuTuDuyet;
	vector<int> duongDi;
	int isExist = astar(g.adj, g.h, g.N, g.start, g.end, thuTuDuyet, duongDi);
	printResult(name, isExist, thuTuDuyet, duongDi);
}