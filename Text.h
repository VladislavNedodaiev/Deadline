#pragma once

#include <vector>
#include "TextInfo.h"

#include <iostream>

class Text
{

protected:

	sf::Texture _texture;
	sf::RenderTexture _renderTexture;
	sf::RectangleShape _box;

	sf::Text _text;
	std::vector <sf::String> _strings;
	TextInfo _textinfo;

	// creating texture
	Text& _createTexture();

	sf::Vector2f _size;
	sf::Vector2f _position;

public:

	// default constructor
	Text();

	// destructor
	virtual ~Text();

	// setting the position
	virtual Text& setPosition(const sf::Vector2f &position);

	// setting the position
	virtual Text& setPosition(float x, float y);

	// moving relatively
	virtual Text& move(const sf::Vector2f &offset);

	// moving relatively
	virtual Text& move(float offsetX, float offsetY);

	// setting TextInfo (which determines the style of the text)
	Text& setTextInfo(TextInfo &textinfo);

	// getting textinfo
	TextInfo& getTextInfo();

	// setting text (= operator overload)
	Text& operator=(const sf::String &string);

	Text& setText(const sf::String &string);
	Text& setText(const sf::String &string, int charPerStroke);

	// render
	Text& render(sf::RenderTarget &target);

};