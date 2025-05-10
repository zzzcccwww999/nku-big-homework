#pragma once
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
};

