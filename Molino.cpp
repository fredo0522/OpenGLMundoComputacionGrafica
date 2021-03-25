#include "Molino.h"

Molino::Molino(float x, float y, float z)
{

	this->x = x;
	this->y = y;
	this->z = z;

	this->objmodel_ptr = NULL;

	if (!objmodel_ptr)
	{
		objmodel_ptr = glmReadOBJ("");
		if (!objmodel_ptr)
			exit(0);

		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}
}

void Molino::DibujarObjeto()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL); 
	glPopMatrix();
}

Molino::~Molino()
{
	objmodel_ptr = NULL;
}

