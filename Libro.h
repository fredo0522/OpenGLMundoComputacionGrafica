#include "Objeto.h"

class Libro: public Objeto
{
public:
	Libro(float x, float y, float z);
	void DibujarObjeto();
	~Libro();
};

