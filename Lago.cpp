#include "Lago.h"

Lago::Lago() {
	objmodel_ptr = NULL;

	if (!objmodel_ptr) {
		objmodel_ptr = glmReadOBJ("./Mallas/lago.obj");
		if (!objmodel_ptr)
			exit(0);
		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}
}

void Lago::DibujarObjeto() {
	glPushMatrix();
	glScalef(10, 10, 10);
	glTranslatef(1.5, 0, -2);
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);

	glPopMatrix();
}

Lago::~Lago() {
	objmodel_ptr = NULL;
}