#include "image.h"
#include <iostream>
#include <cmath>

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

