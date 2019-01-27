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

	this->_playButton.setAnimation(this->_buttonSheet.getSheet()).setSize(sf::Vector2f(500, 150));
	this->_playButton.text.setTextInfo(textinfo);
	this->_playButton.text = L"Play game";
	this->_playButton.setFillColor(sf::Color::White);
	this->_playButton.setPosition(sf::Vector2f(this->_gameHelper->settings.WINDOW_SIZEX / 2 - this->_playButton.getSize().x / 2, this->_gameHelper->settings.WINDOW_SIZEY / 5));

	this->_exitButton.setAnimation(this->_buttonSheet.getSheet()).setSize(sf::Vector2f(500, 150));
	this->_exitButton.text.setTextInfo(textinfo);
	this->_exitButton.text = L"Exit game";
	this->_exitButton.setFillColor(sf::Color::White);
	this->_exitButton.setPosition(sf::Vector2f(this->_gameHelper->settings.WINDOW_SIZEX / 2 - this->_exitButton.getSize().x / 2, this->_gameHelper->settings.WINDOW_SIZEY / 5 * 2));

	this->_music.setLoop(true);
	this->_music.play();

	return *this;

} // initializing

Menu& Menu::loadContent()
{

	this->_backgroundSheet.load("Data/background_menu_sheet.png");
	this->_buttonSheet.load("Data/button_sheet.png");

	this->_music.openFromFile("Data/menu.ogg");
	this->_music.stop();
	
	return *this;

} // loading

Menu& Menu::unloadContent()
{

	this->_music.stop();

	return *this;

} // unloading

State& Menu::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_playButton.isPressed(this->_gameHelper->event, mousePos))
	{

		PlayState *playstate = new PlayState(*this->_gameHelper);
		this->_music.stop();
		return *playstate;

	} // if play pressed
	else if (this->_exitButton.isPressed(this->_gameHelper->event, mousePos))
		this->_gameHelper->isPlaying = false;

	return *this;

} // input

Menu& Menu::update(float dt)
{

	if (this->_music.getStatus() != this->_music.Playing)
		this->_music.play();

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