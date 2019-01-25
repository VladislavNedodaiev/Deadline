#include "Game.h"

Game::Game() : _gsm(_gamehelper)
{

	this->loadContent().initialize();

} // constructor

Game::~Game()
{

	this->unloadContent();

} // destructor

Game& Game::loadContent()
{

	return *this;

} // loading needed resources (textures, sounds, music etc)

Game& Game::unloadContent()
{

	return *this;

} // unloading resources

Game& Game::initialize()
{

	return *this;

} // initialize (comes after loadContent)

Game& Game::input()
{

	while (this->_gamehelper.renderWindow.pollEvent(this->_gamehelper.event))
	{

		if (_gamehelper.event.type == sf::Event::Closed)
		{

			this->_gamehelper.renderWindow.close();
			this->_gamehelper.isPlaying = false;

		} // if

		else if (_gamehelper.event.type == sf::Event::Resized)
			this->_gamehelper.setLetterboxView();
		this->_gsm.input();

	} // while

	return *this;

} // update input

Game& Game::update()
{

	this->_gsm.update(dt);
	if (this->_gsm.getStatesCount() == 0)
		this->_gamehelper.isPlaying = false;

	return *this;

} // updating the game

Game& Game::render()
{

	this->_gamehelper.renderWindow.clear();
	this->_gsm.render();
	this->_gamehelper.renderWindow.display();

	return *this;

} // rendering

Game& Game::play()
{

	sf::Clock dtClock;
	while (this->_gamehelper.isPlaying)
	{

		this->dt = dtClock.restart().asSeconds();
		this->update().render().input();

	} // while

	return *this;

} // main game loop