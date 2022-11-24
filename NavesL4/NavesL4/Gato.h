#pragma once

#include "Actor.h"
#include "Animation.h" 

class Gato: public Actor
{
public:
	Gato(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	float vxIntelligence;
	int state;
	int orientation;

	int tempoGirar;

	Animation* aDying;

	//movimientos en 4 direcciones
	Animation* aMovingRight;
	Animation* aMovingLeft;
	Animation* aMovingUp;
	Animation* aMovingDown;
	Animation* aIdleRight;
	Animation* aIdleLeft;



	Animation* animation; // Referencia a la animación mostrada
};
