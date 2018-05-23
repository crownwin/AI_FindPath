#include <iostream>
#include "NhapXuat.h"
#include "graph.h"
using namespace std;

int main()
{
	graph g = readData("input.txt");

	printDFS(g, "dfs.txt");
	
	printBFS(g, "bfs.txt");
	
	printUCS(g, "ucs.txt");
	
	printGreedy(g, "gbfs.txt");

	printAStar(g, "astar.txt");

	return 0;
}