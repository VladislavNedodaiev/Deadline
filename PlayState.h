#pragma once

#include "State.h"

#include "Text.h"
#include "Button.h"
#include "CounterBar.h"

class Menu : public State
{

private:

	SpriteSheet _backgroundSheet;
	SpriteSheet _buttonSheet;
	SpriteSheet _panelSheet;

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

	virtual Menu& input();

	virtual Menu& update(float dt);
	virtual Menu& render();

};