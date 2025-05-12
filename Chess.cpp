#include "Chess.h"
#include<mmsystem.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")
//使图片边缘透明化的接口
void putimagePNG(int x, int y, IMAGE* picture)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture
	int picture_width = picture->getwidth(); //获取picture的宽度
	int picture_height = picture->getheight(); //获取picture的高度
	int graphWidth = getwidth();       //获取绘图区的宽度
	int graphHeight = getheight();     //获取绘图区的高度
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   
			int sb = src[srcX] & 0xff;              
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
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
	//创建棋盘窗口
	initgraph(897, 895, EX_SHOWCONSOLE);
	//显示棋盘图片
	loadimage(0, "res/棋盘2.jpg");
	mciSendString("play res/start.wav", 0, 0, 0);
	//加入黑棋和白棋的图片
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	//每轮结束，清空棋盘
	for (int i = 0; i < chessMap.size(); i++) {
		for (int j = 0; j < chessMap[i].size(); j++) {
			chessMap[i][j] = 0;
		}
	}
	//黑棋先行
	playerFlag = true;

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	//计算左上角在第几行第几列
	int col = (x - margin_x) / chessSize;//列
	int row = (y - margin_y) / chessSize;//行
	int leftTopPosX = margin_x + col * chessSize;//左上角X坐标
	int leftTopPosY = margin_y + row * chessSize;//左上角Y坐标
	int offest = chessSize * 0.4;//设置极限值
	bool ret = false;
	int len;//棋子到某个角的距离
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
		//右上角判断
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
		//左下角判断
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
		//右下角判断
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


void Chess::chessDown(ChessPos * pos, chess_kind_t kind)//实现落子功能
{
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	//判断下黑棋还是白棋
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
	playerFlag = !playerFlag;//实现黑白方交换
}
