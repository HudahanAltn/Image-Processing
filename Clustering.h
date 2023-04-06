#pragma once

#include "Image.h";

image convertGrayScale(image im);
int* createHistogram(image im);
image OtsuThresholding(image im, int* hist);