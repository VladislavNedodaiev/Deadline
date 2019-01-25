#pragma once

#include <SFML\Graphics.hpp>

struct BasicSettings
{

	static const int WINDOW_SIZEX = 1920;
	static const int WINDOW_SIZEY = 1080;

	bool fullscreen;

	BasicSettings();

	sf::VideoMode getVideoMode();
	sf::String getWindowName();
	sf::ContextSettings getContextSettings();
	sf::Uint32 getWindowStyle();

};