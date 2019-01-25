#pragma once

#include "State.h"

class Menu : public State
{
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