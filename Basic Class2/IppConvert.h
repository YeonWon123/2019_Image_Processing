#pragma once

#include "IppImage.h"
#include "IppDib.h"

void IppDibToImage(IppDib& dib, IppByteImage& img);
void IppDibToImage(IppDib& dib, IppRgbImage& img);

void IppImageToDib(IppByteImage& img, IppDib& dib);
void IppImageToDib(IppFloatImage& img, IppDib& dib);
void IppImageToDib(IppRgbImage& img, IppDib& dib);
