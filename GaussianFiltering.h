#pragma once
#include "Image.h"


image sobelFilter(image im);
image prewittFilter(image im);
image cannyEdgeDetection(image im);
void createGaussianKernel(void);