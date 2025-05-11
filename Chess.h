#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
typedef enum {
	CHESS_WHITE = -1,  // 白方
	CHESS_BLACK = 1    // 黑方
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
};

class Chess
{
public:
	//利用构造函数初始化
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	// 棋盘的初始化
	void init();

	// 判断在指定坐标位置，是否是有效点击
	// 如果是有效点击，把有效点击的位置,保存在参数pos中
	bool clickBoard(int x, int y, ChessPos* pos);

	// 在棋盘的指定位置, 落子
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// 获取棋盘的大小（13线、15线、19线）
	int getGradeSize();

	// 获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// 判断棋局是否结束
	bool checkOver();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	int gradeSize;//棋盘大小（13，15，17，19）
	int margin_x;//棋盘左侧边界大小
	int margin_y;//棋盘上边缘大小
	float chessSize;//棋子大小，即格子大小
	//表示当前棋局上棋子的分布情况.0为空白；1为黑子；-1为白子
	vector<vector<int>>chessMap;//如chessMap[3][5]表示棋盘第三行第五列的落子情况
	bool playerFlag;//表示现在该哪一方落子，true:该黑棋落子； flase:该白棋落子
};

