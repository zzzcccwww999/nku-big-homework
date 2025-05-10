#pragma once
#include"AI.h"
#include"Man.h"
#include"Chess.h"
class ChessGame //控制
{
public:
	//利用构造函数进行初始化
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();//控制游戏开始
private: //添加成员
	Man* man;
	AI* ai;
	Chess* chess;
};

