#include "Objeto.h"

class Molino: public Objeto
{
public:
	Molino(float x, float y, float z);
	void DibujarObjeto();
	~Molino();
};

