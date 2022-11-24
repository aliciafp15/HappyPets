#include "Gato.h"

Gato::Gato(float x, float y, Game* game)
	: Actor("res/gatos/gato_blanco.png", x, y, 32, 32, game) {
	tempoGirar = 300;

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aMovingLeft = new Animation("res/gatos/gato_blanco_izquierda.png", width, height,
		126, 42, 6, 3, true, game);
	animation = aMovingLeft;

	aMovingRight = new Animation("res/gatos/gato_blanco_derecha.png", width, height,
		126, 42, 6, 3, true, game);
	animation = aMovingRight;

	/*
	aMovingUp = new Animation("res/gatos/gato_blanco_arriba.png", width, height,
		126, 42, 6, 3, true, game);
	animation = aMovingUp;

	aMovingDown = new Animation("res/gatos/gato_blanco_abajo.png", width, height,
		126, 42, 6, 3, true, game);
		*/

	aIdleLeft = new Animation("res/gatos/gato_blanco_idle_izquierda.png", width, height,
		126, 42, 6, 3, true, game);
	animation = aIdleLeft;

	aIdleRight = new Animation("res/gatos/gato_blanco_idle_derecha.png", width, height,
		126, 42, 6, 3, true, game);
	animation = aIdleRight;

	
	vx = 1;
	vxIntelligence = -1;
	vx = 1;
	

}

void Gato::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	
	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	if (vx != 0) {
		if (orientation == game->orientationRight) {
			animation = aMovingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aMovingLeft;
		}
	}

	if (vx == 0) {
		if (orientation == game->orientationRight) {
			animation = aIdleRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aIdleLeft;
		}
	}
	/*
	//MOVIMIENTO ARTIFICIAL:
	//quieto derecha
	if (vx == 0) {
		vxIntelligence = vxIntelligence * -1;
		vx = vxIntelligence;
	}
	//		detectar chocques con objetos estáticos:
	//si es falso es que no s ehan detectado choques
	//se empieza con todo a true
	if (outRight) {//algo chocando en la derecha
		// mover hacia la izquierda vx tiene que ser negativa
		if (vxIntelligence > 0) {
			vxIntelligence = vxIntelligence * -1;
		}
		vx = vxIntelligence;
	}
	if (outLeft) {
		// mover hacia la derecha vx tiene que ser positiva
		if (vxIntelligence < 0) {
			vxIntelligence = vxIntelligence * -1;
		}
		vx = vxIntelligence;
	}
	*/


	if (tempoGirar == 0) {
		//si estaba mirando a la derecha, ahora hacia la izquierda
		if (orientation == game->orientationRight) {
			orientation = game->orientationLeft;
			vx = -1;
		} 
		else {
			orientation = game->orientationRight;
			vx = 1;
		}
	
		tempoGirar = 300;
	}
	else {

		tempoGirar--;
	}




}


void Gato::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}


