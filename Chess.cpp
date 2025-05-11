#include "Chess.h"
#include<mmsystem.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	for (int i = 0; i < gradeSize; i++) {
		vector<int>row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}

}

void Chess::init()
{
	//�������̴���
	initgraph(897, 895, EX_SHOWCONSOLE);
	//��ʾ����ͼƬ
	loadimage(0, "res/����2.jpg");
	mciSendString("play res/start.wav", 0, 0, 0);
	//�������Ͱ����ͼƬ
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	//ÿ�ֽ������������
	for (int i = 0; i < chessMap.size(); i++) {
		for (int j = 0; j < chessMap[i].size(); j++) {
			chessMap[i][j] = 0;
		}
	}
	//��������
	playerFlag = true;

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	//�������Ͻ��ڵڼ��еڼ���
	int col = (x - margin_x) / chessSize;//��
	int row = (y - margin_y) / chessSize;//��
	int leftTopPosX = margin_x + col * chessSize;//���Ͻ�X����
	int leftTopPosY = margin_y + row * chessSize;//���Ͻ�Y����
	int offest = chessSize * 0.4;//���ü���ֵ
	bool ret = false;
	int len;//���ӵ�ĳ���ǵľ���
	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offest) {
			pos->col = col;
			pos->row = row;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		//���Ͻ��ж�
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offest) {
			pos->col = col + 1;
			pos->row = row;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
		x2 = leftTopPosX;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offest) {
			pos->col = col;
			pos->row = row + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offest) {
			pos->col = col + 1;
			pos->row = row + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
	} while (0);
	return ret;
}


void Chess::chessDown(ChessPos * pos, chess_kind_t kind)
{
}

int Chess::getGradeSize()
{
	return 0;
}

int Chess::getChessData(ChessPos* pos)
{
	return 0;
}

int Chess::getChessData(int row, int col)
{
	return 0;
}

bool Chess::checkOver()
{
	return false;
}
