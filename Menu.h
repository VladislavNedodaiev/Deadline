#pragma once

#include "State.h"

#include "CounterBar.h"
#include "Text.h"

class Menu : public State
{

private:

	SpriteSheet _backgroundSheet;
	SpriteSheet _buttonSheet;
	
	GameObject *_backgroundObject;
	GameObject *_playButton;
	GameObject *_exitButton;

protected:

	virtual Menu& initialize();

	virtual Menu& loadContent();
	virtual Menu& unloadContent();

public:


	Menu(GameHelper &gameHelper);
	virtual ~Menu();

	virtual Menu& input();

	virtual Menu& update(float dt);
	virtual Menu& render();

};