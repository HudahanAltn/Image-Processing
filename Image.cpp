#include "Image.h"
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h";


Image loadImage(const char* filename)
{
	int w, h, c;// weight,height,color
	int channel = 3;

	//w = width, h = height, c = # 8 - bit components per pixel .

	unsigned char* data = stbi_load(filename, &w, &h, &c, channel);/*stbi_load fonksiyonu std_image.h tarafýndan saðlanan fonksiyon.
																   bu fonk resmin bellekte kapladýðý datayý döndürür.*/

	if (!data) {// path bozuk veya path'da okunabilir dosya yoksa hata döndürülür.
		exit(EXIT_FAILURE);
	}

	Image imageOut;
	imageOut.w = w;
	imageOut.h = h;
	imageOut.c = c;
	imageOut.data = data;

	return imageOut;

}//load_image

void Image::Free(Image im) {
	delete[] im.data;
}
