#include "Color.h"
#include <iostream>

Color::Color(int r, int g, int b, int samples) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->samples = samples;
}

Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->samples = 0;
}

Color Color::operator+(Color other) {
	return Color(this->r + other.r, this->g + other.g, this->b + other.b, this->samples + other.samples + 1);
}

Color Color::operator*(float scale) {
	int rOut = static_cast<int>(static_cast<float>(this->r) * scale);
	int gOut = static_cast<int>(static_cast<float>(this->g) * scale);
	int bOut = static_cast<int>(static_cast<float>(this->b) * scale);
	return Color(rOut, gOut, bOut, this->samples);
}

Color Color::output() {
	//std::cout << this->samples << "  ";
	float scale = 1 / static_cast<float>(this->samples);
	int rOut = static_cast<int>(static_cast<float>(this->r) * scale);
	int gOut = static_cast<int>(static_cast<float>(this->g) * scale);
	int bOut = static_cast<int>(static_cast<float>(this->b) * scale);
	if (rOut > 255) 
		rOut = 255;

	if (gOut > 255) 
		gOut = 255;

	if (bOut > 255) 
		bOut = 255;
	static_cast<uint8_t> (rOut);
	static_cast<uint8_t> (gOut);
	static_cast<uint8_t> (bOut);
	return Color(rOut, gOut, bOut);
}