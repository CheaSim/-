/*
code by CheaSim 
in Nanjing tech university
*/
#define  _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#ifndef Gomoku_H_
#include<iostream>
#include<cmath>
#include <set>
#include <vector>
using std::set;
using std::vector;
inline int Max(int a, int b) {
	return (a > b) ? a : b;
}
inline int Min(int a, int b) {
	return (a < b) ? a : b;
}
struct score {
	int ONE = 10;
	int TWO = 100;
	int THREE = 1000;
	int FOUR = 100000;
	int FIVE = 10000000;
	int BLOCK_ONE = 1;
	int BLOCK_TWO = 10;
	int BLCOK_THREE = 100;
	int BLOCK_FOUR = 1000;
};
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) :x(x), y(y) {}
};
class Ai {
public:
	class Cmp {
	public:
		bool operator() (const Point& p1, const Point& p2) const {
			if (p1.x == p2.x)
				return p1.y < p2.y;
			else
				return p1.x < p2.x;
		}
	};
public:
	//judge if the game ends
	bool isEnd(int x, int y);
	static const int searchDeep = 4;    //搜索深度  
	static const int size = 15;   //棋盘大小  
	bool isFinished = false;
	void putChess(int x, int y);
	bool isBlack = false;
	set<Point,Cmp> toJudge; // ai可能会下棋的点  
private:
	//1 means black -1 means white 0 means empty
	int board[17][17];
	bool isFinished = false;
	//the size of chessboard
	int size = 15;
	bool hasNeighbor(int x,int y,int step);
	const int dir[8][2] = { 0,1,0,-1,1,0,-1,0,   1,1,-1,1,1,-1,-1,-1 };
	const int dir_judge[4][2] = { 0,1 ,1,1 ,1,0 ,1,-1 };
	bool win(int x,int y);
	int serachDeep;
	int comMaxScore;
	int humMaxScore;
	int countToScore(int count, int block, bool empty);
	Point maxmin(int deep);
	int min(int deep,int alpha,int beta);
	int max(int deep,int alpha,int beta);
	vector<Point> gen(int deep);
	const int MAX = 1 << 28;
	const int MIN = -MAX;
	const int hum = 1;
	const int com = -1;
	const int empty = 0;
};
#endif