#include "Morphology.h"

/*D�KKAT!! burada arkaplan beyaz (255) nesneler ise siyah(0) ile temsil edildi�i�i i�in morfolojik i�lemlerde ters mant�k s�z konusudur.
Clustering alogritmalar�nda arkplan� 0 nesneyi 1 yap�nca buradaki erosion dilation ,dilation ise erosion olur :D .�uan ise 
arkaplan 0 nesneler ise 1 ile temsil edilemktedir.*/

image Erosion(image im) {

    //sonucu tutacak olan image nesnesi
    image erosionedImage;
    erosionedImage.data = new unsigned char[im.w * im.h];
    erosionedImage.w = im.w;
    erosionedImage.h = im.h;
    erosionedImage.c = im.c;

    int kernel[3][3] = {//erosion i�in kernel matris 
        {255, 255, 255},
        {255, 255, 255},
        {255, 255, 255}
    };

    int kernel_size = 3;//booyutunu tek bir noktadan de�i�tirmek i�in b�yle yazd�k.

    for (int i = 0; i < im.h; i++) {//d�� for d�ng�s� binary resmin her bir pixelini bize getirir.
        for (int j = 0; j < im.w; j++) {


            int max_val = 0;

            for (int k = 0; k < kernel_size; k++) {//kernel mask i�in for d�ng�s�
                for (int l = 0; l < kernel_size; l++) {

                    /*buradak x ve y orj matris �zerinde kernel gezdirirken dikkate al�nacak konumlar� hesaplamak i�in kullan�lackak.kernelin
                    d��ar� ta��p ta�mad�p�n�n saptanmas� i�in kullan�lacak.*/
                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;

                    //xve y 00 dan b�y�kse kernel ile org matrisin ilgili elemanlar� �r�t��yor demek.
                    if (x >= 0 && x < im.h && y >= 0 && y < im.w && kernel[k][l] == 255) {

                        
                        if (im.data[x * im.w + y] > max_val) {
                            max_val = im.data[x * im.w + y];
                        }
                    }
                }
            }
            erosionedImage.data[i * erosionedImage.w + j] = max_val;
        }
    }

    return erosionedImage;
}

image Dilation(image im) {

    image dilationedImage;
    dilationedImage.data = new unsigned char[im.w * im.h];
    dilationedImage.w = im.w;
    dilationedImage.h = im.h;
    dilationedImage.c = im.c;

    int kernel[3][3] = {
        {255, 255, 255},
        {255, 255, 255},
        {255, 255, 255}
    };

    int kernel_size = 3;


    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int min_val = 255;

            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {

                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;


                    if (x >= 0 && x < im.h && y >= 0 && y < im.w) {
                        if (kernel[k][l] == 255 && im.data[x * im.w + y] < min_val) {
                            min_val = im.data[x * im.w + y];
                        }
                    }
                }
            }
            dilationedImage.data[i * dilationedImage.w + j] = min_val;
        }
    }


    return dilationedImage;

}
