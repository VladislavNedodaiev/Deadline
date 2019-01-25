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

	// TODO

	return *this;

} // initializing

Menu& Menu::loadContent()
{

	// TODO

	return *this;

} // loading

Menu& Menu::unloadContent()
{

	// TODO

	return *this;

} // unloading

Menu& Menu::input()
{

	// TODO

	return *this;

} // input

Menu& Menu::update(float dt)
{

	// TODO

	return *this;

} // updating

Menu& Menu::render()
{

	// TODO

	return *this;

} // rendering