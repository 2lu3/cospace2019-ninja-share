import tkinter as tk
import time
from PIL import Image, ImageTk
import cv2
import os
import sys
sys.setrecursionlimit(10000000)
image_width = None
image_height = None
margin = 20
button_margin = 120
magnification = 20

image_rgb = None
canvas = None
image_pil = None
tkimg = None
show_option = 0
paint_option = 0
listShowMode = None
listPaintBrush = None

# 0 : オブジェクトのみ
# 1 : 地形のみ
mode = 0

border_area_object = 5
button_labels = ["White", "Yellow", "Wall", "Swampland",  "Deposit", "SuperArea", "Red", "Cyan", "Black"]
button_values = [1, 2, 3, 4, 5, 6, 7, 8, 9]
registered_color = [
        [255, 255, 255], # white
        [255, 255, 0], # yellow
        [221, 186, 151], # wall
        [166, 166, 166], # swampland
        [255, 153, 0], # deposit
        [0, 176, 240], # superarea
        [237, 28, 36], # red
        [63, 72, 204], # cyan
        [0, 0, 0] # black
    ]
map_data = None

start_x = 0
start_y = 0
moving_x = 0
moving_y = 0
end_x = 0
end_y = 0

def reloadImage():
    global tkimg, image_rgb, image_pil, map_data, registered_color, canvas, show_option


    if show_option == 0: # マップ情報のみ
        for hi in range(image_height):
            for wj in range(image_width):
                image_rgb[hi][wj] = registered_color[map_data[hi][wj].index(1)]
    elif show_option == 1 or show_option == 2 or show_option == 3: # Objectのみ
        object_label_index = border_area_object + show_option
        white_label_index = button_labels.index("White")
        for hi in range(image_height):
            for wj in range(image_width):
                # Yellow, Wall, Depositは上書き禁止
                if map_data[hi][wj][object_label_index] == 1:
                    image_rgb[hi][wj] = registered_color[object_label_index]
                else:
                    image_rgb[hi][wj] = registered_color[map_data[hi][wj].index(1)]
                    if map_data[hi][wj].index(1) > border_area_object:
                        print("error")





    image_pil = Image.fromarray(image_rgb)
    tkimg = ImageTk.PhotoImage(image_pil)
    canvas.create_image(margin, margin, image=tkimg, anchor=tk.NW)


def onClickLoadData(event):
    global map_data
    map_data = [[[0 for i in range(len(button_labels))] for j in range(image_width)] for k in range(image_height)]
    width = int(image_width / magnification)
    height = int(image_height / magnification)
    with open("output.txt", mode='r') as f:
        line = []
        for i in range(height + 1):
            line.append(f.readline().split())
        del line[-1]
        for hi in range(height):
            for wj in range(width):
                for hi_add in range(magnification):
                    for wj_add in range(magnification):
                        map_data[hi * magnification + hi_add][wj * magnification + wj_add][int(line[hi][wj])] = 1

        for i in range(3):
            line = []
            for j in range(height + 1):
                line.append(f.readline().split())
            del line[-1]
            for hi in range(height):
                for wj in range(width):
                    for hi_add in range(magnification):
                        for wj_add in range(magnification):
                            map_data[hi * magnification + hi_add][wj * magnification + wj_add][i + border_area_object + 1] = int(line[hi][wj])
    # pass



def onClickOutput(event):
    output_width = int(image_width / magnification)
    output_height = int(image_height / magnification)
    output_map = [[[0 for i in range(4)] for j in range(output_width)] for k in range(output_height)]
    for hi in range(output_height):
        for wj in range(output_width):
            max_id = 0
            max_num = 0
            is_object = [0, 0, 0]
            num = [0 for i in range(border_area_object + 1)]
            for hi_add in range(magnification):
                for wj_add in range(magnification):
                    for k in range(3):
                        if map_data[hi * magnification + hi_add][wj * magnification + wj_add][border_area_object + k + 1] == 1:
                            is_object[k] = 1
                    for k in range(border_area_object + 1):
                        if map_data[hi * magnification + hi_add][wj * magnification + wj_add][k] == 1:
                            num[k] += 1
            for k in range(border_area_object + 1):
                if num[k] > max_num:
                    max_num = num[k]
                    max_id = k
            output_map[hi][wj][0] = max_id
            # print(str(hi) + " " + str(wj) + " " + str(max_id))
            for k in range(3):
                # print(is_object[k])
                output_map[hi][wj][k + 1] = is_object[k]

    with open("output.txt", mode='w') as f:
        for k in range(4):
            for hi in range(output_height):
                for wj in range(output_width):
                    f.write(str(output_map[hi][wj][k]) + " ")
                f.write("\n")
            f.write("\n")
        f.write("\n")

    with open("output_array.txt", mode='w') as f:
        array_name = ["map_output_data", "red_data", "cyan_data", "black_data"]
        for k in range(4):
            f.write("int " + array_name[k] + "[" + str(output_height) + "][" + str(output_width) + "] = {")
            for hi in range(output_height):
                f.write("{")
                for wj in range(output_width - 1):
                    f.write(str(output_map[hi][wj][k]) + ",")
                f.write(str(output_map[hi][output_width - 1][k]))
                if hi != output_height - 1:
                    f.write("},\n")
                else:
                    f.write("}\n")
            f.write("};\n")
            f.write("\n")
        f.write("\n")



    print("finished")

def onImageClick(event):
    global start_x, start_y
    start_x = event.x
    start_y = event.y

def onImageMotion(event):
    global start_x, start_y, canvas, moving_x, moving_y
    canvas.delete("temp")
    moving_x = event.x
    moving_y = event.y
    canvas.create_rectangle(start_x, start_y, moving_x, moving_y, width = 1, outline = "black", tag = "temp")


def onImageRelease(event):
    global start_x, start_y, end_x, end_y, image_rgb, image_pil, tkimg
    canvas.delete("temp")

    if show_option == 0:
        # マップのみ
        if paint_option > border_area_object:
            print("failed")
            return
    else:
        if show_option + border_area_object != paint_option:
            print("failed")
            return


    end_x = event.x
    end_y = event.y

    start_x -= margin
    start_y -= margin
    end_x -= margin
    end_y -= margin

    if show_option == 0:
        for hi in range(start_y, end_y):
            for wj in range(start_x, end_x):
                if hi < 0 or hi >= image_height or wj < 0 or wj >= image_width:
                    continue
                else:
                    for k in range(border_area_object + 1):
                        map_data[hi][wj][k] = 0
                    map_data[hi][wj][paint_option] = 1
    else:
        for hi in range(start_y, end_y):
            for wj in range(start_x, end_x):
                if hi < 0 or hi >= image_height or wj < 0 or wj >= image_width:
                    continue
                elif map_data[hi][wj][button_labels.index("Yellow")] != 1 and map_data[hi][wj][button_labels.index("Wall")] != 1 and map_data[hi][wj][button_labels.index("Deposit")] != 1:
                    map_data[hi][wj][paint_option] = 1
    reloadImage()

def onClickModeChange(event):
    global show_option, paint_option
    show_option = listShowMode.curselection()[0]
    print("show mode : " + button_labels[show_option + border_area_object])
    if show_option != 0:
        paint_option = show_option + border_area_object
    reloadImage()


def onClickPaintMode(event):
    global paint_option
    paint_option = listPaintBrush.curselection()[0]
    print("paint mode : " + button_labels[paint_option])


def setButtons(root):
    global listShowMode, listPaintBrush
    # global button_labels, button_values, buttons_is_checked
    button_width = 10
    listPaintBrush =tk.Listbox(root, height = len(button_labels))
    for line in button_labels:
        listPaintBrush.insert(tk.END, line)
    listPaintBrush.select_set(0)
    listPaintBrush.bind("<ButtonRelease-1>", onClickPaintMode)
    listPaintBrush.place(x = image_width + margin * 2, y = margin * 1)

    # for i in range(len(button_labels)):
    #     button = tk.Checkbutton(root, text=button_labels[i], variable=buttons_is_checked[i], width = button_width, anchor="w")
    #     button.place(x = image_width + margin * 2, y = margin * (i + 1))

    listShowMode =tk.Listbox(root, height = 4)
    for line in ["床情報", "Red", "Cyan", "Black"]:
        listShowMode.insert(tk.END, line)
    listShowMode.select_set(0)
    listShowMode.bind("<ButtonRelease-1>", onClickModeChange)
    listShowMode.place(x = image_width + margin * 2, y = margin * (len(button_labels) + 2))

    button = tk.Button(root, text="Output")
    button.bind("<Button-1>", onClickOutput)
    button.place(x = image_width + margin * 2, y = margin * (len(button_labels) + 8))

    button = tk.Button(root, text="Load")
    button.bind("<Button-1>", onClickLoadData)
    button.place(x = image_width + margin * 2, y = margin * (len(button_labels) + 10))

def formatImage():
    global map_data, image_rgb
    for hi in range(image_height):
        for wj in range(image_width):
            min_val = 10000
            min_color_num = 0
            for i in range(len(button_labels)):
                if (registered_color[i][0] - image_rgb[hi][wj][0]) ** 2 + (registered_color[i][1] - image_rgb[hi][wj][1]) ** 2 + (registered_color[i][2] - image_rgb[hi][wj][2]) ** 2 <= min_val:
                    min_color_num = i
                    min_val = (registered_color[i][0] - image_rgb[hi][wj][0]) ** 2 + (registered_color[i][1] - image_rgb[hi][wj][1]) ** 2 + (registered_color[i][2] - image_rgb[hi][wj][2]) ** 2
                    # break
            map_data[hi][wj][min_color_num] = 1
            if min_color_num > border_area_object:
                map_data[hi][wj][button_labels.index("White")] = 1




def main():
    global button_labels, button_values, image_rgb, canvas, map_data, image_width, image_height


    # 初期化
    root = tk.Tk()
    # 名前
    root.title("Image2Array")



    # 画像の読み込み
    image_bgr = cv2.imread("Background.bmp")
    image_height, image_width,_ = image_bgr.shape
    print(str(image_height) + " " + str(image_width))

    # マップの情報を収納する変数を0初期化
    map_data = [[[0 for i in range(len(button_labels))] for j in range(image_width)] for k in range(image_height)]

    image_rgb = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGB)
    formatImage()

    image_pil = Image.fromarray(image_rgb)
    tkimg = ImageTk.PhotoImage(image_pil)





    # メイン画面の配置
    canvas = tk.Canvas(root, width=image_width + margin * 2 + button_margin, height=image_height + margin * 2, bg="white")
    canvas.pack()

    # ボタンを配置
    setButtons(root)

    # 画像を表示
    reloadImage()


    # 画像の周りに線を表示
    line_margin = 2
    canvas.create_rectangle(margin - line_margin / 2, margin - line_margin / 2, image_width + margin + line_margin / 2, image_height + margin + line_margin / 2, outline="black", width = line_margin)

    canvas.bind("<Button-1>", onImageClick)
    canvas.bind("<ButtonRelease-1>", onImageRelease)
    canvas.bind("<B1-Motion>", onImageMotion)




    root.mainloop()


if __name__ == "__main__":
    main()
