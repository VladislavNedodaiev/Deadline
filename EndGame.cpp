#include "EndGame.h"

EndGame::EndGame(GameHelper &gameHelper, sf::String &endText, sf::Color backgroundColor) : State(gameHelper)
{

	this->loadContent().initialize(endText, backgroundColor);

} // constructor

EndGame::~EndGame()
{

	this->unloadContent();

} // destructor

EndGame& EndGame::initialize()
{

	return *this;

} // endgame initialize

EndGame& EndGame::initialize(sf::String &endText, sf::Color backgroundColor)
{

	this->_backgroundObject.setSize(sf::Vector2f(BasicSettings::WINDOW_SIZEX, BasicSettings::WINDOW_SIZEY));
	this->_backgroundObject.setFillColor(backgroundColor);

	TextInfo textinfo;
	textinfo.font = &this->_gameHelper->font;
	textinfo.characterSize = 92;
	textinfo.horizontalAlign = textinfo.Middle;
	textinfo.verticalAlign = textinfo.Center;

	this->_endText.setText(endText, 30);
	this->_endText.setTextInfo(textinfo);
	this->_endText.setPosition(BasicSettings::WINDOW_SIZEX / 2, BasicSettings::WINDOW_SIZEY / 2);

	return *this;

} // initializing

EndGame& EndGame::loadContent()
{

	return *this;

} // loading

EndGame& EndGame::unloadContent()
{

	return *this;

} // unloading

State& EndGame::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_gameHelper->event.type == sf::Event::KeyPressed || this->_gameHelper->event.type == sf::Event::MouseButtonPressed)
		this->toDelete = true;

	return *this;

} // input

EndGame& EndGame::update(float dt)
{

	return *this;

} // updating

EndGame& EndGame::render()
{

	this->_gameHelper->renderWindow.draw(this->_backgroundObject);

	this->_endText.render(this->_gameHelper->renderWindow);

	return *this;

} // rendering