#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
}

void ChessGame::play()
{
	chess->init();//对棋盘进行初始化
	while (1) {
		//由棋手先走
		man->go();
		if (chess->checkOver()) {
			chess->init();//对棋盘进行初始化
			continue;
		}
		//ai后走
		ai->go();
		if (chess->checkOver()) {
			chess->init();//对棋盘进行初始化
			continue;
		}
	}
}
