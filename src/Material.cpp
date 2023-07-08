#include "Material.h"

Material::Material() {
	this->color = Color(255, 255, 255);
	this->absorbtion = .8f;
	this->shader = 1;  // should be enum
}