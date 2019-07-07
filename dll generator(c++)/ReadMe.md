# dll generator(c++)の使い方(How to use dll generator(c++))

## For English user

Please see the ReadMe in dll generator(c).

It's same user guide.

## Abstract

dll generatorは、Cospace用のdllファイルを自動で作成するツールである。

原理は、`code`というフォルダーに入っている拡張子が`.cpp`のファイルを検索し、それらすべてをまとめてコンパイルする。
そのため、Cospaceに関係ない`.cpp`のファイルはcodeのフォルダーの中に入れてはならない。

## Pythonをインストールしている場合

dll_generator.pyをコピーして、以下のようなフォルダー構造にしなければならない。

> 適当なフォルダー/<br>
> 　├ code/<br>
> 　│　└ main.cpp<br>
> 　│　└ tools.cpp<br>
> 　│　└ tools.hpp<br>
> 　└ dll_generator.py

`python dll_generator.py`とコマンドプロンプトで実行する。

## Pythonをインストールしていない場合

`cplus.exe`をコピーして、以下のようなフォルダー構造にしなければならない。

> 適当なフォルダー/<br>
> 　├ code/<br>
> 　│　└ main.cpp<br>
> 　│　└ tools.cpp<br>
> 　│　└ tools.hpp<br>
> 　└ cplus.exe

その後、`cplus.exe`を実行すればよい。


## コマンドラインオプション一覧

- --help
  - コマンドオプション一覧を表示する
- --debug
  - debugモードで実行する
- --outhere
  - Ninja.dllを、dll_generator(c++)がある場所に生成する
- --outcospace
  - Ninja.dllを、`/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/`の中に生成する
- --no-lite-warming
  - 重要度の低い警告を無視する

## 最終更新日時

* ReadMe.md : 2019-06-10 18:50:56
* ReadMe.pdf : 2019-06-10 18:51:03
* dll_generator.py : 2019-04-13 10:10:24
* dll_generator.exe : 2019-04-13 10:10:29
