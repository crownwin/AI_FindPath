#pragma once 
#include <iostream>
using namespace std;

struct graph
{
	int N;				// Số đỉnh của đồ thị
	int start, end;		// Đỉnh bắt đầu tìm kiếm và đỉnh kết thúc tìm kiếm
	int **adj;			// Ma trận kề của các đỉnh trong đồ thị
	int *h;				// Mảng chứa Heuristic của từng đỉnh trong đồ thị
};