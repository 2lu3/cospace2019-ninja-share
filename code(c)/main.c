#include "CospaceSettings.h"
#include "CommonTools.h"
#include "masuda.h"
#include "Hikaru.h"
#include "HIKARU2.h"

// sprintfのエラーを無視するため
#define _CRT_SECURE_NO_WARNINGS 1

/*
	命名規則名	先頭	区切り	適用先
	PascalCase	大		大		クラス名
	camelCase	小		大		メソッド名、関数名
	snake_case	全て小	_		変数名、メンバ名、ファイル名
	SNAKE_CASE	全て大	_		マクロ名、定数、列挙体
	ただし、Cospaceで既に決まっている変数は上に従わない(Cospaceで定まっているものに同じ形式に変数名を変更する？)
	また、数字などの関係で視認性が悪いときもこれに従わなくて良い
*/
/*
	気をつけること
	・関数の引数がない場合、引数にvoidを入れること。引数がなにもない関数に引数を渡すと、全く別の変数の値が書き換わる。voidを入れると、引数を入れた時点でエラー表示が出る
	・
*/

/*	インクルードについて
ヘッダファイル同士が依存関係を持つことがないようにする
![image](out/include_files/include_files.svg)
*/

void Game0()
{
	if (getRepeatedNum() == 0)
	{
		commonSetup0();
		m_localGameSetup0();
		// localGameSetup0();
	}
	commonLoopStart0();
	m_Game0();
	// localGame0();
	commonLoopEnd0();
}

void Game1()
{
	if (getRepeatedNum() == 0 || (log_x == -1 && log_y == -1))
	{
		commonSetup1();
		localGameSetup1();
	}
	commonLoopStart1();
	localGame1();
	commonLoopEnd1();
}
