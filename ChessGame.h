#pragma once
#include"AI.h"
#include"Man.h"
#include"Chess.h"
class ChessGame //����
{
public:
	//���ù��캯�����г�ʼ��
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();//������Ϸ��ʼ
private: //��ӳ�Ա
	Man* man;
	AI* ai;
	Chess* chess;
};

