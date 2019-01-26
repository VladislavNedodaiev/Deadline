#pragma once

#include "Button.h"
#include "Text.h"
#include "Card.h"
#include "BasicSettings.h"

class CardObject : public GameObject
{

	Card *_card;
	
	sf::Image *_panelSheet;
	sf::Image *_buttonSheet;

public:

	GameObject imageObject;
	std::vector <Button*> buttons;
	TextInfo textinfo;
	Text eventText;

	CardObject(sf::Image &panelSheet,
			   sf::Image &buttonSheet);
	~CardObject();

	virtual CardObject& clear();

	virtual CardObject& setCard(Card *card);
	virtual Card* getCard();

	virtual CardObject& move(const sf::Vector2f &offset);
	virtual CardObject& move(float offsetX, float offsetY);

	virtual CardObject& setPosition(const sf::Vector2f &position);
	virtual CardObject& setPosition(float x, float y);

	// returns 0 if no input, 1-... for choice made
	virtual int input(sf::Event &event, sf::Vector2i mousePos);
	virtual CardObject& update(float dt);
	virtual CardObject& render(sf::RenderTarget &target);

};