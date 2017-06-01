#pragma once
#include "Texture.h"
#include "Vec3.h"

class Image {

private:
	GLint texID;
	Texture * tex;
	Vec3 * scal;
public:
	void SetScal(float x, float y, float z);

	void LoadImg(const char * imagepath);
	void Draw();
};