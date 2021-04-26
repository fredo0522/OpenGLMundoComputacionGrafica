#include "Molino.h"

Molino::Molino(float ax, float ay, float az)
{
	this->x = ax;
	this->y = ay;
	this->z = az;

	if (!this->objmodel_ptr)
	{
		this->objmodel_ptr = glmReadOBJ("./Mallas/windmill.obj");
		if (!this->objmodel_ptr)
			exit(0);

		glmUnitize(this->objmodel_ptr);
		glmFacetNormals(this->objmodel_ptr);
		glmVertexNormals(this->objmodel_ptr, 90.0);
	}
}

void Molino::DibujarObjeto()
{
	glPushMatrix();
		glTranslatef(this->x, this->y, this->z);
		glScalef(5, 5, 5);
		glRotatef(-90, 0, 1, 0);
		glmDraw(this->objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}

Molino::~Molino()
{
	this->objmodel_ptr = NULL;
}

