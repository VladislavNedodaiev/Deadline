#pragma once

#include <SFML\Graphics.hpp>

#include "Animation.h"

class GameObject : public sf::RectangleShape
{
protected:

	sf::Texture _texture;

	Animation *_currentAnimation;

public:

	enum eInputType
	{
		None = 0
	};

	bool isVisible;
	bool isMovable;

	GameObject();
	GameObject(sf::Image &imageSheet);
	GameObject(sf::Image &imageSheet, float fps, sf::IntRect firstFrame);
	GameObject(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame);
	virtual ~GameObject();

	virtual GameObject& setAnimation(sf::Image &imageSheet);
	virtual GameObject& setAnimation(sf::Image &imageSheet, float fps, sf::IntRect firstFrame);
	virtual GameObject& setAnimation(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame);

	virtual GameObject& unsetAnimation();

	virtual GameObject& setFrame(int frame);

	virtual bool pointIsOver(sf::Vector2i &point) const;
	virtual bool isPressed(sf::Event &event, sf::Vector2i &point) const;

	virtual GameObject& move(const sf::Vector2f &offset);
	virtual GameObject& move(float offsetX, float offsetY);

	virtual GameObject& setSize(const sf::Vector2f &size);

	virtual int input(sf::Event &event, sf::Vector2i mousePos);
	virtual GameObject& update(float dt);
	virtual GameObject& render(sf::RenderTarget &target);

};