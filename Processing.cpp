#include "Image.h";

image convertGrayScale(image im) {// ilgili resim rgb formatýnda ilgili fonksiyona gelir.

	image grayImage;// 
	grayImage.data = new unsigned char[im.h * im.w]; /* gri görüntü boyutu kadar yeni bellek alaný ayýrýp bu alanýn baþlangýcýný 
	grayImage nesnesinin data pointerýna iþaret ettiriyoruz. rgb(w*h*3)  gri(w*h*1) */

	//yükseklik ve geniþlik deðerlerini geçiriyoruz.
	grayImage.w = im.w;
	grayImage.h = im.h;
	grayImage.c = 1;

	
	long bufpos = 0;
	long newpos = 0;
	/*bu döngülerde rgb görüntü 1 boyutlu dizi þeklinde tanýmlandý dolayýsýyla her bir elemanýndaki deðer alýnacak ve gri seviye deðere
	dönüþecektir.burada aslýnda 3 boyutlu mantýýyla tanýmlanmýþ ama aslýnda 1 boyutlu olan diziyi 2 boyutlu mantýðýyla tanýmlanan ama aslýnda
	1 boyutlu olan diziye çevirme iþlemi yapýyoruz.*/
	for (int row = 0; row < im.h; row++) {
		for (int column = 0; column < im.w; column++) {

			newpos = row * im.w + column;/*2d dizi mantýðýyla tanýmlanan ama slýnda 1 boyutlu olan dizi üzerinde gezecek iþaretçi*/
			bufpos = row * im.w * im.c + column * im.c;/*3d dizide gezecek olan iþaretçi*/

			/*burada iþte 3d ama aslýnda 1 d olan dizinin her bir elemaný 2d ama aslýnda 1 d olan yeni diziye geçirilir.*/
			grayImage.data[newpos] = unsigned char(0.30 * im.data[bufpos] + 0.59 * im.data[bufpos + 1] + 0.11 * im.data[bufpos + 2]);

		}
	}

	return grayImage;// burada artýk dönen nesne 2 boyut mantýðýyla tanýmlanan ama aslen 1 boyutlu olan ve boyutu h*w olan diizidr.
}

int* createHistogram(image im) {

	int* hist;

	if (im.c == 1) {// gelen resim gray level ise
		hist = new int[256];// bellekte yeni 256 lýk alan açýyoruz.bu histogramýmýzda x eksenini yani gri seviye pixel deðerlerini gösterecek

		for (int i = 0; i < 256; i++) {// dizinin elemanlarýný 0 a setliyoruz.
			hist[i] = 0;//her bir yere 0 atýyoruz.
		}

		for (int i = 0; i < im.h * im.w; i++) {//gri seviye bir görüntü geniþlik*yükseklik boyutundadýr.
			hist[im.data[i]]++;/* burada 255 adet veri var.hist dizinin index numaralarýna karþýlýk gelen bellek hücresinde  gri görüntünün
			0 index deðerindeki pixel adedi mevcuttur.*/
		}

		return hist;// hist dizinin baþlangýç adresi return edilir.
	}
	else {
		hist = NULL;
	}
}