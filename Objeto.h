#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glm/glm.h"

#ifndef __OBJETO_H
#define __OBJETO_H

class Objeto
{
protected:
	float x = 0;
	float y = 0;
	float z = 0;
	GLMmodel* objmodel_ptr = NULL;

public:
	virtual void DibujarObjeto() = 0;
};

#endif
