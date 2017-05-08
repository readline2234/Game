#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Vec3.h"
#include "glm\glm\glm.hpp"

using namespace std;

class Model {
private:
	int vertices;
	int positions;
	int texels;
	int normals;
	int faces;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Vec3 > temp_vertices;
	std::vector< Vec3 > temp_uvs;
	std::vector< Vec3 > temp_normals;

	std::vector < glm::vec3 > & out_vertices;
	std::vector < glm::vec2 > & out_uvs;
	std::vector < glm::vec3 > & out_normals;

public:
	Model(char * fp);
};