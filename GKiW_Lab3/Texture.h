#pragma once
#include "stdafx.h"

class Texture {
private:


public:
	Texture();
	static GLuint loadBMP_custom(const char * imagepath);
};