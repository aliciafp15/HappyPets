#include "Recolectable.h"

Recolectable::Recolectable(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game) {


	animation = new Animation("res/recolectable.png", width, height,
		256, 32, 6, 8, true, game);//velocidad de actualizacion = ?,numero de frames = 8

	
}

void Recolectable::update() {
	// Actualizar la animación
	animation->update();

}

void Recolectable::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}