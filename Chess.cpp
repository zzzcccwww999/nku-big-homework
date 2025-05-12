#include "Chess.h"
#include<mmsystem.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")
//ʹͼƬ��Ե͸�����Ľӿ�
void putimagePNG(int x, int y, IMAGE* picture)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ��
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ��
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ��
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   
			int sb = src[srcX] & 0xff;              
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         
					| (sb * sa / 255 + db * (255 - sa) / 255);              
			}
		}
	}
}

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


void Chess::chessDown(ChessPos * pos, chess_kind_t kind)//ʵ�����ӹ���
{
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	//�ж��º��廹�ǰ���
	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
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

void Chess::updateGameMap(ChessPos* pos)
{
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;//ʵ�ֺڰ׷�����
}
