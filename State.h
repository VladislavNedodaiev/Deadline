#pragma once

#include "GameHelper.h"
#include "GameObject.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class State
{
protected:

	GameHelper * _gameHelper;

	virtual State& initialize() = 0;

	virtual State& loadContent() = 0;
	virtual State& unloadContent() = 0;

public:

	bool toDelete;

	State(GameHelper &gameHelper);
	virtual ~State();

	virtual State& input() = 0;

	virtual State& update(float dt) = 0;
	virtual State& render() = 0;

};