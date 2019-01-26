#include "PlayState.h"

PlayState::PlayState(GameHelper &gameHelper) : State(gameHelper)
{

	this->loadContent().initialize();

} // constructor

PlayState::~PlayState()
{

	this->unloadContent();

} // destructor

PlayState& PlayState::initialize()
{

	this->_backgroundObject.setAnimation(this->_backgroundSheet.getSheet()).setSize(sf::Vector2f(1920, 1080));

	this->_cardObject = new CardObject(this->_panelSheet.getSheet(),
									   this->_buttonSheet.getSheet());
	this->_cardObject->setCard(this->_deck.getRandomCard());

	this->_textinfo.font = &this->_gameHelper->font;
	this->_textinfo.characterSize = 32;
	this->_textinfo.horizontalAlign = this->_textinfo.Middle;
	this->_textinfo.verticalAlign = this->_textinfo.Center;

	this->_stats.health = 75;
	this->_stats.joy = 75;
	this->_stats.money = 100;
	this->_stats.project = 0;

	return *this;

} // initializing

PlayState& PlayState::loadContent()
{

	this->_backgroundSheet.load("Data/background_sheet.png");
	this->_buttonSheet.load("Data/button_sheet.png");

	this->_deck.loadFromFile("Data/deck.dat");

	return *this;

} // loading

PlayState& PlayState::unloadContent()
{

	delete _cardObject;

	return *this;

} // unloading

State& PlayState::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_cardObject != nullptr)
	{

		int inp = this->_cardObject->input(this->_gameHelper->event, mousePos);
		if (inp)
		{

			Card *card = this->_cardObject->getCard();
			if (card != nullptr)
			{

				if (card->choices.size() > inp)
				{
					this->_stats += card->choices[inp]->stats;
					if (!(this->_stats.isAlive()))
					{

						this->toDelete = true;
						return *this;

					} // if
					else if (card->choices[inp]->nextCard != Choice::NO_NEXT_CARD)
					{

						if (card->choices[inp]->nextCard == Choice::RANDOM_NEXT_CARD)
							this->_cardObject->setCard(this->_deck.getRandomCard());
						else
							this->_cardObject->setCard(this->_deck.getCard(card->choices[inp]->nextCard));

					} // else if

				} // if

			} // if

		} // if

	} // if

	return *this;

} // input

PlayState& PlayState::update(float dt)
{

	this->_backgroundObject.update(dt);
	if (this->_cardObject != nullptr)
		this->_cardObject->update(dt);

	return *this;

} // updating

PlayState& PlayState::render()
{

	this->_backgroundObject.render(this->_gameHelper->renderWindow);
	if (this->_cardObject != nullptr)
		this->_cardObject->render(this->_gameHelper->renderWindow);

	return *this;

} // rendering