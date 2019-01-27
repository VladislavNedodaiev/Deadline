#include "CounterBar.h"

CounterBar::CounterBar(sf::Vector2f size, sf::Color fillColor, float initialRate, sf::Color backColor = sf::Color::Transparent) : 
	_bar(sf::Quads, 4),
	_backbar(sf::Quads, 4)
{

	_initialSize = size;

	_bar[0].position = sf::Vector2f(0, 0);
	_bar[1].position = sf::Vector2f(size.x, 0);
	_bar[2].position = sf::Vector2f(size.x, size.y);
	_bar[3].position = sf::Vector2f(0, size.y);
	for (int i = 0; i < 4; i++)
		_bar[i].color = fillColor;

	_backbar[0].position = sf::Vector2f(0, 0);
	_backbar[1].position = sf::Vector2f(size.x, 0);
	_backbar[2].position = sf::Vector2f(size.x, size.y);
	_backbar[3].position = sf::Vector2f(0, size.y);
	for (int i = 0; i < 4; i++)
		_backbar[i].color = backColor;

	setRate(initialRate);

} // constructor

CounterBar::~CounterBar() {} // destructor

CounterBar& CounterBar::setPosition(const sf::Vector2f &position)
{

	return move(position - _bar[0].position);

} // setting position

CounterBar& CounterBar::setPosition(float x, float y)
{

	return setPosition(sf::Vector2f(x, y));

} // setting position

CounterBar& CounterBar::move(const sf::Vector2f &offset)
{

	for (int i = 0; i < 4; i++)
	{

		_bar[i].position += offset;
		_backbar[i].position += offset;

	} // for

	return *this;

} // moving

CounterBar& CounterBar::move(float offsetX, float offsetY)
{

	return move(sf::Vector2f(offsetX, offsetY));

} // moving

CounterBar& CounterBar::setSize(sf::Vector2f size)
{

	_initialSize = size;

	_backbar[1].position.x = _backbar[0].position.x + _initialSize.x;
	_backbar[2].position.x = _backbar[3].position.x + _initialSize.x;

	return setRate(_rate);

} // setting new MAX size

sf::Vector2f CounterBar::getSize()
{

	return _initialSize;

} // returning MAX size

CounterBar& CounterBar::increase(float rate)
{

	setRate(_rate + rate);

	return *this;

} // increasing/decreasing

CounterBar& CounterBar::setRate(float rate)
{

	_rate = rate;

	if (_rate < 0)
		return setEmpty();
	else if (_rate > 1)
		return setFull();

	_bar[1].position.x = _bar[0].position.x + rate * _initialSize.x;
	_bar[2].position.x = _bar[3].position.x + rate * _initialSize.x;

	return *this;

} // setting the rate

CounterBar& CounterBar::setFull()
{

	_rate = 1;
	_bar[1].position.x = _bar[0].position.x + _initialSize.x;
	_bar[2].position.x = _bar[3].position.x + _initialSize.x;

	return *this;

} // setting FULL rate (max size)

CounterBar& CounterBar::setEmpty()
{

	_rate = 0;
	_bar[1].position.x = _bar[0].position.x;
	_bar[2].position.x = _bar[3].position.x;

	return *this;

} // setting empty 

float CounterBar::getRate()
{

	return _rate;

} // getting rate

CounterBar& CounterBar::setFillColor(sf::Color fillColor)
{

	for (int i = 0; i < _bar.getVertexCount(); i++)
		_bar[i].color = fillColor;

	return *this;

} // setting fillcolor

CounterBar& CounterBar::setBackColor(sf::Color backColor)
{

	for (int i = 0; i < _bar.getVertexCount(); i++)
		_backbar[i].color = backColor;

	return *this;

} // setting fillcolor

CounterBar& CounterBar::render(sf::RenderTarget &target)
{

	target.draw(_backbar);
	target.draw(_bar);

	return *this;

} // render