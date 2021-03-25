#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glm/glm.h"

class Objeto
{
private:
	float x;
	float y;
	float z;
	GLMmodel *objmodel_ptr;
public:
	void DibujarObjeto();
};

