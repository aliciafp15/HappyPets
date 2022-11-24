#include "Puerta.h"
Puerta::Puerta(float x, float y, int pTipo, Game* game)
	: Actor("res/puerta.png", x, y, 35, 34, game) {
	tipo = pTipo;

}


