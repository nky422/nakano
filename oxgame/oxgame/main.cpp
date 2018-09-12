#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <array>
#include <memory>
#include <map>

using namespace std;

//�萔
namespace GAME
{
	constexpr int  BOARD_SIZE { 3 };
	constexpr int  ERROR_DATA { 999 };
	constexpr bool GAME_LOOP  { true };
	constexpr int  OX_MAX{ 3 };
}

namespace OX
{
	constexpr int NONE { 0 };
	constexpr int CIRCLE{ 1 };
	constexpr int XMARK{ 2 };

}

//�^
namespace TYPE
{
	template <typename T>
	using LINE = array < T, GAME::BOARD_SIZE>;
	using MAP = array < LINE<int>, GAME::BOARD_SIZE>;

	template <typename T>
	using VEC_LAN = map<int, T>;

	template <typename T>
	using UN_VEC_LAN = unique_ptr<VEC_LAN<T>>;
}

//�N���X�ʒu
class CPOS
{
public:
	int x;
	int y;
};
using CVEC = CPOS;

//�N���X�@�V�X�e��
template <typename T>
class CGame
{
public:
	CGame(T* board);
	bool Input(int ox);
private:
	T * m_board;
	int m_in_run;
};

//�N���X�@�{�[�h���
class CBoard
{
public:
	CBoard();
	bool CheckIfAreaQutside(int x, int y);
	void Draw();

private:
	inline void COUNT_DRAW(int x) { cout << "[" << setw(2) << x << "]"; }
	TYPE::MAP  m_board;
	TYPE::UN_VEC_LAN<CPOS> m_vec_lan;

	array<int, GAME::OX_MAX> m_ox;
};

//�{�[�h���\�b�h�Q
CBoard::CBoard()
{
	//�{�[�h�̏�����
	int board[GAME::BOARD_SIZE][GAME::BOARD_SIZE]
	{
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
	};
	memcpy(&m_board, board, sizeof(board));
	//�T�������H�H�H�H

	//�Z�~�̎擾���̏�����
	m_ox[OX::CIRCLE] = 0;
	m_ox[OX::XMARK]  = 0;
	m_ox[OX::NONE]   = 0;
}

//�z��̗̈�𒴂��Ă邩�ǂ���
bool CBoard::CheckIfAreaQutside(int x, int y)
{
	;//
}

//�Z���~��u��

//�`��
void CBoard::Draw()
{
	int count = 0;

	system("cls");
	for (auto &y : m_board)
	{

	}
}

//���C��
int main()
{
	//unipue_ptr<CBoard> Board(new CBoard());
}