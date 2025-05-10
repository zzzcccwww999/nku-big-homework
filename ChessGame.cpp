#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
}

void ChessGame::play()
{
	chess->init();//�����̽��г�ʼ��
	while (1) {
		//����������
		man->go();
		if (chess->checkOver()) {
			chess->init();//�����̽��г�ʼ��
			continue;
		}
		//ai����
		ai->go();
		if (chess->checkOver()) {
			chess->init();//�����̽��г�ʼ��
			continue;
		}
	}
}
