#include "TemporalTile.h"
TemporalTile::TemporalTile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {

}


void TemporalTile::update() {

	//comprueba cuando tiene un objeto dinámico encima
	if (collisionUp == true) {
		activado = true;
		tiempoEspera--;
	}
	else {
		activado = false;
	}

}