#pragma once

#include "PlayStateStats.h"

#include <SFML\Graphics.hpp>

struct Choice
{

	static const int RANDOM_NEXT_CARD = -2;
	static const int NO_NEXT_CARD = -1;
	int nextCard;

	sf::String text;
	PlayStateStats stats;

	Choice();

};