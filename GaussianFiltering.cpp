#include "image.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

image sobelFilter(image im) {//parametre olarak gray image gelir.


    image GradientXImage;
    GradientXImage.h = im.h;
    GradientXImage.w = im.w;
    GradientXImage.c = 1;
    GradientXImage.data = new unsigned char[im.w * im.h];


    image GradientYImage;
    GradientYImage.h = im.h;
    GradientYImage.w = im.w;
    GradientYImage.c = 1;
    GradientYImage.data = new unsigned char[im.w * im.h];


    image EdgeImage;
    EdgeImage.h = im.h;
    EdgeImage.w = im.w;
    EdgeImage.c = 1;
    EdgeImage.data = new unsigned char[im.w * im.h];

    //sobel kernel masks
    int kernelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int kernelY[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    int kernel_size = 3;

    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int sumX = 0;
            int sumY = 0;

            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {

                    //ge�erli koordinat hesab�
                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;

                    if (x >= 0 && x < im.h && y >= 0 && y < im.w) {//koordinatlar istenilen aral�ktaysa
                        //convole i�lemi
                        sumX += im.data[x * im.w + y] * kernelX[k][l];
                        sumY += im.data[x * im.w + y] * kernelY[k][l];
                    }
                }
            }
            //atama
            GradientXImage.data[i * im.w + j] = abs(sumX);
            GradientYImage.data[i * im.w + j] = abs(sumY);
        }
    }

    //x ve y y�n�ndeki t�revli resimleri birle�tirip edge image elde etme
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            int  gxValue = GradientXImage.data[i * im.w + j];
            int gYValue = GradientYImage.data[i * im.w + j];
            int result = gxValue * gxValue + gYValue * gYValue;
            EdgeImage.data[i * im.w + j] = sqrt(result);
        }
    }


    //edge image pixel de�er aral��� 0-1020 aral���ndand�r bunu 0-255 aral���na �ekmek i�in normalize i�lemi.
    int max = 0;
    for (int i = 0; i < EdgeImage.h; i++) { //resimdeki max de�er bulunur
        for (int j = 0; j < EdgeImage.w; j++) {
            int val = EdgeImage.data[i * EdgeImage.w + j];
            if (val > max) {
                max = val;
            }
        }
    }


    for (int i = 0; i < EdgeImage.h; i++) {
        for (int j = 0; j < EdgeImage.w; j++) {
            float ratio = (float)EdgeImage.data[i * EdgeImage.w + j] / max;
            EdgeImage.data[i * EdgeImage.w + j] = ratio * 255;
        }
    }


    return EdgeImage;
}

image angleImageFilter(image im) {

    image GradientXImage;
    GradientXImage.h = im.h;
    GradientXImage.w = im.w;
    GradientXImage.c = 1;
    GradientXImage.data = new unsigned char[im.w * im.h];

    image GradientYImage;
    GradientYImage.h = im.h;
    GradientYImage.w = im.w;
    GradientYImage.c = 1;
    GradientYImage.data = new unsigned char[im.w * im.h];

    image angleImage;
    angleImage.h = im.h;
    angleImage.w = im.w;
    angleImage.c = 1;
    angleImage.data = new unsigned char[im.w * im.h];


    int kernelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int kernelY[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    int kernel_size = 3;

    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int sumX = 0;
            int sumY = 0;

            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {

                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;

                    if (x >= 0 && x < im.h && y >= 0 && y < im.w) {
                        sumX += im.data[x * im.w + y] * kernelX[k][l];
                        sumY += im.data[x * im.w + y] * kernelY[k][l];
                    }
                }
            }

            GradientXImage.data[i * im.w + j] = abs(sumX);
            GradientYImage.data[i * im.w + j] = abs(sumY);
        }
    }


    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            int gxValue = GradientXImage.data[i * im.w + j];
            int gYValue = GradientYImage.data[i * im.w + j];
            angleImage.data[i * im.w + j] = atan2(gYValue, gxValue);
        }
    }

    int max = 0;

    for (int i = 0; i < angleImage.h; i++) {
        for (int j = 0; j < angleImage.w; j++) {
            int val = angleImage.data[i * angleImage.w + j];
            if (val > max) {
                max = val;
            }
        }
    }

    for (int i = 0; i < angleImage.h; i++) {
        for (int j = 0; j < angleImage.w; j++) {
            float ratio = (float)angleImage.data[i * angleImage.w + j] / max;
            angleImage.data[i * angleImage.w + j] = ratio * 255;
        }
    }

    return angleImage;
}

image prewittFilter(image im) {

    image GradientXImage;
    GradientXImage.h = im.h;
    GradientXImage.w = im.w;
    GradientXImage.c = 1;
    GradientXImage.data = new unsigned char[im.w * im.h];

    image GradientYImage;
    GradientYImage.h = im.h;
    GradientYImage.w = im.w;
    GradientYImage.c = 1;
    GradientYImage.data = new unsigned char[im.w * im.h];

    image EdgeImage;
    EdgeImage.h = im.h;
    EdgeImage.w = im.w;
    EdgeImage.c = 1;
    EdgeImage.data = new unsigned char[im.w * im.h];

    //x-axis ve y-axis kernelleri
    int kernelX[3][3] = {
        {-1, 0, 1},
        {-1, 0, 1},
        {-1, 0, 1}
    };

    int kernelY[3][3] = {
        {1, 1, 1},
        {0, 0, 0},
        {-1, -1, -1}
    };

    int kernel_size = 3;

    //convolution
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int sumX = 0;
            int sumY = 0;

            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {

                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;

                    if (x >= 0 && x < im.h && y >= 0 && y < im.w) {
                        sumX += im.data[x * im.w + y] * kernelX[k][l];
                        sumY += im.data[x * im.w + y] * kernelY[k][l];
                    }
                }
            }

            GradientXImage.data[i * im.w + j] = abs(sumX);
            GradientYImage.data[i * im.w + j] = abs(sumY);
        }
    }

    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            int gxValue = GradientXImage.data[i * im.w + j];
            int gYValue = GradientYImage.data[i * im.w + j];
            int result = gxValue * gxValue + gYValue * gYValue;
            EdgeImage.data[i * im.w + j] = sqrt(result);
            double atanResult = atan2(gYValue, gxValue) * 180.0 / 3.14159265;
        }
    }


    //min-max normalization
    int max = 0;

    for (int i = 0; i < EdgeImage.h; i++) {
        for (int j = 0; j < EdgeImage.w; j++) {
            int val = EdgeImage.data[i * EdgeImage.w + j];
            if (val > max) {
                max = val;
            }
        }
    }

    for (int i = 0; i < EdgeImage.h; i++) {
        for (int j = 0; j < EdgeImage.w; j++) {
            float ratio = (float)EdgeImage.data[i * EdgeImage.w + j] / max;
            EdgeImage.data[i * EdgeImage.w + j] = ratio * 255;
        }
    }

    return EdgeImage;

}


void createGaussianKernel5x5(double GKernel[][5]) {//5x5 lik gaussian blur kernel mask �reten fonksiyon

    //standart sapma
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    //normalizasyon
    double sum = 0.0;

    // 5x5 kernel �reten for d�ng�s�
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {

            r = sqrt(x * x + y * y);
            GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (3.14 * s);
            sum += GKernel[x + 2][y + 2];
        }
    }

    // normalizasyon
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            GKernel[i][j] /= sum;
}



void createGaussianKernel7x7(double GKernel[][7]) {

    // standart sapma
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    //normalizasyon
    double sum = 0.0;

    // 7x7 kernel �reten for d�ng�s�
    for (int x = -3; x <= 3; x++) {
        for (int y = -3; y <= 3; y++) {
            r = sqrt(x * x + y * y);
            GKernel[x + 3][y + 3] = (exp(-(r * r) / s)) / (3.14 * s);
            sum += GKernel[x + 3][y + 3];
        }
    }

    // normalizasyon
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            GKernel[i][j] /= sum;
}

void createGaussianKernel9x9(double GKernel[][9]) {

    // standart sapma
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    //normalizasyon
    double sum = 0.0;

    // 7x7 kernel �reten for d�ng�s�
    for (int x = -4; x <= 4; x++) {
        for (int y = -4; y <= 4; y++) {
            r = sqrt(x * x + y * y);
            GKernel[x + 4][y + 4] = (exp(-(r * r) / s)) / (3.14 * s);
            sum += GKernel[x + 4][y + 4];
        }
    }

    // normalizasyon
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            GKernel[i][j] /= sum;
}

image gaussianBlur(image im) { //gri resmi bulan�kla�t�rmaya yarayan gaussianBlur fonksiyonu

    //double GKernel[5][5];//gaussian blur kernel yarat
    double GKernel[7][7];
    //double GKernel[9][9];
    //createGaussianKernel5x5(GKernel);//5x5 kernel de�erlerini hesapla
    createGaussianKernel7x7(GKernel);//7x7 kernel de�erlerini hesapla
    //createGaussianKernel99(GKernel);

    int kernel_size = 7;


    image blurredImage;//bulan�kla�t�r�alacak resmi tutan nesne
    blurredImage.h = im.h;
    blurredImage.w = im.w;
    blurredImage.c = 1;
    blurredImage.data = new unsigned char[im.w * im.h];


    //fonksiyona gelen gri resim �nce gaussian blur kernel ile  convole edilir.
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int sumX = 0;

            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {

                    int x = i - kernel_size / 2 + k;
                    int y = j - kernel_size / 2 + l;

                    if (x >= 0 && x < im.h && y >= 0 && y < im.w) {
                        sumX += im.data[x * im.w + y] * GKernel[k][l];

                    }
                }
            }

            blurredImage.data[i * im.w + j] = abs(sumX);

        }

    }

    //burada resim blurlanm��t�r.
    //min-max normalization ile pixel de�erleri uygun aral��a �ekilir.
    int max = 0;

    for (int i = 0; i < blurredImage.h; i++) {
        for (int j = 0; j < blurredImage.w; j++) {
            int val = blurredImage.data[i * blurredImage.w + j];
            if (val > max) {
                max = val;
            }
        }
    }

    for (int i = 0; i < blurredImage.h; i++) {
        for (int j = 0; j < blurredImage.w; j++) {
            float ratio = (float)blurredImage.data[i * blurredImage.w + j] / max;
            blurredImage.data[i * blurredImage.w + j] = ratio * 255;
        }
    }

    return blurredImage;
}


image nonMaximumSuppression(image edgeImage, image angleImage) {//sobel'den gelen edgeImage ve harici hesaplanan angleImage parametreleri.

    
    image suppressedImage;//nonmaxSupp sonucunu tutacak olan image
    suppressedImage.h = edgeImage.h;
    suppressedImage.w = edgeImage.w;
    suppressedImage.c = 1;
    suppressedImage.data = new unsigned char[edgeImage.w * edgeImage.h];


    for (int i = 0; i < edgeImage.h; i++) {
        for (int j = 0; j < edgeImage.w; j++) {

            suppressedImage.data[i * edgeImage.w + j] = edgeImage.data[i * edgeImage.w + j]; // Kenar olmayan piksellerin de�erini koru ve atama yap

            // Kenar olmayan pikselleri atla
            if (edgeImage.data[i * edgeImage.w + j] == 0) { //siyah pixeller atlan�r.
                continue;
            }

            //gradyan ve theta de�erleri al�n�r.
            double angle = edgeImage.data[i * edgeImage.w + j];
            double gradient = angleImage.data[i * angleImage.w + j];

            // Pikselin yatay ve dikey kom�ular�n�n indislerini hesapla
            int x1, y1, x2, y2;

            if (angle < 0) { //a�� pozitife �ekilir.
                angle += 180.0;
            }

            // Yatay y�nde
            if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180)) {
                x1 = i;
                y1 = j - 1;
                x2 = i;
                y2 = j + 1;
            }
            // 45 derece y�nde
            else if (angle >= 22.5 && angle < 67.5) {
                x1 = i - 1;
                y1 = j - 1;
                x2 = i + 1;
                y2 = j + 1;
            }
            // Dikey y�nde
            else if (angle >= 67.5 && angle < 112.5) {
                x1 = i - 1;
                y1 = j;
                x2 = i + 1;
                y2 = j;
            }
            // -45 derece y�nde
            else if (angle >= 112.5 && angle < 157.5) {
                x1 = i - 1;
                y1 = j + 1;
                x2 = i + 1;
                y2 = j - 1;
            }

            // Kom�u piksellerin de�erlerini kontrol et
            int pixelValue = edgeImage.data[i * edgeImage.w + j];
            int neighbor1Value = edgeImage.data[x1 * edgeImage.w + y1];
            int neighbor2Value = edgeImage.data[x2 * edgeImage.w + y2];

            // Piksel, yatay veya dikey y�nde max ise kenar olarak koru
            if (pixelValue >= neighbor1Value && pixelValue >= neighbor2Value) {
                suppressedImage.data[i * suppressedImage.w + j] = pixelValue;
            }
            // kenar olmayan olarak i�aretle
            else {
                suppressedImage.data[i * suppressedImage.w + j] = 0;
            }
        }
    }

    return suppressedImage;
}

//histerize ve doble thresold ile edge image'i binary edge image'e d�n���t�ren fonks.son 2 paramtere el ile �imdilik manuel olarak girilecek.

image applyHysteresisThreshold(image im, int lowThreshold, int highThreshold) {//non-max ile gelen edge image ve 2 threshold de�eri.


    image edgeImage;
    edgeImage.h = im.h;
    edgeImage.w = im.w;
    edgeImage.c = 1;
    edgeImage.data = new unsigned char[im.w * im.h];

    // Hysteresis e�ikleme i�lemi
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int pixelIndex = i * im.w + j;//kolayl�k olsun diye bu sefer b�yle yapt�m.

            // Pikselin de�erini kontrol et
            int pixelValue = im.data[pixelIndex];

            // Y�ksek e�ik de�eri �zerindeki pikselleri kenar olarak i�aretle
            if (pixelValue >= highThreshold) {
                edgeImage.data[pixelIndex] = 255;
            }
            // D���k e�ik de�eri alt�ndaki pikselleri kenar olmayan olarak i�aretle
            else if (pixelValue <= lowThreshold) {
                edgeImage.data[pixelIndex] = 0;
            }

            // Arada kalan pikselleri kom�ular�na bakarak belirle.
            else {
                bool isEdge = false;

                // Pikselin 8 kom�usunu kontrol et
                for (int m = -1; m <= 1; m++) {
                    for (int n = -1; n <= 1; n++) {
                        // Kom�u pikselin indislerini hesapla
                        int neighborIndex = (i + m) * im.w + (j + n);

                        // Kom�u pikselin de�erini kontrol et
                        int neighborValue = im.data[neighborIndex];

                        // Y�ksek e�ik de�eri �zerindeki kom�u varsa, pikseli kenar olarak i�aretle
                        if (neighborValue >= highThreshold) {
                            edgeImage.data[pixelIndex] = 255;
                            isEdge = true;
                            break;
                        }
                    }

                    if (isEdge) {
                        break;
                    }
                }

                // Kenar olarak i�aretlenmeyen pikselleri kenar olmayan olarak i�aretle
                if (!isEdge) {
                    edgeImage.data[pixelIndex] = 0;
                }
            }
        }
    }

    return edgeImage;
}



image cannyEdgeDetection(image im) {

    /*double GKernel[5][5];
    createGaussianKernel5x5(GKernel);
    int kernel_size = 5;*/

    double GKernel[7][7];
    createGaussianKernel7x7(GKernel);
    int kernel_size = 7;

    /*double GKernel[9][9];
    createGaussianKernel9x9(GKernel);
    int kernel_size = 9;*/

    image blurredImage = gaussianBlur(gaussianBlur(im));//1.A�AMA: resmi 2 defa bulan�kla�t�r.


    image edgeImage = sobelFilter(blurredImage);//2.A�AMA: sobel filtresi ile edge image elde et
    image angleImage = angleImageFilter(blurredImage);//2:A�AMA: angle image
    image suppressedImage = nonMaximumSuppression(edgeImage, angleImage);//3.A�AMA: nonmax ile kenar incelt.
    image binaryEdgeImage = applyHysteresisThreshold(suppressedImage, 20, 100);//4.A�AMA: histerize ile kesin kenar sonu�lar� bul.

    return binaryEdgeImage;

}
