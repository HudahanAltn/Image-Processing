#include "Image.h";
#include <cmath>;

image convertGrayScale(image im) {// ilgili resim rgb format�nda ilgili fonksiyona gelir.

	image grayImage;// 
	grayImage.data = new unsigned char[im.h * im.w]; /* gri g�r�nt� boyutu kadar yeni bellek alan� ay�r�p bu alan�n ba�lang�c�n�
	grayImage nesnesinin data pointer�na i�aret ettiriyoruz. rgb(w*h*3)  gri(w*h*1) */

	//y�kseklik ve geni�lik de�erlerini ge�iriyoruz.
	grayImage.w = im.w;
	grayImage.h = im.h;
	grayImage.c = 1;


	long bufpos = 0;
	long newpos = 0;
	/*bu d�ng�lerde rgb g�r�nt� 1 boyutlu dizi �eklinde tan�mland� dolay�s�yla her bir eleman�ndaki de�er al�nacak ve gri seviye de�ere
	d�n��ecektir.burada asl�nda 3 boyutlu mant��yla tan�mlanm�� ama asl�nda 1 boyutlu olan diziyi 2 boyutlu mant���yla tan�mlanan ama asl�nda
	1 boyutlu olan diziye �evirme i�lemi yap�yoruz.*/
	for (int row = 0; row < im.h; row++) {
		for (int column = 0; column < im.w; column++) {

			newpos = row * im.w + column;/*2d dizi mant���yla tan�mlanan ama sl�nda 1 boyutlu olan dizi �zerinde gezecek i�aret�i*/
			bufpos = row * im.w * im.c + column * im.c;/*3d dizide gezecek olan i�aret�i*/

			/*burada i�te 3d ama asl�nda 1 d olan dizinin her bir eleman� 2d ama asl�nda 1 d olan yeni diziye ge�irilir.*/
			grayImage.data[newpos] = unsigned char(0.30 * im.data[bufpos] + 0.59 * im.data[bufpos + 1] + 0.11 * im.data[bufpos + 2]);

		}
	}

	return grayImage;// burada art�k d�nen nesne 2 boyut mant���yla tan�mlanan ama aslen 1 boyutlu olan ve boyutu h*w olan diizidr.
}

int* createHistogram(image im) {

	int* hist;

	if (im.c == 1) {// gelen resim gray level ise
		hist = new int[256];// bellekte yeni 256 l�k alan a��yoruz.bu histogram�m�zda x eksenini yani gri seviye pixel de�erlerini g�sterecek

		for (int i = 0; i < 256; i++) {// dizinin elemanlar�n� 0 a setliyoruz.
			hist[i] = 0;//her bir yere 0 at�yoruz.
		}

		for (int i = 0; i < im.h * im.w; i++) {//gri seviye bir g�r�nt� geni�lik*y�kseklik boyutundad�r.
			hist[im.data[i]]++;/* datan�n bir eleman�n�n de�eri zaten 0-255 aras�nda bir de�erdir. ilk d�ng�de datan�n 0.eeman�n�n de�eri 200
							   ��ks�n bu im.data[0] = 200 demektir. his[200]++ ise histoggram�n en ba�ta 200. eleman� 0 demekti bunu ++ ile
							   1 artt�r demektir.b�ylece her bir d�ng�de histogram�n 0-255 aras� de�erleri bir bir artt�r�l�r.*/
		}

		return hist;// hist dizinin ba�lang�� adresi return edilir.
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