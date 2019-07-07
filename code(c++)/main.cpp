#include "CospaceSettings.hpp"
#include "CommonTools.hpp"
#include "Hikaru.hpp"
#include "Masuda.hpp"
#include "Superteam.hpp"
// #include "AutoStrategy2019.hpp"
#include <bits/stdc++.h>

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

using namespace std;

// Game0_Hikaru game0;
//Game0_Masuda game0;
Game0_Superteam game0;
Game1_Hikaru game1;
// Game1_Masuda game1;
// AutoStrategy game1;

int triger = 0;

void Game0()
{
	 if (getRepeatedNum() == 0)
	 {
	 	game0.setup();
	 }

	 if (game0.shouldTeleport())
	 {
	 	game0.taskOnTeleport();
	 }
	 else
	 {
	 	game0.loop();
	 }
}

void Game1()
{
	if (getRepeatedNum() == 0 || triger == 0)
	{
		game1.setup();
		triger = 1;
	}
	game1.loop();
}
