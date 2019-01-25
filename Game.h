#pragma once

#include "GameStateManager.h"

class Game
{
protected:

	GameHelper _gamehelper;
	GameStateManager _gsm;
	float dt;

	virtual Game& loadContent();
	virtual Game& unloadContent();

	virtual Game& initialize();

	virtual Game& input();

	virtual Game& update();
	virtual Game& render();

public:

	Game();
	virtual ~Game();

	virtual Game& play();
};