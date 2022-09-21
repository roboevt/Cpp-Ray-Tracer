#pragma once
#include <stdint.h>
#include <memory>
/*
class ImageLine
{
	int width;
	uint8_t* line;
public:
	ImageLine(int width);
	uint8_t* operator[](size_t pixel);
	~ImageLine();
	int width() { return width; }
};

class Image
{
	int width, height, numSlices;
	ImageLine** slices;
	std::allocator<ImageLine> lineAllocator;
public:
	Image(int width, int height, int numSlices);
	ImageLine& operator[](size_t line);
	~Image();
	int width() { return width; }
	int height() { return height; }
	int numSlices() { return numSlices; }

};

*/