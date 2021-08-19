#pragma once
#include <cstdint>
class Color
{
public:
	int r, g, b, samples;

	Color(int r, int g, int b, int sampels = 0);
	Color();

	Color operator+(Color other);

	Color output();
};

