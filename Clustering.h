#pragma once

#include "Image.h";

image convertGrayScale(image im);
int* createHistogram(image im);
image OtsuThresholding(image im, int* hist);

float* KMeans_Eucliden(image im, int k);
image KBasedSegmentation(image im, float* kmeans, int k);
unsigned char EuclideanDistance(float data, float* kmeans, int k);