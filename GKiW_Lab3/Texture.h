#pragma once
#include "stdafx.h"

class Texture {
private:
	Texture();

public:
	static GLuint loadBMP_custom(const char * imagepath);
};