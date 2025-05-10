#pragma once
typedef enum {
	CHESS_WHITE = -1,  // �׷�
	CHESS_BLACK = 1    // �ڷ�
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
};

class Chess
{
public:
	// ���̵ĳ�ʼ��
	void init();

	// �ж���ָ������λ�ã��Ƿ�����Ч���
	// �������Ч���������Ч�����λ��,�����ڲ���pos��
	bool clickBoard(int x, int y, ChessPos* pos);

	// �����̵�ָ��λ��, ����
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// ��ȡ���̵Ĵ�С��13�ߡ�15�ߡ�19�ߣ�
	int getGradeSize();

	// ��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// �ж�����Ƿ����
	bool checkOver();
};

