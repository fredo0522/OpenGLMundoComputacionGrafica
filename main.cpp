//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include <FreeImage.h>
#include "Molino.h"
#include "Libro.h"
#include "Lago.h"
#include "Demonio.h"
#include "Muelle.h"

#define DELTA_X 0.05

//-----------------------------------------------------------------------------
GLuint texid;

class myWindow : public cwc::glutWindow
{
protected:
	cwc::glShaderManager SM;
	cwc::glShader* shader;
	GLuint ProgramObject;
	clock_t time0, time1;
	float timer010;  // timer counting 0->1->0
	bool bUp;        // flag if counting up or down.

	// Variables de movimiento
	bool movXizq, movXder;
	bool movZup, movZdown;
	float camX;
	float camZ;

	// Instancias de objetos
	Demonio demonio;
	Molino* molino;
	Libro* libro;
	Lago lago;
	Muelle muelle;

public:
	myWindow() {}

	void initialize_textures(void)
	{
		int w, h;
		GLubyte* data = 0;
		data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;
		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./objs/soccer_ball_diffuse2.jpg", 0),
			"./objs/soccer_ball_diffuse2.jpg");
		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);
	}

	void posCamara() {
		if (movXizq)
			camX = camX + DELTA_X;
		else if (movXder)
			camX = camX - DELTA_X;

		// lo ponemos en diferentes condicionales por si se quiere mover
		// diagonalmente (oprimiendo dos teclas)
		if (movZup)
			camZ = camZ + DELTA_X;
		else if (movZdown)
			camZ = camZ - DELTA_X;
	}

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		if (shader) shader->begin();

			// Simulacion camara/observador
			posCamara();
			glTranslatef(camX, -2, camZ);

			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texid); 
				molino->DibujarObjeto();
				libro->DibujarObjeto();
				lago.DibujarObjeto();

				demonio.angle = timer010 * 360;
				demonio.DibujarObjeto();

				muelle.DibujarObjeto();
			glPopMatrix();

		if (shader) shader->end();
		glutSwapBuffers();
		glPopMatrix();

		UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		initialize_textures();


		shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
		if (shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
			ProgramObject = shader->GetProgramObject();

		time0 = clock();
		timer010 = 0.0f;
		bUp = true;

		// variable movimiento
		// pos X
		movXizq = false;
		movXder = false;
		camX = 0.0;
		// posZ
		movZup = false;
		movZdown = false;
		camZ = -40.0;


		// Elementos/Mallas de blender
		molino = new Molino(-15, 4, 0); // 100m/8 = 12.5m (para hacer el escalamiento)
		libro = new Libro(-11, 0, 0); // N = 6
		lago = Lago();
		demonio = Demonio();
		muelle = Muelle();

		DemoLight();

	}

	virtual void OnResize(int w, int h)
	{
		if (h == 0) h = 1;
		float ratio = 1.0f * (float)w / (float)h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glViewport(0, 0, w, h);

		gluPerspective(45, ratio, 1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, 4.0f,
			0.0, 0.0, -1.0,
			0.0f, 1.0f, 0.0f);
	}

	virtual void OnClose(void) {}
	virtual void OnMouseDown(int button, int x, int y) {}
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

	virtual void OnKeyDown(int nKey, char cAscii)
	{
		switch (cAscii) {
		case 27: // 0x1b = ESC
			this->Close(); // close window
			break;
		case 'a':
			movXizq = true;
			break;
		case 'd':
			movXder = true;
			break;
		case 'w':
			movZup = true;
			break;
		case 's':
			movZdown = true;
			break;
		}
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		switch (cAscii) {
		case 'a':
			movXizq = false;
			break;
		case 'd':
			movXder = false;
			break;
		case 'w':
			movZup = false;
			break;
		case 's':
			movZdown = false;
			break;
		}
	}

	void UpdateTimer()
	{
		time1 = clock();
		float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
		delta = delta / 4;
		if (delta > 0.00005f)
		{
			time0 = clock();
			if (bUp)
			{
				timer010 += delta;
				if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
			}
			else
			{
				timer010 -= delta;
				if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
			}
		}
	}

	void DemoLight(void)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		// Light model parameters:
		// -------------------------------------------

		GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

		// -------------------------------------------
		// Spotlight Attenuation

		GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
		GLint spot_exponent = 30;
		GLint spot_cutoff = 180;

		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
		glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

		GLfloat Kc = 1.0;
		GLfloat Kl = 0.0;
		GLfloat Kq = 0.0;

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


		// ------------------------------------------- 
		// Lighting parameters:

		GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
		GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
		GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

		// -------------------------------------------
		// Material parameters:

		GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
		GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
		GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
		GLfloat material_Se = 20.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
	}
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() { std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication* pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

