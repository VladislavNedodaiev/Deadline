#include "Button.h"

Button::Button() :
	GameObject()
{

	this->_textcenter();

} // default constructor

Button::Button(sf::Image &imageSheet) :
	GameObject(imageSheet)
{

	this->_textcenter();

} // constructor

Button::Button(sf::Image &imageSheet, float fps, sf::IntRect firstFrame) :
	GameObject(imageSheet, fps, firstFrame)
{

	this->_textcenter();

} // constructor

Button::Button(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame) :
	GameObject(imageSheet, frames, fps, firstFrame)
{

	this->_textcenter();

} // constructor

Button& Button::setAnimation(sf::Image &imageSheet)
{

	GameObject::setAnimation(imageSheet);
	this->_textcenter();

} // set animation

Button& Button::setAnimation(sf::Image &imageSheet, float fps, sf::IntRect firstFrame)
{

	GameObject::setAnimation(imageSheet, fps, firstFrame);
	this->_textcenter();

} // set animation

Button& Button::setAnimation(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame)
{

	GameObject::setAnimation(imageSheet, frames, fps, firstFrame);
	this->_textcenter();

} // set animation

Button& Button::move(const sf::Vector2f &offset)
{

	GameObject::move(offset);

	this->_textcenter();

	return *this;

} // Button& Button::move(const sf::Vector2f &offset)

Button& Button::move(float offsetX, float offsetY)
{

	GameObject::move(offsetX, offsetY);

	this->_textcenter();

	return *this;

} // Button& Button::move(const float offsetX, const float offsetY)

Button& Button::setSize(const sf::Vector2f size)
{

	GameObject::setSize(size);

	this->_textcenter();

	return *this;

} // Button& Button::setSize(const sf::Vector2f size)

Button& Button::setPosition(const sf::Vector2f position)
{

	GameObject::setPosition(position);

	this->_textcenter();

	return *this;

} // Button& Button::setPosition(const sf::Vector2f position)

Button& Button::setPosition(float x, float y)
{

	GameObject::setPosition(x, y);

	this->_textcenter();

	return *this;

} // Button& Button::setPosition(float x, float y)

Button& Button::render(sf::RenderTarget &target)
{

	GameObject::render(target);

	text.render(target);

	return *this;

} // Button& Button::render(sf::RenderTarget &target)

Button& Button::_textcenter()
{

	this->text.setPosition(this->getPosition().x + this->getSize().x / 2,
		this->getPosition().y + this->getSize().y / 2);

} // text to center