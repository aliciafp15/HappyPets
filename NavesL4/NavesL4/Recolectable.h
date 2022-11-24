#pragma once
#include "Actor.h"
#include "Animation.h" 

class Recolectable : public Actor
{
public:
	Recolectable(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	Animation* animation; // Referencia a la animaci�n mostrada
};

