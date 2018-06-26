#include "stdafx.h"
#include "Ai.h"

Ai::Ai()
{
}


Ai::~Ai()
{
}

bool Ai::hasNeighbor(int x, int y,int step) {
	int tx, ty;
	if (step == 1) {
		for (int i = 0; i < 8; i++) {
			tx = x + dir[i][0];
			ty = x + dir[i][1];
			if (tx >= size || tx < 0 || ty >= size || ty < 0)
				continue;
			if (board[tx][ty] != 0) {
				return true;
			}
		}
	}
	if (step == 2) {
		for (int i = 0; i < 8; i++) {
			tx = x + dir[i][0];
			ty = y + dir[i][1];
			if (tx >= size || tx < 0 || ty >= size || ty < 0)
				continue;
			int ttx, tty;
			for (int j = 0; j < 8; j++) {
				ttx = tx + dir[j][0];
				tty = tx + dir[j][1];
				if (ttx >= size || ttx < 0 || tty >= size || tty < 0)
					continue;
				if (board[ttx][tty] != 0) {
					return true;
				}
			}
		}
	}
	return false;
}
Point Ai::maxmin(int deep) {
	int best = MIN;
	auto points = gen(deep);
	for (int i = 0; i < points.size(); i++) {
		auto p = points[i];
		board[p.x][p.y];
		auto v = min(deep - 1);
	}
}
int Ai::min(int deep,int alpha,int beta) {
	int v = evaluate();     //重点来了，评价函数，这个函数返回的是对当前局势的估分。
	if (deep <= 0 || win()) {
		return v;
	}

	int best = MAX;
	auto points = gen(deep);

	for (int i = 0; i<points.size(); i++) {
		auto p = points[i];
		board[p.x][p.y] = hum;
		int v = max(deep - 1, best < alpha ? best : alpha, beta);
		board[p.x][p.y] = empty;
		if (v < best) {
			best = v;
		}
		if (v < beta) 
			break;
	}
	return best;
}
int Ai::max(int deep,int alpha,int beta) {
	int v = evaluate();
	if (deep <= 0 || win(board)) {
		return v;
	}

	int best = MIN;
	auto points = gen(deep);

	for (int i = 0; i<points.size(); i++) {
		auto p = points[i];
		board[p.x][p.y] = com;
		int v = min(deep - 1, alpha, best > beta ? best : beta);
		board[p.x][p.y] = empty;
		if (v > best) {
			best = v;
		}
		if (v > alpha)
			break;
	}
	return best;
}
vector<Point> Ai::gen(int deep) {
	vector<Point> neighbors;
	vector<Point> nextNeighbors;

	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			if (board[i][j] == empty) {
				if (hasNeighbor(i,j,1)) { //必须是有邻居的才行
					neighbors.push_back(Point(i,j));
				}
				else if (deep >= 2 && hasNeighbor(i,j,2)) {
					nextNeighbors.push_back(Point(i,j));
				}
			}
		}
	}
	return neighbors;
}
bool Ai::win(int x,int y) {
	// four directs
	int cnt = 0;
	int i, j;
	int tx, ty;
	for (i = 0; i < 4; i++) {
		cnt = 0;
		for (j = -4; j <= 4; j++) {
			tx = x + dir_judge[i][0] * j;
			ty = y + dir_judge[i][1] * j;
			if (tx >= size || tx < 0 || ty >= size || ty < 0)
				continue;
			if (board[tx][ty] == com)
				cnt++;
			if (cnt == 5)
				return true;
		}
	}
	return false;
}