# dll generatorの使い方(How to use dll generator(c))

Dll generator makes dll file for cospace automatically.

dll generatorは、Cospace用のdllファイルを自動で作成するツールである。

This dll generator will compile all `.c` files in `code` folder or `code(c)` folder to one dll file.

原理は、`code` または `code(c)` というフォルダーに入っている拡張子が`.c`のファイルを検索し、それらすべてをまとめてコンパイルする。

So, you must not input any `.c` file unrelated to cospace.

そのため、Cospaceに関係ない`.c`のファイルはcodeのフォルダーの中に入れてはならない。

## Pythonをインストールしている場合(If you have python)

dll_generator.pyをコピーして、以下のようなフォルダー構造にしなければならない。

copy `dll_generator.py` and must restructure like the graph.

> folder/<br>
> 　├ code/<br>
> 　│　└ main.c<br>
> 　│　└ tools.c<br>
> 　│　└ tools.h<br>
> 　└ dll_generator.py

`python dll_generator.py`とコマンドプロンプトで実行する。

Run `python dll_generator.py` in command prompt.

## Pythonをインストールしていない場合(If you don't have python)

copy `dll_generator.exe` and must restructure like the graph.

dll_generator.exeをコピーして、以下のようなフォルダー構造にしなければならない。

> folder/<br>
> 　├ code/<br>
> 　│　└ main.c<br>
> 　│　└ tools.c<br>
> 　│　└ tools.h<br>
> 　└ dll_generator.exe

その後、dll_generator.exeを実行すればよい。

Run `dll_generator.exe` in command prompt.

## コマンドラインオプション一覧(all command options)

- --help
  - コマンドオプション一覧を表示する
  - show all commands
- --debug
  - debugモードで実行する
  - run in debug mode
- --outhere
  - Ninja.dllを、dll_generator(c++)がある場所に生成する
  - Generate `Ninja.dll` to current directory.
- --outcospace
  - Ninja.dllを、`/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/`の中に生成する
  - Generate `Ninja.dll` to `/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/`.
- --no-lite-warming
  - 重要度の低い警告を無視する
  - Ignore lite warmings

## 最終更新日時

* `ReadMe.md` : 2019/07/07
* `ReadMe.pdf` : 2019/07/07
* `dll_generator.py` : 2019/07/07
* `dll_generator.exe` : 2019/07/01
