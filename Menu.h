#pragma once

#include "PlayState.h"

class Menu : public State
{

private:

	SpriteSheet _backgroundSheet;
	SpriteSheet _buttonSheet;
	
	GameObject _backgroundObject;

	Button _playButton;
	Button _exitButton;

protected:

	virtual Menu& initialize();

	virtual Menu& loadContent();
	virtual Menu& unloadContent();

public:

	Menu(GameHelper &gameHelper);
	virtual ~Menu();

	virtual State& input();

	virtual Menu& update(float dt);
	virtual Menu& render();

};