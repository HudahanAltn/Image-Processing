#include "Image.h"
#include <cstdlib>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h";


image loadImage(const char* filename)
{
	int w, h, c;// weight,height,color
	int channel = 3;

	//w = width, h = height, c = # 8 - bit components per pixel .

	unsigned char* data = stbi_load(filename, &w, &h, &c, channel);/*stbi_load fonksiyonu std_image.h taraf�ndan sa�lanan fonksiyon.
	bu fonksiyon bellekten rgb resmi al�r.rgb resim 3 boyutlu bir dizi �eklinde ifade edilir.Lakin bu fonksiyon bu diziyi 3 boyut
	yerine tek boyut �eklinde belle�e yerle�tirir.Sonu� olarak dizinin ba�lang�� adresini bize pointer olarak d�nd�r�r.Ayr�ca ilgili 
	resim i�in w,h ve c de�i�kenlerine ilgili verileri ge�irir.��nk� stbi_load bunlar� referans cinsinden alm��t�r.*/

	if (!data) {//resmin okunmamas� durumunda data NULL olu.
		exit(EXIT_FAILURE);
	}

	image imageOut;// bellekteki resmi temsil etmesi i�in bir struct olu�turduk.
	// ilgili resmin geni�lik , y�kseklik ve renk de�eri(rgb oldu�u i�in bu de�er 3 t�r) atamas� yapt�k.
	imageOut.w = w;
	imageOut.h = h;
	imageOut.c = c;

	imageOut.data = data;/*buarada art�k imageout nesnesinin data pointer� bellekteki resmin ba�lang�c�n� i�aret eder.*/
	return imageOut;

}//load_image

void Free(image im) {//al�nan bellek alan�n� serbest b�rak�r.
	delete[] im.data;
}
