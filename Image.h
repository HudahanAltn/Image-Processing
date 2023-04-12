#pragma once
#include <string.h>

// image.h
typedef struct image {// görüntü temsili için basit struct yapýsý

	int w;//geniþlik
	int h;//yükseklik
	int c;//rgb color uzayý deðeri
	unsigned char* data;//bu bizim görüntümüzün bellekteki yerini gösteren pointer.
} image;

image loadImage(const char* filename);
//Image makeImage(int w, int h, int c);
//Image makeEmptyImage(int w, int h, int c);
void Free(image im);

