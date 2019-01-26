#include "GameObject.h"

GameObject::GameObject() : RectangleShape()
{

	_texture.create(0, 0);
	this->setTexture(&_texture);

	_currentAnimation = nullptr;

	isVisible = true;
	isMovable = true;

} // default constructor

GameObject::GameObject(sf::Image &imageSheet) : RectangleShape(sf::Vector2f(imageSheet.getSize()))
{

	this->setAnimation(imageSheet);

	isVisible = true;
	isMovable = true;

} // constructor

GameObject::GameObject(sf::Image &imageSheet, float fps, sf::IntRect firstFrame) :
	RectangleShape(sf::Vector2f(firstFrame.width, firstFrame.height))
{

	this->setAnimation(imageSheet, fps, firstFrame);

	isVisible = true;
	isMovable = true;

} // creates the gameobject with the animation

GameObject::GameObject(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame) :
	RectangleShape(sf::Vector2f(firstFrame.width, firstFrame.height))
{

	this->setAnimation(imageSheet, frames, fps, firstFrame);

	isVisible = true;
	isMovable = true;

} // create with animation

GameObject::~GameObject()
{

	if (_currentAnimation != nullptr)
		delete _currentAnimation;

} // destructor

GameObject& GameObject::setAnimation(sf::Image &imageSheet)
{

	_texture.create(imageSheet.getSize().x, imageSheet.getSize().y);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(imageSheet.getSize())),
		1,
		0,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	return *this;

} // set animation

GameObject& GameObject::setAnimation(sf::Image &imageSheet, float fps, sf::IntRect firstFrame)
{

	_texture.create(firstFrame.width, firstFrame.height);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(firstFrame,
		fps,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	return *this;

} // set animation

GameObject& GameObject::setAnimation(sf::Image &imageSheet, int frames, float fps, sf::IntRect firstFrame)
{

	_texture.create(firstFrame.width, firstFrame.height);
	this->setTexture(&_texture);

	_currentAnimation = new Animation(firstFrame,
		frames,
		fps,
		imageSheet,
		_texture);

	_currentAnimation->updateTexture();

	return *this;

} // set animation

GameObject& GameObject::unsetAnimation()
{

	if (_currentAnimation != nullptr)
		delete _currentAnimation;

	_texture.create(this->getSize().x, this->getSize().y);
	this->setTexture(&_texture);

	return *this;

} // unset animation

GameObject& GameObject::setFrame(int frame)
{

	if (this->_currentAnimation != nullptr)
		this->_currentAnimation->setFrame(frame).updateTexture();

	return *this;

} // setting the frame for animation

bool GameObject::pointIsOver(sf::Vector2i &point) const
{

	if (this->getGlobalBounds().contains(sf::Vector2f(point)))
		return true;

	return false;

} // checking if mouse is over the button

bool GameObject::isPressed(sf::Event &event, sf::Vector2i &point) const
{

	if (pointIsOver(point) &&
		event.type == sf::Event::MouseButtonPressed)
		return true;

	return false;

} // checking if the button is pressed

GameObject& GameObject::move(const sf::Vector2f &offset)
{

	if (isMovable)
		RectangleShape::move(offset);

	return *this;

} // recshape move overload #1

GameObject& GameObject::move(float offsetX, float offsetY)
{

	if (isMovable)
		RectangleShape::move(offsetX, offsetY);

	return *this;

} // recshape move overload #2

int GameObject::input(sf::Event &event, sf::Vector2i mousePos)
{

	return None;

} // reading input

GameObject& GameObject::update(float dt)
{

	if (_currentAnimation != nullptr)
		_currentAnimation->update(dt);

	return *this;

} // update(dt)

GameObject& GameObject::render(sf::RenderTarget &target)
{

	if (isVisible)
		target.draw(*this);

	return *this;

} // render