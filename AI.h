#pragma once
#include"Chess.h"
class AI
{
public:
	void init(Chess* chess);//利用棋盘的数据进行AI的初始化
	void go();
private:
	Chess* chess;
	vector<vector<int>>scoreMap;

private:
	void caculateScore();
	ChessPos think();
};

