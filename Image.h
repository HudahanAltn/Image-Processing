#pragma once
#include <string.h>

// image.h
typedef struct Image {// g�r�nt� temsili i�in basit struct yap�s�

	int w;//geni�lik
	int h;//y�kseklik
	int c;//rgb color uzay� de�eri
	unsigned char* data;//bu bizim g�r�nt�m�z�n bellekteki yerini g�steren pointer.

	Image loadImage(const char* filename);
	/*Image makeImage(int w, int h, int c);
	Image makeEmptyImage(int w, int h, int c);*/
	void  Free(Image im);
}Image;
