#pragma once

#include "State.h"

#include "Text.h"

class EndGame : public State
{

private:

	sf::RectangleShape _backgroundObject;

	Text _endText;

	sf::Music _music;

protected:

	virtual EndGame& initialize();
	virtual EndGame& initialize(sf::String &endText, sf::Color backgroundColor);

	virtual EndGame& loadContent();
	virtual EndGame& loadContent(sf::String &music);
	virtual EndGame& unloadContent();

public:

	EndGame(GameHelper &gameHelper, sf::String &endText, sf::Color backgroundColor, sf::String &music);
	virtual ~EndGame();

	virtual State& input();

	virtual EndGame& update(float dt);
	virtual EndGame& render();

};