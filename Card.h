#pragma once

#include "Choice.h"
#include "SpriteSheet.h"

#include <vector>

struct Card
{

	std::vector <Choice*> choices;
	sf::String cardtext;
	SpriteSheet sheet;

	Card();
	~Card();

};