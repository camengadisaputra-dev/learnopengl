#pragma once
#include "glad/glad.h"
#include <iostream>

class Texture
{
public:
	Texture();
	void loadTexture(const char* path, const GLenum format);
	void applyTexture();
private:
	unsigned int ID;
};

