#include "image.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

image sobelFilter(image im) {

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
            int tempx = GradientXImage.data[i * im.w + j];
            int tempy = GradientYImage.data[i * im.w + j];
            int result = tempx * tempx + tempy * tempy;
            EdgeImage.data[i * im.w + j] = sqrt(result);
        }
    }

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
            int tempx = GradientXImage.data[i * im.w + j];
            int tempy = GradientYImage.data[i * im.w + j];
            int result = tempx * tempx + tempy * tempy;
            EdgeImage.data[i * im.w + j] = sqrt(result);
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

//
//void createGaussianKernel5x5(double GKernel[][5]) {//5x5 lik gaussian blur kernel mask üreten fonksiyon
//
//    //standart sapma
//    double sigma = 1.0;
//    double r, s = 2.0 * sigma * sigma;
//
//    //normalizasyon
//    double sum = 0.0;
//
//    // 5x5 kernel üreten for döngüsü
//    for (int x = -2; x <= 2; x++) {
//        for (int y = -2; y <= 2; y++) {
//
//            r = sqrt(x * x + y * y);
//            GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (3.14 * s);
//            sum += GKernel[x + 2][y + 2];
//        }
//    }
//
//    // normalizasyon
//    for (int i = 0; i < 5; ++i)
//        for (int j = 0; j < 5; ++j)
//            GKernel[i][j] /= sum;
//}



void createGaussianKernel7x7(double GKernel[][7]) {

    // standart sapma
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    //normalizasyon
    double sum = 0.0;

    // 7x7 kernel üreten for döngüsü
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


image cannyEdgeDetection(image im) {

    //1.AÞAMA : GAUSSIAN BLUR ÝLE BLURLU RESÝM ELDE ETME
    
    //double GKernel[5][5];//gaussian blur kernel yarat
    double GKernel[7][7];
    //createGaussianKernel5x5(GKernel);//5x5 kernel deðerlerini hesapla
    createGaussianKernel7x7(GKernel);//7x7 kernel deðerlerini hesapla

    int kernel_size = 7;
   

    image blurredImage;//bulanýklaþtýrýalacak resmi tutan nesne
    blurredImage.h = im.h;
    blurredImage.w = im.w;
    blurredImage.c = 1;
    blurredImage.data = new unsigned char[im.w * im.h];


    //fonksiyona gelen gri resim önce gaussian blur kernel ile  convole edilir.
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {

            int sumX = 0;
            int sumY = 0;

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
    //burada resim blurlanmýþtýr.
    // 
    //min-max normalization ile pixel deðerleri uygun aralýða çekilir.
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

    //bu aþamada uygun pixel aralýklarýnda blur'lu gri resim mevcuttur.
    
    //2.AÞAMA: BLURLU RESMÝ SOBEL FÝLTRESÝNE TABÝ TUTUP GRADÝENT IMAGE 'I HESAPLAMA.
    image edgeImage = sobelFilter(blurredImage);// gri resmi sobel filtresine tabi tutup gradient image'i elde ederiz.

    return edgeImage;

    
}