#include "png.h"
#include <stdio.h>
#include <string.h>

#ifdef _DEBUG
	#pragma comment(lib, "libpng_debug.lib")
	#pragma comment(lib, "zlib_debug.lib")
#else
	#pragma comment(lib, "libpng_release.lib")
	#pragma comment(lib, "zlib_release.lib")
#endif


void MakeOutputFileName(const char *pInputFileName, char *pOutputFileName);
void EncodePngFile(const char *pInputFileName, const char *pOutputFileName);

void main(int argc, char *argv[]){
	char buf[256];
	
	for(int i = 1; i < argc; ++i){
		MakeOutputFileName(argv[i], buf);
		EncodePngFile(argv[i], buf);
	}
	/*
	
	MakeOutputFileName("title_bg.png", buf);
	EncodePngFile("title_bg.png", buf);
	*/
}

void EncodePngFile(const char *pInputFileName, const char *pOutputFileName){
	png_structp sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop ip = png_create_info_struct(sp);
	FILE *fp = fopen(pInputFileName, "rb");
	
	if(fp == NULL){
		return;
	}
	
	png_init_io(sp, fp);
	png_read_info(sp, ip);
	
	int nDepth;
	int nInterlaceType;
	int nWidth, nHeight;
	int nColorType;
	
	png_get_IHDR(
		sp, 
		ip, 
		(png_uint_32*)&nWidth, 
		(png_uint_32*)&nHeight, 
		&nDepth, &nColorType,
		&nInterlaceType,
		NULL, 
		NULL
	);
	
	int rb = png_get_rowbytes(sp, ip);
	unsigned char *m_pTex = new unsigned char[nHeight * rb];	// ビットマップデータのメモリ確保
	unsigned char **pWork = new unsigned char*[nHeight];		// 作業用ワーク確保
	
	for(int i = 0; i < nHeight; ++i){
		pWork[i] = &m_pTex[i * rb];
	}
	
	png_read_image(sp, pWork);
	png_read_end(sp, ip);
	
	png_destroy_read_struct(&sp, &ip, NULL);
	fclose(fp);
	
	delete[] pWork;

	fp = fopen(pOutputFileName, "wb");

	fwrite(&nWidth, sizeof(int), 1, fp);
	fwrite(&nHeight, sizeof(int), 1, fp);
	int color;

	if(nColorType != PNG_COLOR_TYPE_RGBA){
		color = 3;
		fwrite(&color, sizeof(int), 1, fp);

		unsigned char *Tex24bit = new unsigned char[nWidth * nHeight * 3];

		for(int i = 0; i < nWidth * nHeight * 3; ++i){
			Tex24bit[i] = m_pTex[i];
		}

		fwrite(Tex24bit, sizeof(unsigned char), nWidth * nHeight * 3, fp);

		delete[] Tex24bit;

	} else {
		color = 4;
		fwrite(&color, sizeof(int), 1, fp);
		fwrite(m_pTex, sizeof(unsigned char), nWidth * nHeight * 4, fp);
	}


	delete[] m_pTex;

	fclose(fp);
}

void MakeOutputFileName(const char *pInputFileName, char *pOutputFileName){

	strcpy(pOutputFileName, pInputFileName);
	
	int i;
	for(i = strlen(pOutputFileName); pOutputFileName[i] != '.'; --i);

	strcpy(&pOutputFileName[i], ".img");
}