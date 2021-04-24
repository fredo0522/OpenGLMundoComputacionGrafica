#include "Demonio.h"

Demonio::Demonio() {
	objmodel_ptr = NULL;

	if (!objmodel_ptr) {
		objmodel_ptr = glmReadOBJ("./Mallas/demonio.obj");
		if (!objmodel_ptr)
			exit(0);
		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}
}

void Demonio::DibujarObjeto() {
	glPushMatrix();

		//Posicion inicial
		glTranslatef(15, 0.05, -20);

		// Pivote para hacer la rotacion
		glRotatef(angle, 0.f, 1.f, 0.f);
		glTranslatef(3.5, 0, 0);

		glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);

	glPopMatrix();
}

Demonio::~Demonio() {
	objmodel_ptr = NULL;
}