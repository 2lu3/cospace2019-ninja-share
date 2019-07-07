# Code Collectorとは (Japanaese)

Code Collectorは、C言語で複数ファイルに分けているソースコードを1つのソースコードにまとめるものである。

## 前提条件
ソースコードのみを、codeという名前のフォルダーに入れる。
また、`code_collector.py`または`code_collector.exe`を、codeという名前のフォルダーが入っているフォルダーの中に入れる。

## Pythonをインストールしている場合
コマンドプロンプトで

> python code_collector.py

と実行する。

## Pythonをインストールしていない場合

`code_collector.exe`をダブルクリックして実行する


# What is "Code Collector"

Code Collector is a tool to merge separated C-language files into one .c file.
For example, there are 3 files. main.c, cospace.h, cospace.c. This tool merge these 3 files into new_main.c automatically.

## Requirement

Put all C-language source codes into a folder named `code`. The `code` can not have any other files. And put `code_collector.py` or `code_collector.exe` in the folder which contains the `code` folder.

## If you have python

Please Run this command on command prompt.

> python code_collector.py

## If you don't have python

Double click `code_collector.exe'.


# 更新履歴

code_collector.py : 2019-02-18
code_collector.exe : 2019-02-18
ReadMe.md : 2019-02-18
ReadMe.pdf : 2019-02-18
