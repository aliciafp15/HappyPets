#pragma once
#include "Actor.h"
class TemporalTile:public Actor
{

public:
	TemporalTile(string filename, float x, float y, Game* game);
	int tiempoEspera = 60;
	bool activado = false;
	void update();
};

