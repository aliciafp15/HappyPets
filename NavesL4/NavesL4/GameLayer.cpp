#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)

	init();
}


void GameLayer::init() {


	space = new Space(0);//0, sin gravedad, juego con perspectiva aerea
	//scrollX = 0;
	//scrollY = 0;
	tiles.clear();
	temporalTiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	
	background = new Background("res/background/salon.jpg", WIDTH * 0.5, HEIGHT * 0.5, 0, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);

	//---------contador de los recolectables-------------------------------------------
	backgroundRecolectable = new Actor("res/contador_recolectable.png",
		WIDTH * 0.6, HEIGHT * 0.05, 24, 24, game);

	recolectablePoints = 0;
	textRecolectable = new Text("hola", WIDTH * 0.67, HEIGHT * 0.04, game);
	textRecolectable->content = to_string(recolectablePoints);
	//_--------------------------------------------



	gatos.clear(); // Vaciar por si reiniciamos el juego
	puertas.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	
	case 'G': {
		Gato* gato = new Gato(x, y, game);
		// modificación para empezar a contar desde el suelo.
		gato->y = gato->y - gato->height / 2;
		gatos.push_back(gato);
		space->addDynamicActor(gato);
		break;
	}
	case '1': {
		//si  consiguió punto de salvado, arranca desde él
		if(initialX != 0 or initialY!=0)
			player = new Player(initialX, initialY, game);
		else
			player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}

			
	//ITEMS RECOLECTABLES
	case 'A': {
		Recolectable* rec = new Recolectable(x, y, game);
		// modificación para empezar a contar desde el suelo.
		rec->y = rec->y - rec->height / 2;
		recolectables.push_back(rec);
		break;
	}


	//--------------PUERTAS----------------------
	case '9': {
		//le decimos el tipo de puerta, 9
		Puerta* puerta = new Puerta(x,y,9,game);
		puerta->y = puerta->y - puerta->height / 2;
		puertas.push_back(puerta);
		break;
	}



	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
		


	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}


	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::update() {


	space->update();
	background->update();
	player->update();
	
	for (auto const& Gato : gatos) {
		Gato->update();
	}
	

	//items recolectables
	//for (auto const& rec : recolectables) {
		//rec->update();//para activar la animacion
	//}


	
	//----------------------------------------------------
	//sumar puntos de items recolectable

	list<Recolectable*> deleteRecolectable;
	for (auto const& rec : recolectables) {
		//si llegó a un recolectable
		if (player->isOverlap(rec)) {

			bool pInList = std::find(deleteRecolectable.begin(),
				deleteRecolectable.end(),
				rec) != deleteRecolectable.end();

			if (!pInList) {
				deleteRecolectable.push_back(rec);
			}

			recolectablePoints++;
			textRecolectable ->content = to_string(recolectablePoints);
		}
	}

	



	//player con la puerta
	for (auto const& p1 : puertas) {
		for (auto const& p2 : puertas) {

			//si son el mismo par de puertas
			if (p1->tipo == p2->tipo) {
				//si colisionó con el jugador
				if (player->isOverlap(p1)) {
					//comprobar que no nos estamos cambiando a la misma puerta
					if (p1->x != p2->x or p1->y != p2->y) {

						//(ajustar la posicion para no aparecer delante de la otra puerta y hacer bucle infinito)
						//si estaba caminando hacia la izquierda (vx <0), aparecerá a la izquieda de la puerta
						if(player->vx <0)
							player->x = p2->x - 35;//aparecerá a la izquierda
						else if(player->vx > 0)
							player->x = p2->x + 35;//aparecerá a la derecha

						player->y = p2->y;
					}
				}
				
			}
		}
	}


	//borar recolectables
	for (auto const& rec : deleteRecolectable) {
		recolectables.remove(rec);
	}



	cout << "update GameLayer" << endl;
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;

		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}

	//limite arriba
	if (player->y - scrollY < HEIGHT * 0.3) {//condicion bien formada
		scrollY = player->y - HEIGHT * 0.3;
		
	}
	
	
	//limite abajo
	if (player->y - scrollY > HEIGHT * 0.7) {
		scrollY = player->y - HEIGHT * 0.7;
	}
	


}


void GameLayer::draw() {
	//calculateScroll();

	background->draw();
	//items recolectables
	for (auto const& rec : recolectables) {
		rec->draw(scrollX, scrollY);
	}


	for (auto const& puerta : puertas) {
		puerta->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);

	for (auto const& Gato : gatos) {
		Gato->draw(scrollX, scrollY);
	}


	//HUD-----------------------------
	backgroundPoints->draw();
	textPoints->draw();

	//contador de recolectables
	backgroundRecolectable->draw();
	textRecolectable->draw();



	SDL_RenderPresent(game->renderer); // Renderiza
}






void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}

