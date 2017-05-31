#include "stdafx.h"
#include "GKiW_Lab3.h"
#include "Vec3.h"
#include "GameObject.h"
#include "Model.h"
#include "Player.h"

GameObject * start = new GameObject(0, 0, 0);
GameObject * road1 = new GameObject(0, 0, 0);
GameObject * road2 = new GameObject(0, 0, 0);
GameObject * road3 = new GameObject(0, 0, 0);
GameObject * finish = new GameObject(0, 0, 0);

GameObject * light = new GameObject(0, 0, 0);

Player * gracz = new Player(2.2, -1.1, 1);
Player * oponent = new Player(-2.2, -1.1, 1);

GameObject * plane = new GameObject(0, 0, 0);
GLint teks;

using namespace std;

void OponentEnable(int)
{
	oponent->SetEnabled();
}
void WhoWin()	//ewentualnie popraw to zeby po zatrzymaniu i pozniej puszczeniu gry nie wygra³ drugi
{
	if (gracz->GetPosZ() > 1988)
	{
		cout << "WYGRAL GRACZ" << endl;		
		cin >> T;
	}

	if (oponent->GetPosZ() > 1988)
	{
		cout << "WYGRAL KOMPUTER" << endl;
		cin >> T;
	}

	return;
}

void CountdownYellow(int)
{
		light->LoadModel("models\\light.obj", "models\\light2.bmp");
}

void CountdownGreen(int)
{
	light->LoadModel("models\\light.obj", "models\\light1.bmp");
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("BOOSTER");

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

	start->LoadModel("models\\start.obj", "models\\start2.bmp");
	road1->LoadModel("models\\road.obj", "models\\road3.bmp");
	road2->LoadModel("models\\road.obj", "models\\road3.bmp");
	finish->LoadModel("models\\finish.obj", "models\\finish3.bmp");
	road3->LoadModel("models\\road.obj", "models\\road3.bmp");

	light->LoadModel("models\\light.obj", "models\\light3.bmp");

	gracz->LoadModel("models\\lp4.obj", "models\\lp4.bmp");
	oponent->LoadModel("models\\lp4.obj", "models\\lp4purple.bmp");

	plane->LoadModel("models\\plane.obj", "models\\planeGameOver.bmp");

	Texture * tex = new Texture();
	teks = tex->loadBMP_custom("models\\planeGameOver.bmp");

	oponent->ClearEnabled();

	glutTimerFunc(2200, CountdownYellow, 0);									//22
	glutTimerFunc(3400, CountdownGreen, 0);										//34
	gracz->CheckFalseStart();
	glutTimerFunc(3600, OponentEnable, 0);	//kiedy startuje komputer >34bezp	//34


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

		if (key == 'i')					// Nie moze byc nizej
			gracz->GearUp();

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

		if (keystate['o']) {
			//gracz->SetVelocity = gracz->GetSpeed();
			gracz->SetVelocity(0.5);
			gracz->GainRPM();
			gracz->GainAcc();
			//cout << "v: " << gracz->GetVelocity() << endl;
		}

		if (keystate['l']) {
			cout << gracz->GetPosX() << "\t " << gracz->GetPosY() << "\t " << gracz->GetPosZ() << endl;
		}

		if (!keystate['i']) 
		{
			// bieg w gorê - gracz->GearUp(), definicja wyzej w KeyUp
		}

		if (keystate['u'])
		{
			//gracz->SetEnabled();
			//oponent->SetEnabled();
			gracz->Teleport();
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
		gracz->MoveForward();
		// Chodzenie na boki
		player.pos.x += per.x * player.velS * .1f;
		player.pos.z += per.z * player.velS * .1f;
		
		// Bezwladnosc - w kazdym cyklu maleje predkosc gracza
		player.velM /= 1.2;
		player.velS /= 1.2;

		gracz->LooseSpeed();
		gracz->LooseRPM();
		gracz->LooseAcc();
		gracz->LooseBooster();
		
		// MIKEMIKEMIKE
		//glutTimerFunc(3300, OponentEnable, 0);	//kiedy startuje komputer


		cout << "rpm: " << gracz->GetRPM() << "\tg: " << gracz->GetGear() << "\t acc " << gracz->GetAcc() << "\t b " << gracz->GetBooster() << "\t m " << gracz->GetMoved() << endl;
		//cout << "rpm: " << oponent->GetRPM() << "\tg: " << oponent->GetGear() << "\t acc " << oponent->GetAcc() << "\t b " << oponent->GetBooster() << endl;

		//oponent
		oponent->SetVelocity(0.5);
		oponent->MoveForward();

		if (oponent->GetGear() == 0 && oponent->GetRPM() > 3000)
		{ }		// na zerowym biegu odpusc obroty jak > 3000 , w przeciwnym przypadku GAZU!
		else
		{
		oponent->GainRPM();
		}

		oponent->GainAcc();
		if (/*oponent->GetGear() == 1 &&*/ oponent->GetRPM() > 2300 )
		{
			oponent->GearUp();
		}

		oponent->LooseSpeed();
		oponent->LooseRPM();
		oponent->LooseAcc();
		oponent->LooseBooster();




		WhoWin();

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Using gluPerspective. It's pretty easy and looks nice.
	gluPerspective(60.0f, (float)800 / 600, .01f, 100.0f); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//gluLookAt(
	//	player.pos.x, player.pos.y, player.pos.z,
	//	player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
	//	0.0f, 1.0f, 0.0f
	//);

	gluLookAt(
		9.0f, 4.0f, gracz->GetPosZ()-4,//-6.0f,
		0.0f,0.0f, gracz->GetPosZ(),
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

	start->SetPosXYZ(0, -1, 0);
	start->SetScal(0.5, 0.5, 0.5);
	start->DrawModel();

	//road1->SetPosXYZ(0, -1, 19.5);
	//road1->SetScal(0.5, 0.5, 0.5);
	//road1->DrawModel();

	road2->SetPosXYZ(0, -1, 487);
	road2->SetScal(0.5, 0.5, 50);
	road2->DrawModel();

	finish->SetPosXYZ(0, -1, 1988.5);
	finish->SetRot(0, 180, 0);
	finish->SetScal(0.5, 0.5, 0.5);
	finish->DrawModel();

	road3->SetPosXYZ(0, -1, 2465.5);
	road3->SetScal(0.5, 0.5, 50);
	road3->DrawModel();
	
	light->SetPosXYZ(0, 1.5, 7.5);
	light->SetScal(0.5, 0.5, 0.5);
	light->DrawModel();

	gracz->SetScal(0.5, 0.5, 0.5);
	gracz->DrawModel();

	oponent->SetScal(0.5, 0.5, 0.5);
	oponent->DrawModel();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	float m0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

	glFrontFace(GL_CW);



	glBindTexture(GL_TEXTURE_2D, teks);
	
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex2f(50, 50);
	glTexCoord2f(0, 0);
	glVertex2f(50, 500);
	glTexCoord2f(1, 0);
	glVertex2f(500, 500);
	glTexCoord2f(1, 1);
	glVertex2f(500, 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	
	glDepthMask(GL_TRUE);

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
