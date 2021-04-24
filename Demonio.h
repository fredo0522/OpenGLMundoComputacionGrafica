#include "Objeto.h"

class Demonio: public Objeto
{
public:
	float angle;
	Demonio();
	void DibujarObjeto();
	void animationAngle();
	~Demonio();
};

