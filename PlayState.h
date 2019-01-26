#pragma once

#include "State.h"

#include "CardObject.h"

class PlayState : public State
{

private:

	SpriteSheet _backgroundSheet;
	SpriteSheet _buttonSheet;
	SpriteSheet _panelSheet;

	GameObject _backgroundObject;

	Deck _deck;
	TextInfo _textinfo;

	CardObject *_cardObject;

	PlayStateStats _stats;

protected:

	virtual PlayState& initialize();

	virtual PlayState& loadContent();
	virtual PlayState& unloadContent();

public:


	PlayState(GameHelper &gameHelper);
	virtual ~PlayState();

	virtual State& input();

	virtual PlayState& update(float dt);
	virtual PlayState& render();

};