#include "Image.h";
#include <cmath>;

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
			hist[im.data[i]]++;/* datanýn bir elemanýnýn deðeri zaten 0-255 arasýnda bir deðerdir. ilk döngüde datanýn 0.eemanýnýn deðeri 200
							   çýksýn bu im.data[0] = 200 demektir. his[200]++ ise histoggramýn en baþta 200. elemaný 0 demekti bunu ++ ile
							   1 arttýr demektir.böylece her bir döngüde histogramýn 0-255 arasý deðerleri bir bir arttýrýlýr.*/
		}

		return hist;// hist dizinin baþlangýç adresi return edilir.
	}
	else {
		hist = NULL;
	}
}



image OtsuThresholding(image im, int* hist) {


	image binaryImage;

	binaryImage.data = new unsigned char[im.h * im.w]();
	binaryImage.w = im.w;
	binaryImage.h = im.h;
	binaryImage.c = 1;

	int Tm1, Tm2;

	int T1 = 0, T2 = 255;




	int ortancaDeger = T2 - (T2 - T1) / 2;

	int T1bas = T1;
	int T2bas = T2;

	int T1Ussu = 0;
	int T2Ussu = 0;



	while (true) {
		unsigned long long T1UssuPay = 0, T1UssuPayda = 1;
		unsigned long long T2UssuPay = 0, T2UssuPayda = 1;

		for (int i = 0; i < 256; i++) {

			if (i < ortancaDeger) {

				T1UssuPay += i * hist[i];
				T1UssuPayda += hist[i];
			}
			else {
				T2UssuPay += i * hist[i];
				T2UssuPayda += hist[i];

			}

		}


		T1Ussu = T1UssuPay / (T1UssuPayda);
		T2Ussu = T2UssuPay / (T2UssuPayda);

		if (T1bas == T1Ussu && T2bas == T2Ussu) {

			Tm1 = T1Ussu;
			Tm2 = T2Ussu;
			break;
		}
		else {

			T1bas = T1Ussu;
			T2bas = T2Ussu;
		}
	}



	//int Threshold = Tm2 - (Tm2 - Tm1) / 2;
	int Threshold = static_cast<int>(Tm2 - (Tm2 - Tm1) / 2);

	long newpos = 0;

	for (int row = 0; row < im.h; row++) {
		for (int column = 0; column < im.w; column++) {

			newpos = row * im.w + column;
			int griDeger = im.data[newpos];


			if (griDeger < Threshold) {

				binaryImage.data[newpos] = unsigned char(0);

			}
			else {
				binaryImage.data[newpos] = unsigned char(255);

			}


		}
	}

	return binaryImage;
}