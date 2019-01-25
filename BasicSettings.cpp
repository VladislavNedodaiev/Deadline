#include "BasicSettings.h"

BasicSettings::BasicSettings()
{

	this->fullscreen = true;

} // Settings constructor

sf::VideoMode BasicSettings::getVideoMode()
{

	if (fullscreen)
		return sf::VideoMode::getFullscreenModes()[0];

	return sf::VideoMode::getDesktopMode();

} // get videomode

sf::String BasicSettings::getWindowName()
{

	return sf::String("Deadline");

} // get window name

sf::ContextSettings BasicSettings::getContextSettings()
{

	return sf::ContextSettings();

} // get window context settings

sf::Uint32 BasicSettings::getWindowStyle()
{

	if (fullscreen)
		return sf::Style::Fullscreen;

	return sf::Style::Default;

} // get window style