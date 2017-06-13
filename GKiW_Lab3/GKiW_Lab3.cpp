#include "stdafx.h"
#include "GKiW_Lab3.h"
#include "Vec3.h"
#include "GameObject.h"
#include "Model.h"
#include "Player.h"
#include "Image.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

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

std::vector <Image*> GearImages;

Image * playerwon = new Image();
int winner = 0; //1-gracz 2-PC
Image * computerwon = new Image();
Image * rpmbar = new Image();
Image * rpmscale = new Image();
Image * falsestartimage = new Image();

GameObject * city = new GameObject(0, 0, 0);

int COMPUTER_GEAR_UP_RPM = 2300;
int COMPUTER_FIRST_GEAR_UP_RPM = 3000;

bool startb = true;
bool sterowanieb = true;
bool once = true;

Image * startimage = new Image();
Image * sterowanieimage = new Image();

using namespace std;

void OponentEnable(int)
{
	oponent->SetEnabled();
}

void WhoWin()	//ewentualnie popraw to zeby po zatrzymaniu i pozniej puszczeniu gry nie wygra³ drugi
{
	if (winner == 0)
	{

		if (gracz->GetPosZ() > 1988)
		{
			winner = 1;
			//playerwin = true;
			//cout << "WYGRAL GRACZ" << endl;		
			//cin >> T;
		}

		if (oponent->GetPosZ() > 1988)
		{
			winner = 2;
			//computerwin = true;
			//cout << "WYGRAL KOMPUTER" << endl;
			//cin >> T;
		}
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

	start->LoadModel("models\\start.obj", "models\\start2.bmp");
	road1->LoadModel("models\\road.obj", "models\\road3.bmp");
	road2->LoadModel("models\\road.obj", "models\\road3.bmp");
	finish->LoadModel("models\\finish.obj", "models\\finish3.bmp");
	road3->LoadModel("models\\road.obj", "models\\road3.bmp");
	light->LoadModel("models\\light.obj", "models\\light3.bmp");
	gracz->LoadModel("models\\lp4.obj", "models\\lp4.bmp");
	oponent->LoadModel("models\\lp4.obj", "models\\lp4purple.bmp");
	plane->LoadModel("models\\plane.obj", "models\\planeGameOver.bmp");
	playerwon->LoadImg("models\\playerwon.bmp");
	computerwon->LoadImg("models\\computerwon.bmp");
	rpmbar->LoadImg("models\\rpmbar.bmp");
	rpmscale->LoadImg("models\\rpmscale.bmp");
	falsestartimage->LoadImg("models\\falsestart.bmp");
	city->LoadModel("models\\plane2.obj", "models\\city.bmp");
	startimage->LoadImg("models\\start.bmp");
	sterowanieimage->LoadImg("models\\sterowanie.bmp");

	for (int i = 0; i <= 4; i++)
	{
		GearImages.push_back(new Image());
		char imagepath[50];

		strcpy(imagepath, "models\\gears\\");
		strcat(imagepath, std::to_string(i).c_str());
		strcat(imagepath, ".bmp");

		GearImages[i]->LoadImg(imagepath);
	}

	PlaySound(TEXT("12.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	oponent->ClearEnabled();

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

		if (key == 32)					// Nie moze byc nizej
			gracz->GearUp();

		if (key == 'f')					
			startb = false;

		if (key == 'g')					
			sterowanieb = false;

		keystate[key] = false;
	}

	void OnSpecialKeyUp(int key, int x, int y) {
		keystate_special[key] = false;
	}

#pragma endregion

void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);
	
	T = glutGet(GLUT_ELAPSED_TIME); // Ile milisekund uplynelo od momentu uruchomienia programu?

		if (keystate['w']) {
			gracz->SetVelocity(0.5);
			gracz->GainRPM();
			gracz->GainAcc();
		}

		if (keystate['l']) {
			cout << gracz->GetPosX() << "\t " << gracz->GetPosY() << "\t " << gracz->GetPosZ() << endl;
		}

		if (keystate['z']) {
			COMPUTER_GEAR_UP_RPM = 2300;
			COMPUTER_FIRST_GEAR_UP_RPM = 3000;
		}

		if (keystate['x']) {
			COMPUTER_GEAR_UP_RPM = 2400;
			COMPUTER_FIRST_GEAR_UP_RPM = 2650;
		}

		if (keystate['c']) {
			COMPUTER_GEAR_UP_RPM = 2550;
			COMPUTER_FIRST_GEAR_UP_RPM = 2500;
		}

		gracz->MoveForward();

		gracz->LooseSpeed();
		gracz->LooseRPM();
		gracz->LooseAcc();
		gracz->LooseBooster();
		
		//cout << "rpm: " << gracz->GetRPM() << "\tg: " << gracz->GetGear() << "\t acc " << gracz->GetAcc() << "\t b " << gracz->GetBooster() << "\t m " << gracz->GetMoved() << endl;
		//cout << "rpm: " << oponent->GetRPM() << "\tg: " << oponent->GetGear() << "\t acc " << oponent->GetAcc() << "\t b " << oponent->GetBooster() << endl;

		//oponent
		oponent->SetVelocity(0.5);
		oponent->MoveForward();

		if (oponent->GetGear() == 0 && oponent->GetRPM() > COMPUTER_FIRST_GEAR_UP_RPM)
		{ }		// na zerowym biegu odpusc obroty jak > 3000 , w przeciwnym przypadku GAZU! //level
		else
		{
			oponent->GainRPM();
		}

		oponent->GainAcc();

		if (oponent->GetRPM() > COMPUTER_GEAR_UP_RPM)	//level
		{
			oponent->GearUp();
		}

		oponent->LooseSpeed();
		oponent->LooseRPM();
		oponent->LooseAcc();
		oponent->LooseBooster();

		if (sterowanieb == false && once == true)
		{
			PlaySound(TEXT("11s.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			glutTimerFunc(2200, CountdownYellow, 0);									//22
			glutTimerFunc(3400, CountdownGreen, 0);										//34
			gracz->CheckFalseStart();
			glutTimerFunc(3600, OponentEnable, 0);	//kiedy startuje komputer >34bezp	//34

			once = false;
		}
		WhoWin();
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

	city->SetRot(180, 90, 0);
	
	city->SetScal(25,21,1);
	for (int i = -30; i < 2500; i=i+50)
	{
		glDisable(GL_LIGHTING);
		city->SetPosXYZ(-55, 0, i);	
		city->DrawModel();
		glEnable(GL_LIGHTING);
	}

	/////////2D SECTION /////////

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);


	rpmbar->SetScal(0.075, gracz->GetRPM() / 3750, 1.0);
	rpmbar->Draw();

	rpmscale->SetScal(0.05, 1, 1);
	rpmscale->Draw();

	GearImages[gracz->GetGear()]->SetScal(0.10, 0.15, 0.1);
	GearImages[gracz->GetGear()]->Draw();

	if (sterowanieb)
	{
		sterowanieimage->Draw();
	}

	if (startb)
	{
		startimage->Draw();
	}

	glEnable(GL_LIGHTING);

	if (gracz->GetFalstart() == true)
	{
		glDisable(GL_LIGHTING);
		falsestartimage->Draw();
	}

	if (winner == 1)
	{
		glDisable(GL_LIGHTING);
		playerwon->Draw();
	}

	if (winner == 2)
	{
		glDisable(GL_LIGHTING);
		computerwon->Draw();
	}

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
