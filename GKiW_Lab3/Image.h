#pragma once
#include "Texture.h"

class Image {

private:
	GLint texID;
	Texture * tex;
public:
	void LoadImg(const char * imagepath);
	void Draw();
};