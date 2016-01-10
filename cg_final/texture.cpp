#include "texture.h"

unsigned int bck_texture;
unsigned int wall_texture;

void initTexture()
{
	bck_texture = LoadBitMap("../welcome_background.bmp");
	if (bck_texture == -1){
		printf("load welcome background error");
		exit(0);
	}
	wall_texture = LoadBitMap("../button_background.bmp");
	if (wall_texture == -1){
		printf("load button background error");
		exit(0);
	}
}


int LoadBitMap(const char *file)
{
	unsigned int ID, i;
	int width, height;
	byte *image;
	byte t;
	FILE *fp;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	fp = fopen(file, "rb");
	if (fp == NULL){
		perror("LoadBitMap");
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if (FileHeader.bfType != 0x4D42)  //确保文件是一个位图文件，效验文件类型
	{
		printf("Error: This file is not a bmp file!");
		fclose(fp);
		return -1;
	}
	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = InfoHeader.biWidth;
	height = InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0)  {
		InfoHeader.biSizeImage = width*height * 3;
	}

	fseek(fp, FileHeader.bfOffBits, SEEK_SET);
	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage);
	if (image == NULL)
	{
		free(image);
		printf("Error: No enough space!");
		return -1;
	}
	fread(image, 1, InfoHeader.biSizeImage, fp);
	for (i = 0; i < InfoHeader.biSizeImage; i += 3){
		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	fclose(fp);
	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);

	return ID;
}