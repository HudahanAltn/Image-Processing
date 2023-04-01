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

	unsigned char* data = stbi_load(filename, &w, &h, &c, channel);/*stbi_load fonksiyonu std_image.h tarafýndan saðlanan fonksiyon.
	bu fonksiyon bellekten rgb resmi alýr.rgb resim 3 boyutlu bir dizi þeklinde ifade edilir.Lakin bu fonksiyon bu diziyi 3 boyut
	yerine tek boyut þeklinde belleðe yerleþtirir.Sonuç olarak dizinin baþlangýç adresini bize pointer olarak döndürür.Ayrýca ilgili 
	resim için w,h ve c deðiþkenlerine ilgili verileri geçirir.çünkü stbi_load bunlarý referans cinsinden almýþtýr.*/

	if (!data) {//resmin okunmamasý durumunda data NULL olu.
		exit(EXIT_FAILURE);
	}

	image imageOut;// bellekteki resmi temsil etmesi için bir struct oluþturduk.
	// ilgili resmin geniþlik , yükseklik ve renk deðeri(rgb olduðu için bu deðer 3 tür) atamasý yaptýk.
	imageOut.w = w;
	imageOut.h = h;
	imageOut.c = c;

	imageOut.data = data;/*buarada artýk imageout nesnesinin data pointerý bellekteki resmin baþlangýcýný iþaret eder.*/
	return imageOut;

}//load_image

void Free(image im) {//alýnan bellek alanýný serbest býrakýr.
	delete[] im.data;
}
