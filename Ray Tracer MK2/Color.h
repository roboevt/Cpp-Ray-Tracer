#pragma once
#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	unsigned int r, g, b, samples;

	Color(unsigned int r, unsigned int g, unsigned int b, unsigned int sampels = 0);
	Color();

	Color operator+(Color other);

	Color operator*(float scale);

	Color output();
};

#endif