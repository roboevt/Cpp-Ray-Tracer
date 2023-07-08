#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

enum materialTypes {diffuse = 1, reflective = 2, emmisive = 3};

class Material
{
public:
	float absorbtion;
	int shader;
	Color color;
	Material();
};

#endif // !MATERIAL_H