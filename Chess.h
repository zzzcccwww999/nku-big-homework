#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
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
	//���ù��캯����ʼ��
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
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
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	int gradeSize;//���̴�С��13��15��17��19��
	int margin_x;//�������߽��С
	int margin_y;//�����ϱ�Ե��С
	float chessSize;//���Ӵ�С�������Ӵ�С
	//��ʾ��ǰ��������ӵķֲ����.0Ϊ�հף�1Ϊ���ӣ�-1Ϊ����
	vector<vector<int>>chessMap;//��chessMap[3][5]��ʾ���̵����е����е��������
	bool playerFlag;//��ʾ���ڸ���һ�����ӣ�true:�ú������ӣ� flase:�ð�������
};

