#pragma once

#include "BasicSettings.h"
#include "Deck.h"

class GameHelper
{
private:

	sf::View _view;

public:

	bool isPlaying;

	sf::Font font;
	sf::RenderWindow renderWindow;
	sf::Event event;
	BasicSettings settings;

	GameHelper();
	~GameHelper();

	GameHelper& resetWindow();
	GameHelper& setLetterboxView();

};