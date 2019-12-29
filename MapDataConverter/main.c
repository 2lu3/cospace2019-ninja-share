#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#define true 1
#define false 0
#define HEADER_SIZE 54 //heder SIZE 54 = 14 + 40
#define MAX_WIDTH 3000 //upper limit of width(pixel)
#define MAX_HEIGHT 3000 //upper limit of height(pixel)
#define PLUS_MINUS(a, b, c) ((a) + (c) >= b && (a) - (c) <= b)
#define DATA_SIZE 37




//r,g,b values of one pixel
typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  int color_type;//どの色か
} color;
typedef struct {
  long height;
  long width;
  color data[MAX_HEIGHT][MAX_WIDTH];
} img;

img *bmp_color_data_receiver;

FILE *color_RGB_data_file;
char color_RGB_data_file_name[50] = "map_color_information.txt";
FILE *out_put_data_file;
char out_put_data_file_name[50] = "image_data_in_int_format.txt";


int ReadBmp(char *file_name, img *imgp);


int main() {
  bmp_color_data_receiver = (img *)malloc(sizeof(img));

  //Get file name
  char bmp_file_name[100];
  printf("Drag and drop a bmp picture which you want to convert\n");
  printf("And push enter key if I don't say start opening\n");
  scanf("%s", bmp_file_name);

  printf("Start to read %s\n", bmp_file_name);
  if(!ReadBmp(bmp_file_name, bmp_color_data_receiver)) {
    //unsuccess
    return -1;
  }
  printf("Success to read %s\n", bmp_file_name);

  printf("Start to read %s\n", color_RGB_data_file_name);
  color_RGB_data_file = fopen(color_RGB_data_file_name, "r");
  if(color_RGB_data_file == NULL) {
    printf("Failed to oepn %s\n", color_RGB_data_file_name);
    return 0;
  }

  //Read Base Color
  int base_color[20][3];
  int base_color_num = 0;
  while(!feof(color_RGB_data_file)) {
    if(base_color_num >= 19) {
      printf("Error: the number of base color adove 20\n");
      return 0;
    }
    fscanf(color_RGB_data_file, "%d ", &base_color_num);
    fscanf(color_RGB_data_file, "%d %d %d", &base_color[base_color_num][0], &base_color[base_color_num][1], &base_color[base_color_num][2]);
    if(base_color[base_color_num][0] == 1000) {
      break;
    }
    fscanf(color_RGB_data_file, "\n");
  }
  fclose(color_RGB_data_file);
  printf("finish to read %s\n", color_RGB_data_file_name);

  printf("Start to check RGB value with one pixel using base colors\n");
  //Check RGB value with one pixel using base colors
  int ave = 0;
  for(int i = 0; i < bmp_color_data_receiver->height; i++) {
    for(int j = 0; j < bmp_color_data_receiver->width; j++) {
      //If there is no match in base colors
      bmp_color_data_receiver->data[i][j].color_type = base_color_num;
      for(int k = 0; k < base_color_num; k++) {
        if(PLUS_MINUS(base_color[k][0], bmp_color_data_receiver->data[i][j].r, ave)) {
          if(PLUS_MINUS(base_color[k][1], bmp_color_data_receiver->data[i][j].g, ave)) {
            if(PLUS_MINUS(base_color[k][2], bmp_color_data_receiver->data[i][j].b, ave)) {
              //match base color "k"
              bmp_color_data_receiver->data[i][j].color_type = k;
              break;
            }
          }
        }
      }
    }
  }
  printf("Finish to check RGB value with one pixel using base colors\n");


  int out_put_data[MAX_HEIGHT / DATA_SIZE][MAX_WIDTH / DATA_SIZE];

  printf("Change (720) x (540) pixel to (720 / SIZE) x (540 / SIZE) pixel\n");
  //change 720 x 540 to 720 / SIZE x 540 / SIZE
  {
    int num[base_color_num + 1];
    int max = 0;
    int max_num;
    for(int i = 0; i < bmp_color_data_receiver->height / DATA_SIZE; i++) {
      for(int j = 0; j < bmp_color_data_receiver->width / DATA_SIZE; j++) {
        //init
        for(int k = 0; k < base_color_num + 1; k++) {
          num[k] = 0;
        }

        //count number of base color
        for(int k = i * DATA_SIZE; k < i * DATA_SIZE + DATA_SIZE; k++) {
          for(int l = j * DATA_SIZE; l < j * DATA_SIZE + DATA_SIZE; l++) {
            num[bmp_color_data_receiver->data[k][l].color_type]++;
          }
        }

        //check which color is most a lot
        max = num[1];
        max_num = 1;
        for(int k = 1; k < base_color_num; k++) {
          if(max < num[k]) {
            max = num[k];
            max_num = k;
          }
        }
        if(max == 0) {
          max_num = 0;
          max = num[0];
        }
        out_put_data[i][j] = max_num;
      }
    }
  }
  printf("Changeed (720) x (540) pixel to (720 / SIZE) x (540 / SIZE) pixel\n");

	//data format
	/*
	00111 -> 00111
	01001 -> 01111
	01001 -> 01111
	00111 -> 00111
	{
		int zero_connected_land[bmp_color_data_receiver->height / DATA_SIZE][bmp_color_data_receiver->width / DATA_SIZE];
		//init
		for(int i = 0; i < bmp_color_data_receiver->height / DATA_SIZE; i++) {
			for(int j = 0; j < bmp_color_data_receiver->width / DATA_SIZE; j++) {
				zero_connected_land[i][j] = 0;
			}
		}


		for(int i = 0; i < bmp_color_data_receiver->height / DATA_SIZE; i++) {
			for(int j = 0; j < bmp_color_data_receiver->width / DATA_SIZE; j++) {

			}
		}

	}*/

	//Change data format
	/*
		0: nothing
		1: Yellow
		2. wall
		3: deposit
		4. blue
		5. swampland
		6. Cyan
		7. random1
		8. random2
		9. random 3
		10. random 4
		11. red
	*/
	for(int i = 0; i < bmp_color_data_receiver->width / DATA_SIZE; i++) {
		for(int j = 0; j < bmp_color_data_receiver->height / DATA_SIZE; j++) {
			switch (out_put_data[j][i]) {
				case 0:
					out_put_data[j][i] = 1;
					break;
				case 1:
					out_put_data[j][i] = -3;
					break;
				case 2:
					out_put_data[j][i] = -2;
					break;
				case 3:
					out_put_data[j][i] = 0;
					break;
				case 4:
					out_put_data[j][i] = -3;
					break;
				case 5:
					out_put_data[j][i] = -1;
					break;
				case 6:
					out_put_data[j][i] = 15;
					break;
				case 7:
					out_put_data[j][i] = 45;
					break;
				case 8:
					out_put_data[j][i] = 45;
					break;
				case 9:
					out_put_data[j][i] = 45;
					break;
				case 10:
					out_put_data[j][i] = 45;
					break;
				case 11:
					out_put_data[j][i] = 10;
					break;
				case 12:
					out_put_data[j][i] = 15;
					break;
				default:
					break;
			}
		}
	}


  printf("Writing map position information\n");
  out_put_data_file = fopen(out_put_data_file_name, "w");
  fprintf(out_put_data_file, "int map_position_data[%ld][%ld] = {", bmp_color_data_receiver->width / DATA_SIZE, bmp_color_data_receiver->height / DATA_SIZE);
  for(int i = 0; i < bmp_color_data_receiver->width / DATA_SIZE; i++) {
    fprintf(out_put_data_file, (i)?(",{"):("\n{"));
    fprintf(out_put_data_file, "%2d", out_put_data[0][i]);
    for(int j = 1; j < bmp_color_data_receiver->height / DATA_SIZE; j++) {
      fprintf(out_put_data_file, " ,%2d", out_put_data[j][i]);
    }
    fprintf(out_put_data_file, "}");
    fprintf(out_put_data_file, "\n");
  }
  fprintf(out_put_data_file, "}");
  fprintf(out_put_data_file, ";\n");
  fclose(out_put_data_file);
  printf("Finished all processes\n");
  system(out_put_data_file_name);
  return 0;
}


int ReadBmp(char *file_name, img *imgp) {
  FILE *bmp_file;
  unsigned char bmp_header_buf[HEADER_SIZE];

  long real_width;
  unsigned char *bmp_data;

  bmp_file = fopen(file_name, "rb");

  if(bmp_file == NULL) {
    printf("Failed to open bmp file\n");
    printf("If there is \" or new line, it may contain problem\n");
    return 0;
  }

  //Get bmp and information header
  fread(bmp_header_buf, sizeof(unsigned char), HEADER_SIZE, bmp_file);

  //Is the first 2 character "BM"?
  {
    char bmp_type[2];
    memcpy(&bmp_type, bmp_header_buf, sizeof(bmp_type));
    if(strncmp(bmp_type, "BM", 2) != 0) {
      printf("Error: %s is not a bmp file.\n", file_name);
      return 0;
    }
  }

  //Is color pallet 24?
  {
    unsigned short bmp_color;
    memcpy(&bmp_color, bmp_header_buf + 28, 2);
    if(bmp_color != 24) {
      printf("Error: bmp_color = %d is not implemented in this program.\n", bmp_color);
      return 0;
    }
  }

  memcpy(&imgp->width, bmp_header_buf + 18, 4);
  memcpy(&imgp->height, bmp_header_buf + 22, 4);
  if(imgp->width > MAX_WIDTH) {
    printf("Error: bmp_width = %ld > %d = MAX_WIDTH\n", imgp->width, MAX_WIDTH);
    return 0;
  }
  if(imgp->height > MAX_HEIGHT) {
    printf("Error: bmp_height = %ld > %d = MAX_HEIGHT\n", imgp->height, MAX_HEIGHT);
    return 0;
  }
  if(imgp->height < 0) {
    printf("Error hight is under 0\n");
    return 0;
  }


  //calculate real width to fit 4 byte border
  real_width = imgp->width * 3 + imgp->width % 4;

  if((bmp_data = (unsigned char *)calloc(real_width, sizeof(unsigned char))) == NULL) {
    printf("Eroor: memory allocation failed for bmp_data\n");
    return 0;
  }

  printf("Reading data...\n");
  for(int i = 0; i < imgp->height; i++) {
    fread(bmp_data, 1, real_width, bmp_file);
    for(int j = 0; j < imgp->width; j++) {
      imgp->data[/*imgp->height-*/i/*-1*/][j].b = bmp_data[j*3];
      imgp->data[/*imgp->height-*/i/*-1*/][j].g = bmp_data[j*3+1];
      imgp->data[/*imgp->height-*/i/*-1*/][j].r = bmp_data[j*3+2];
    }
  }

  free(bmp_data);
  fclose(bmp_file);
  return 1;
}
