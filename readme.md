# How to use(使用方法)

## First(はじめに)

This is all of the source codes of team Ninja from Japan.

日本チーム「Ninja」のすべてのソースコードに入っています。

If there is any error or English syntax error, please contact me.

もし、ソースコードのエラーや、英語の文法的な間違いがあれば、指摘してもらえると嬉しいです。

If you want my source code quickly, please look at `code(c++)/Hikaru.cpp`.

もし、私のソースコードをすぐに見たければ、`code(c++)/Hikaru.cpp`を見てください

## OverView(概要)

There are 8 folders.

8つのフォルダーがあります。

> cospace2019-ninja-share
>
> ​	├	array2coordinate
>
> ​	├	auto dll generator(c++)
>
> ​	├	code(c)
>
> ​	├	code(c++)
>
> ​	├	dll generator(c)
>
> ​	├	dll generator(c++)
>
> ​	├ 	image2array
>
> ​	└	music

Each folder has software or program.

それぞれ、ソフトやプログラムが入っています。

For details, please read each folder's ReadMe.

詳しい説明は、それぞれのフォルダのReadMeを見てください。

### Array2Coordinate

This software is written by c++.  This software's purpose is to repesent wall positions as formula.

このソフトは、C++で書かれています。このソフトの目的は壁の座標を数式で表すことです。

If you put the array of the map to the software, the software returns the formulas of all wall position.

マップの情報をソフトに入力すると、ソフトはすべての壁を数式として出力します。

This makes it possible to calculate own robot coordinate in world 1.

このソフトは、World1で自分のロボットの座標を計算することに使えます。

## auto dll generator(c++)

If you are nerbous to run compiler every time you save the code, just use this foftware to auto compile.

もし、保存するたびにコンパイルするのが面倒なら、このソフトを使ってください。

This software will compile your source code automatically. This software compiles your code when it detects the changes of your source codes.

このソフトは、あなたのソースコードを自動でコンパイルします。このソフトは、あなたのソースコードが変更されたことを検知したときにコンパイルします。

## code(c)

This folder has cospace source code written in C-language. However, I last time I used C-language for rescue simulation was a ancient period. So, you should not use this source code. It has bugs, and old way.

このフォルダには、Cospace用のC言語でかかれたソースコードが入っています。しかし、僕が最後にC言語を使っていたのは古代のことなので、使わないほうが良いです。バグが入っていますし、古い手法です。

## code(c++)

This folder has cospace source code written in C++-language. This is the latest version. I became the champion of WorldCup 2019.

keywords: Dijkstra, Astar, Odometory

##  dll generator(c)

This is the compiler for C-language. This compiler search all `.c` files in `code(c)` and compile it. So, you don't need to type a complicated command to run compiler. Just run it in command prompt or duble click it.


## dll generator(C++)

This is the compiler for C++-language. This compiler search all `.cpp` files in `code(c++)` and compile it. The other sentences are same as `dll generator(c)`.

## image2array

This software convert image of cospace to arrays. This way is not useful from 2019 rules because we can't know the map infomation before.

But in world1, you can use this.

## music

This folder has some sound effects for auto dll generator. You can custamize by editing souce code of auto dll generator or just replace the files.



## Required to use my source code

Please be open to the other teams. I want to increase all team's level.

