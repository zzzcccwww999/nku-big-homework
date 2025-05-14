#pragma once
#include"Chess.h"
class AI
{
public:
	void init(Chess* chess);//�������̵����ݽ���AI�ĳ�ʼ��
	void go();
private:
	Chess* chess;
	vector<vector<int>>scoreMap;

private:
	void caculateScore();
	ChessPos think();
};

