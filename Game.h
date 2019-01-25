#pragma once

#include "GameStateManager.h"

class Game
{
protected:

	virtual Game& loadContent();
	virtual Game& unloadContent();

	virtual Game& initialize();

	virtual Game& input();

	virtual Game& update();
	virtual Game& render();

	float dt;

public:

	Game();
	virtual ~Game();

	virtual Game& play();
};