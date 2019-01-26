#include "Menu.h"

Menu::Menu(GameHelper &gameHelper) : State(gameHelper)
{

	this->loadContent().initialize();

} // constructor

Menu::~Menu()
{

	this->unloadContent();

} // destructor

Menu& Menu::initialize()
{

	this->_backgroundObject.setAnimation(this->_backgroundSheet.getSheet()).setSize(sf::Vector2f(1920, 1080));

	TextInfo textinfo;
	textinfo.font = &this->_gameHelper->font;
	textinfo.characterSize = 32;
	textinfo.horizontalAlign = textinfo.Middle;
	textinfo.verticalAlign = textinfo.Center;
	textinfo.backgroundColor = sf::Color::Green;

	this->_playButton.setAnimation(this->_buttonSheet.getSheet()).setSize(sf::Vector2f(400, 100));
	this->_playButton.text.setTextInfo(textinfo);
	this->_playButton.text = L"Play game";
	this->_playButton.setFillColor(sf::Color::Yellow);

	this->_exitButton.setAnimation(this->_buttonSheet.getSheet()).setSize(sf::Vector2f(400, 100));
	this->_exitButton.text.setTextInfo(textinfo);
	this->_exitButton.text = L"Exit game";
	this->_exitButton.setFillColor(sf::Color::Red);

	return *this;

} // initializing

Menu& Menu::loadContent()
{

	this->_backgroundSheet.load("data/background_sheet.png");
	this->_buttonSheet.load("data/button_sheet.png");

	return *this;

} // loading

Menu& Menu::unloadContent()
{

	return *this;

} // unloading

Menu& Menu::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_playButton.isPressed(this->_gameHelper->event, mousePos))
	{

		// TODO: START GAME

	} // if play pressed
	else if (this->_exitButton.isPressed(this->_gameHelper->event, mousePos))
		this->_gameHelper->isPlaying = false;

	return *this;

} // input

Menu& Menu::update(float dt)
{

	this->_backgroundObject.update(dt);
	this->_playButton.update(dt);
	this->_exitButton.update(dt);

	return *this;

} // updating

Menu& Menu::render()
{

	this->_backgroundObject.render(this->_gameHelper->renderWindow);
	this->_playButton.render(this->_gameHelper->renderWindow);
	this->_exitButton.render(this->_gameHelper->renderWindow);

	return *this;

} // rendering