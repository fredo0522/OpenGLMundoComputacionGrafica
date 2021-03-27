#include "Muelle.h"

Muelle::Muelle() {
	objmodel_ptr = NULL;

	if (!objmodel_ptr) {
		objmodel_ptr = glmReadOBJ("./Mallas/Muelle.obj");
		if (!objmodel_ptr)
			exit(0);
		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}
}

void Muelle::DibujarObjeto() {
	glPushMatrix();
	glScalef(7, 7, 7);
	glTranslatef(1.3, 0.3, -1.7);
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);

	glPopMatrix();
}

Muelle::~Muelle() {
	objmodel_ptr = NULL;
}