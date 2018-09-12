#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <array>
#include <memory>
#include <map>

using namespace std;

//定数
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

//型
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

//クラス位置
class CPOS
{
public:
	int x;
	int y;
};
using CVEC = CPOS;

//クラス　システム
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

//クラス　ボード情報
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

//ボードメソッド群
CBoard::CBoard()
{
	//ボードの初期化
	int board[GAME::BOARD_SIZE][GAME::BOARD_SIZE]
	{
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
	};
	memcpy(&m_board, board, sizeof(board));
	//探索方向？？？？

	//〇×の取得数の初期化
	m_ox[OX::CIRCLE] = 0;
	m_ox[OX::XMARK]  = 0;
	m_ox[OX::NONE]   = 0;
}

//配列の領域を超えてるかどうか
bool CBoard::CheckIfAreaQutside(int x, int y)
{
	;//
}

//〇か×を置く

//描画
void CBoard::Draw()
{
	int count = 0;

	system("cls");
	for (auto &y : m_board)
	{

	}
}

//メイン
int main()
{
	//unipue_ptr<CBoard> Board(new CBoard());
}