#include "Objeto.h"

class Molino: public Objeto
{
public:
	Molino(float ax, float ay, float az);
	void DibujarObjeto();
	~Molino();
};

