#include "Color.h"

Color::Color(int r, int g, int b, int samples) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->samples = samples;
}

Color::Color() {}

Color Color::operator+(Color other) {
	return Color(this->r + other.r, this->g + other.g, this->b + other.b, this->samples + other.samples + 1);
}

Color Color::output() {
	int rOut = static_cast<float>(this->r) / static_cast<float>(this->samples);
	int gOut = static_cast<float>(this->g) / static_cast<float>(this->samples);
	int bOut = static_cast<float>(this->b) / static_cast<float>(this->samples);
	return Color(rOut, gOut, bOut);
}