#pragma once
#include "Actor.h"
class Puerta : public Actor
{

public:
	Puerta(float x, float y, int pTipo, Game* game);
	int tipo;//indicará el numero que tiene en el mapa, para buscar su pareja
};


