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

	this->_backgroundObject = new GameObject(this->_backgroundSheet.getSheet());
	this->_playButton = new GameObject(this->_buttonSheet.getSheet());
	this->_exitButton = new GameObject(this->_buttonSheet.getSheet());

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

	delete this->_backgroundObject;
	delete this->_playButton;
	delete this->_exitButton;

	return *this;

} // unloading

Menu& Menu::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_playButton->isPressed(this->_gameHelper->event, mousePos))
	{

		// TODO: START GAME

	} // if play pressed
	else if (this->_exitButton->isPressed(this->_gameHelper->event, mousePos))
		this->_gameHelper->isPlaying = false;

	return *this;

} // input

Menu& Menu::update(float dt)
{

	this->_backgroundObject->update(dt);
	this->_playButton->update(dt);
	this->_exitButton->update(dt);

	return *this;

} // updating

Menu& Menu::render()
{

	this->_backgroundObject->render(this->_gameHelper->renderWindow);
	this->_playButton->render(this->_gameHelper->renderWindow);
	this->_exitButton->render(this->_gameHelper->renderWindow);

	return *this;

} // rendering