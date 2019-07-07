from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

import os
import time
from datetime import timedelta
import subprocess
from datetime import datetime
import winsound
from mutagen.mp3 import MP3 as mp3
import pygame
import sys

target_dir_expectations = [
    "./../code(c++)/", "./code(c++)/", "./../code/", "./code/"]
target_dir = None

command_path_expectations = ["./../cplus.exe", "./cplus.exe"]
command_path = None

music_path_expectations = ["./music/", "./../music/"]
music_path = None

is_animal = False

is_cls = False

out_cospace_path_expectations = [os.path.expanduser('~') + '/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/', 'C:/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/',
                                 'D:/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/', 'C:/Microsoft Robotics Developer Studio 4/CS/User/Rescue/CsBot/']
out_cospace_path = None

command = ""

prev_saved_time = None

prev_dll_changed_time = None


def playMusic(filename, playTime=None):
    filename = music_path + filename
    pygame.mixer.init()
    pygame.mixer.music.load(filename)  # 音源を読み込み
    mp3_length = mp3(filename).info.length  # 音源の長さ取得
    pygame.mixer.music.play(1)  # 再生開始。1の部分を変えるとn回再生(その場合は次の行の秒数も×nすること)
    if playTime is None:
        time.sleep(mp3_length + 0.25)
    else:
        time.sleep(1)  # 再生開始後、音源の長さだけ待つ(0.25待つのは誤差解消)
    pygame.mixer.music.stop()  # 音源の長さ待ったら再生停止


class ChangeHandler(FileSystemEventHandler):
    def on_created(self, event):
        filepath = event.src_path
        filename = os.path.basename(filepath)
        print('%sができました' % filename)

    def on_modified(self, event):
        global prev_saved_time, prev_dll_changed_time
        filepath = event.src_path
        filename = os.path.basename(filepath)
        if prev_saved_time is not None and datetime.now() + timedelta(seconds=-30) <= prev_saved_time:
            return
        prev_saved_time = datetime.now()
        print(datetime.now().strftime("%Y/%m/%d %H:%M:%S"), end=' ')
        print('%sが変更されました' % filename)
        print(datetime.now().strftime("%Y/%m/%d %H:%M:%S"), end=' ')
        target_filenames = [".cpp", ".hpp", ".c", ".h"]
        for target_filename in target_filenames:
            if target_filename in filename:
                try:
                    winsound.Beep(3000, 200)
                except RuntimeError:
                    print("Runtime Error")
                print("コンパイルスタート")
                subprocess.run(command, shell=True)

                if prev_dll_changed_time is None or os.stat(out_cospace_path + "Ninja.dll").st_mtime != prev_dll_changed_time:
                    subprocess.run("strip --strip-unneeded " +
                                   "\"" + out_cospace_path + "Ninja.dll\"")
                    prev_dll_changed_time = os.stat(
                        out_cospace_path + "Ninja.dll").st_mtime
                    print(prev_dll_changed_time)
                    print("コンパイル成功")
                    if is_animal:
                        playMusic('cat-cry.mp3')
                    else:
                        try:
                            winsound.Beep(1000, 800)
                        except RuntimeError:
                            print("Runtime Error")

                else:
                    print("コンパイル失敗")
                    if is_animal:
                        playMusic('cat-threat.mp3')
                    else:
                        playMusic('error.mp3', 1)

                break

    def on_deleted(self, event):
        filepath = event.src_path
        filename = os.path.basename(filepath)
        print("%sを削除しました" % filename)


def main():
    global target_dir, command_path, command, out_cospace_path, music_path
    for investigating_target_dir in target_dir_expectations:
        if os.path.isdir(investigating_target_dir):
            target_dir = investigating_target_dir
            print("target dir : " + target_dir)
            break

    if target_dir is None:
        print("Error : there is no target dir")
        return

    for investigating_cospace_path in out_cospace_path_expectations:
        if os.path.isdir(investigating_cospace_path):
            out_cospace_path = investigating_cospace_path
            print("cospace dir : " + out_cospace_path)
            break

    if out_cospace_path is None:
        print("Error : no cospace path")
        return
    prev_dll_changed_time = os.stat(out_cospace_path + "Ninja.dll").st_mtime

    for investigating_command_path in command_path_expectations:
        if os.path.isfile(investigating_command_path):
            command_path = investigating_command_path
            print("command path : " + command_path)
            break

    if command_path is None:
        print("Error : there is no command")
        return

    for investigating_music_path in music_path_expectations:
        if os.path.isdir(investigating_music_path):
            music_path = investigating_music_path
            print("music path : " + music_path)
            break

    if music_path is None:
        print("Error : there is no music folder")
        return

    command = "\"" + command_path + "\"" + " --no-strip " + command

    while 1:
        event_handler = ChangeHandler()
        observer = Observer()
        observer.schedule(event_handler, target_dir, recursive=True)
        observer.start()
        while True:
            time.sleep(0.1)


command_list = ['--animal', '--help', '--cplus=']
if __name__ == '__main__':
    args = sys.argv
    for arg in args:
        if args.index(arg) == 0:
            continue
        elif arg == '--animal':
            is_animal = True
            print('mode : animal')
        elif arg == '--help':
            print(command_list)
            exit()
        elif '--cplus=' in arg:
            command = command + ' --' + arg[8:]
            print('cplus command : ' + arg[8:])
        else:
            print(arg + ' is not a command')
            print('correct commands is this')
            for cmd in command:
                print(cmd)
    main()
