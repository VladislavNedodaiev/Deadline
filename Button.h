#pragma once

#include "GameObject.h"
#include "Text.h"

class Button : public GameObject
{

	Button& _textcenter();

public:

	Text text;

	Button();
	Button(sf::Image &imageSheet);
	Button(sf::Image &imageSheet, float fps, sf::IntRect firstFrame);
	Button(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame);

	Button& setAnimation(sf::Image &imageSheet);
	Button& setAnimation(sf::Image &imageSheet, float fps, sf::IntRect firstFrame);
	Button& setAnimation(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame);

	// moves the gameobject
	Button& move(const sf::Vector2f &offset);

	// moves the gameobject
	Button& move(float offsetX, float offsetY);

	// moves the gameobject
	Button& setSize(const sf::Vector2f size);

	// set position of button (with text)
	Button& setPosition(const sf::Vector2f position);

	// set position of button (with text)
	Button& setPosition(float x, float y);

	// render
	Button& render(sf::RenderTarget &target);

};
