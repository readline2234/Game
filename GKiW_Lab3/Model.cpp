#include "stdafx.h"
#include <iostream>
#include "Model.h"

Model::Model(char * fp, char *ip)
{
	FILE * file = fopen(fp, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		std::cin >> fp;
		exit(1);
	}

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				std::cin >> fp;
				exit(1);
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i<vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}

	for (unsigned int i = 0; i<uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i<normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	textureID = Texture::loadBMP_custom(ip);

}

void Model::Draw()
{
	glPushMatrix();

	float m0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

	glFrontFace(GL_CW);


	
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_TEXTURE_2D);	//test
	
	glBegin(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		//unsigned int vIndex = vertexIndices[i];
		//unsigned int nIndex = normalIndices[i];
		//unsigned int uIndex = uvIndices[i];

		glm::vec3 vec;
		glm::vec2 vec2;



		vec2 = out_uvs[i];
		glTexCoord2f(vec2.x, vec2.y);

		vec = out_normals[i];
		glNormal3f(vec.x, vec.y, vec.z);

		vec = out_vertices[i];
		glVertex3f(vec.x, vec.y, vec.z);
	}
	
	glEnd();

	

	glDisable(GL_TEXTURE_2D);
}