#include "Image.h"

/*ImageLine::ImageLine(int width) : width(width) {
	line = new uint8_t[width];
}

ImageLine::~ImageLine() {
	delete[] line;
}

uint8_t ImageLine::operator[](size_t pixel) {
	return line[pixel];
}

Image::Image(int width, int height, int numSlices) : width(width), height(height), numSlices(numSlices) {
	slices = new ImageLine * [numSlices];
	for (int i = 0; i < numSlices; i++) {
		slices[i] = lineAllocator.allocate(height / numSlices);
		for (int j = 0; j < height / numSlices; j++) {
			lineAllocator.construct(slices[i] + j, width);
		}
	}
}

Image::~Image() {
	for (int i = 0; i < numSlices; i++) {
		for (int j = 0; j < height / numSlices; j++) {
			lineAllocator.destroy(slices[i] + j);
		}
	}
	delete slices;
}

ImageLine& Image::operator[](size_t line) {
	return *slices[line];
}
*/