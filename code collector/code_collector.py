import glob
import re

origin_dir_path = './code/'

main_data = None
new_main = None

included_list = []


# 多重インクルード回避
def isIncludeLineCheck(line):
    line = line.replace(' ', '')
    result = re.search("#include\"\w+.h\"", line)
    if result is not None:
        line = result.group()
        return line
    else:
        return None


def Interpreter(data):
    for line in data:
        is_include_line = isIncludeLineCheck(line)
        # 多重インクルード回避
        if is_include_line is not None:
            # インクルード文が含まれている場合
            if not is_include_line in included_list:
                # ヘッダファイルがまだインクルードされていない場合
                included_list.append(is_include_line)
                # ヘッダファイル読み込み
                file_name = is_include_line[9:-1]
                data = open(origin_dir_path + file_name, 'r', encoding='utf-8')
                Interpreter(data)
            continue

        # 上のどれにも当てはまらない場合
        new_main.write(line)


def main():
    global main_data, new_main
    main_data = open(origin_dir_path + 'main.c', mode='r', encoding="utf-8")
    new_main = open('Ninja.c', mode='w', encoding="utf-8")
    Interpreter(main_data)
    # ソースファイルを最後に埋め込む
    for c_file in included_list:
        c_file = c_file[9:-2] + 'c'
        data = open(origin_dir_path + c_file, mode='r', encoding='utf-8')
        new_main.writelines(data.readlines())

    main_data.close()
    new_main.close()

    print("ソースコードのマージに成功しました")


if __name__ == '__main__':
    main()
