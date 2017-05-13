#include "stdafx.h"
#include "GKiW_Lab3.h"
#include "Vec3.h"
#include "GameObject.h"
#include "Model.h"

Vec3 * wektor = new Vec3(0, 0, 0);
//std::cout << *wektor << std::endl;
//GameObject * obiekt = new GameObject(0, 0, 0);
GameObject * obiekt = new GameObject(*wektor);
//Model * mod = new Model("models\\cb4.obj");

GameObject * obiekt2 = new GameObject(*wektor);
GameObject * obiekt3 = new GameObject(*wektor);


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GAME");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyPress); // klawisze specjalne (strzalki, F1-F12, PgUp/PgDn, Home, End, Delete, Insert)
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	// Ustawiamy komponent ambient naszej sceny - wartosc niezalezna od swiatla (warto zresetowac)
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glShadeModel(GL_SMOOTH); // Wybor techniki cieniowania
	glEnable(GL_LIGHT0); // Wlaczenie 0-go zrodla swiatla

	player.pos.x = 0.0f;
	player.pos.y = 0.0f;
	player.pos.z = 8.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = 1.50f;

	//obiekt2->LoadModel("models\\test.obj","models\\test.bmp");
	obiekt2->LoadModel("models\\asw.obj", "models\\asw.bmp");
	obiekt2->LoadModel("models\\poly.obj", "models\\poly3.bmp");
	
	
	



	glutMainLoop();

	return 0;
}

#pragma region Obsluga wejscia

	bool keystate[256];
	bool keystate_special[256];

	void OnKeyPress(unsigned char key, int x, int y) {
		if (!keystate[key]) {
			OnKeyDown(key, x, y);
		}
		keystate[key] = true;
	}

	void OnSpecialKeyPress(int key, int x, int y) {
		if (!keystate_special[key]) {
			OnSpecialKeyDown(key, x, y);
		}
		keystate_special[key] = true;
	}

	void OnKeyDown(unsigned char key, int x, int y) {
		if (key == 27) {
			glutLeaveMainLoop();
		}
	}

	void OnSpecialKeyDown(int key, int x, int y) {
	}

	void OnKeyUp(unsigned char key, int x, int y) {
		keystate[key] = false;
	}

	void OnSpecialKeyUp(int key, int x, int y) {
		keystate_special[key] = false;
	}

#pragma endregion

void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);
	
	T = glutGet(GLUT_ELAPSED_TIME); // Ile milisekund uplynelo od momentu uruchomienia programu?

	#pragma region Ruch kamery

		// Zmiana predkosci gracza jesli wcisniete W/S/A/D
		if (keystate['w']) {
			player.velM = player.speed;
		}
		if (keystate['s']) {
			player.velM = -player.speed;
		}
		if (keystate['a']) {
			player.velS = -player.speed;
		}
		if (keystate['d']) {
			player.velS = player.speed;
		}

		// Obrot kamery
		float phi = atan2(player.dir.z, player.dir.x);
		if (keystate['q']) {
			phi -= .03f;
		}
		if (keystate['e']) {
			phi += .03f;
		}

		player.dir.x = cos(phi);
		player.dir.z = sin(phi);

		// Znalezienie kierunku prostopadlego
		vec3 per;
		per.x = -player.dir.z;
		per.z = player.dir.x;

		// Chodzenie przod/tyl
		player.pos.x += player.dir.x * player.velM * .1f;
		player.pos.y += player.dir.y * player.velM * .1f;
		player.pos.z += player.dir.z * player.velM * .1f;

		// Chodzenie na boki
		player.pos.x += per.x * player.velS * .1f;
		player.pos.z += per.z * player.velS * .1f;
		
		// Bezwladnosc - w kazdym cyklu maleje predkosc gracza
		player.velM /= 1.2;
		player.velS /= 1.2;

	#pragma endregion

	#pragma region Ruch swiatla

		if (keystate_special[GLUT_KEY_LEFT]) {
			LightPos.x -= .05f;
		}
		if (keystate_special[GLUT_KEY_RIGHT]) {
			LightPos.x += .05f;
		}
		if (keystate_special[GLUT_KEY_UP]) {
			LightPos.y += .05f;
		}
		if (keystate_special[GLUT_KEY_DOWN]) {
			LightPos.y -= .05f;
		}

	#pragma endregion
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z,
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
		0.0f, 1.0f, 0.0f
	);

	#pragma region Swiatlo

		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { LightPos.x, LightPos.y, LightPos.z, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	#pragma endregion

	obiekt->SetScal(1, 1, 5);
	obiekt->SetRot(T / 100, T / 100, T / 100);
	//obiekt->Draw();
	//mod->Draw();

	
	obiekt2->DrawModel();
	//obiekt2->Draw();

	#pragma region Szescian
	
		float m0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -2.0f);
			glRotatef(.05f * T, 0.0f, 1.0f, 0.0f);
			glRotatef(45.0f, 1.0f, 0.0f, 1.0f);
			glutSolidCube(1.0f);
		glPopMatrix();

	#pragma endregion
	
	#pragma region Kula 1
	
		float m1_amb[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float m1_dif[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float m1_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

		glPushMatrix();
			glTranslatef(-2.0f, 2.0f, 0.0f);
			glutSolidSphere(1.0f, 32, 32);
		glPopMatrix();

	#pragma endregion
	
	#pragma region Kula 2
	
		float m2_amb[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		float m2_dif[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		float m2_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m2_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m2_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m2_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
	
		glPushMatrix();
			glTranslatef(2.0f, 2.0f, 0.0f);
			glutSolidSphere(1.0f, 32, 32);
		glPopMatrix();

	#pragma endregion
	
	#pragma region Kula 3
	
		float m3_amb[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float m3_dif[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float m3_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m3_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m3_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m3_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

		glPushMatrix();
			glTranslatef(-2.0f, -2.0f, 0.0f);
			glutSolidSphere(1.0f, 32, 32);
		glPopMatrix();

	#pragma endregion
	
	#pragma region Kula 4
	
		float m4_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m4_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m4_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m4_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m4_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m4_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
	
		glPushMatrix();
			glTranslatef(2.0f, -2.0f, 0.0f);
			glutSolidSphere(1.0f, 32, 32);
		glPopMatrix();

	#pragma endregion
	

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
