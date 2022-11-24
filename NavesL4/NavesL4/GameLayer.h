#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Gato.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "TemporalTile.h"
#include "PuntoSalvado.h"
#include "Recolectable.h"
#include "Puerta.h"


#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;
	

	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	float scrollY;//ampliacion

	int mapWidth;
	list<Tile*> tiles;
	list<TemporalTile*> temporalTiles;
	PuntoSalvado* salvado;


	Audio* audioBackground;
	Text* textPoints;
	int points;
	int newGatoTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	list<Gato*> gatos;
	list<Projectile*> projectiles;

	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	//punto de salvado	//ampliacion
	int initialX = 0;
	int initialY = 0;

	//items recolectables	//ampliacion
	list<Recolectable*> recolectables;
	Text* textRecolectable;
	Actor* backgroundRecolectable;
	int recolectablePoints = 0;


	//puertas	//ampliacion
	list<Puerta*> puertas;

};

