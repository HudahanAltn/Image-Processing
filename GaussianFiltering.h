#pragma once
#include "Image.h"


image sobelFilter(image im);
image prewittFilter(image im);
image cannyEdgeDetection(image im);

void createGaussianKernel5x5(double GKernel[][5]);
void createGaussianKernel7x7(double GKernel[][7]);
void createGaussianKernel9x9(double GKernel[][11]);

image gaussianBlur(image im);

image nonMaximumSuppression(image edgeImage, image angleImage);
image applyHysteresisThreshold(image im, int lowThreshold, int highThreshold);

image cannyEdgeDetection(image im);
