#include "Libro.h"

Libro::Libro(float ax, float ay, float az)
{
	this->x = ax;
	this->y = ay;
	this->z = az;

	if (!this->objmodel_ptr)
	{
		this->objmodel_ptr = glmReadOBJ("./Mallas/book.obj");
		if (!this->objmodel_ptr)
			exit(0);

		glmUnitize(this->objmodel_ptr);
		glmFacetNormals(this->objmodel_ptr);
		glmVertexNormals(this->objmodel_ptr, 90.0);
	}
}

void Libro::DibujarObjeto()
{
	glPushMatrix();
		glTranslatef(this->x, this->y, this->z);
		glScalef(1.6, 1.6, 1.6);
		glRotatef(-12, 0, 1, 0);
		glmDraw(this->objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL); 
	glPopMatrix();
}

Libro::~Libro()
{
	this->objmodel_ptr = NULL;
}

