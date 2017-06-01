#include "stdafx.h"
#include "Image.h"

void Image::SetScal(float x, float y, float z)
{
	scal->SetXYZ(x, y, z);
}

void Image::LoadImg(const char * imagepath)
{
	scal = new Vec3(1, 1, 1);
	tex = new Texture();
	texID = tex->loadBMP_custom(imagepath);
}

void Image::Draw()
{
	glPushMatrix();

	glScalef(scal->GetX(), scal->GetY(), scal->GetZ());	
	// dokoncz skale	//wez argument gracz->rpm przekaz 
	// do nowej napisanej funkcji draw()

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	float m0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

	glFrontFace(GL_CW);

	glBindTexture(GL_TEXTURE_2D, texID);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0); //(50, 50);
	glTexCoord2f(0, 1);
	glVertex2f(0, 600); //(50, 500);
	glTexCoord2f(1, 1);
	glVertex2f(800, 600); //(500, 500);
	glTexCoord2f(1, 0);
	glVertex2f(800, 0); //(500, 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}