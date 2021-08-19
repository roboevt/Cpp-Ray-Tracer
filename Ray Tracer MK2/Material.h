#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
//#include "Collision.h"
class Material
{
public:
	Color color;
	int shader;

	Color getColor();

	//Collision calculateCollision(Collision& collision);

	//Vector randomInUnitSphere();
};

#endif