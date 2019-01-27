#pragma once

#include "State.h"

#include "CardObject.h"
#include "CounterBar.h"

class PlayState : public State
{

private:

	TextInfo _textinfo;
	Deck _deck;

	SpriteSheet _backgroundSheet;
	GameObject _backgroundObject;

	SpriteSheet _buttonSheet;
	SpriteSheet _panelSheet;
	CardObject *_cardObject;

	SpriteSheet _healthSheet;
	Text _healthText;

	SpriteSheet _joySheet;
	Text _joyText;

	SpriteSheet _moneySheet;
	Text _moneyText;

	PlayStateStats _stats;

	CounterBar _projectBar;
	Text _projectText;

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