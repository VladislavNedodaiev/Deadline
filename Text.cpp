#include "Text.h"

Text::Text()
{

	this->_position = sf::Vector2f(0, 0);
	this->_size = sf::Vector2f(0, 0);

} // Text::Text()

Text::~Text()
{

	this->_strings.clear();

} // Text::~Text()

Text& Text::setPosition(const sf::Vector2f &position)
{

	this->_position = position;
	this->_box.setPosition(sf::Vector2f(sf::Vector2i(position)));

	if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
		this->_box.move((int)(-this->_size.x / 2), 0);
	else if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
		this->_box.move((int)(-this->_size.x), 0);

	if (this->_textinfo.verticalAlign == TextInfo::eVerticalAlign::Center)
		this->_box.move(0, (int)(-this->_size.y / 2));
	else if (this->_textinfo.verticalAlign == TextInfo::eVerticalAlign::Bottom)
		this->_box.move(0, (int)(-this->_size.y));

	return *this;

} // Text& Text::setPosition(const sf::Vector2f &position)

Text& Text::setPosition(float x, float y)
{

	return setPosition(sf::Vector2f(x, y));

} // Text& Text::setPosition(float x, float y)

Text& Text::move(const sf::Vector2f &offset)
{

	return setPosition(this->_position + offset);

} // Text& Text::move(const sf::Vector2f &offset)

Text& Text::move(float offsetX, float offsetY)
{

	return move(sf::Vector2f(offsetX, offsetY));

} // Text& Text::move(float offsetX, float offsetY)

Text& Text::setTextInfo(TextInfo &textinfo)
{

	if (this->_textinfo.font == nullptr && textinfo.font == nullptr)
		return *this;

	this->_textinfo = textinfo;

	this->_text.setFont(*this->_textinfo.font);
	this->_text.setCharacterSize(this->_textinfo.characterSize);
	const_cast<sf::Texture&>(this->_text.getFont()->getTexture(this->_textinfo.characterSize)).setSmooth(false);
	this->_text.setFillColor(this->_textinfo.textColor);

	int maxWidth = 0;
	int height = 0;
	int size = this->_strings.size();
	for (int i = 0; i < size; i++)
	{

		this->_text.setString(this->_strings[i]);
		int width = this->_text.getGlobalBounds().width + this->_text.getLocalBounds().left;
		if (width > maxWidth)
			maxWidth = width;
		height += this->_text.getGlobalBounds().height + this->_textinfo.lineSpacing + this->_text.getLocalBounds().top;

	} // for (int i = 0; i < size; i++)

	if (this->_textinfo.font != nullptr)
	{

		this->_size = sf::Vector2f(sf::Vector2i(maxWidth + this->_textinfo.margin.x * 2, height + this->_textinfo.margin.y * 2));
		this->_box.setSize(this->_size);
		this->_createTexture();

	} // if (this->_textinfo.font != nullptr)

	return *this;

} // Text& Text::setTextInfo(TextInfo &textinfo)

TextInfo& Text::getTextInfo()
{

	return this->_textinfo;

} // TextInfo Text::getTextInfo()

Text& Text::operator=(const sf::String &string)
{

	this->_strings.clear();

	int startPos = 0;
	int endPos = 0;

	int size = string.getSize();

	float maxWidth = 0;
	float height = 0;

	while (endPos < size)
	{

		if (string[endPos] == '\n')
		{

			this->_strings.push_back(string.substring(startPos, endPos - startPos));
			startPos = endPos + 1;

			if (this->_textinfo.font != nullptr)
			{

				this->_text.setString(this->_strings[this->_strings.size() - 1]);
				int width = this->_text.getGlobalBounds().width + this->_text.getLocalBounds().left;
				if (width > maxWidth)
					maxWidth = width;
				height += this->_text.getGlobalBounds().height + this->_textinfo.lineSpacing + this->_text.getLocalBounds().top;

			} // if (this->_textinfo.font != nullptr)

		} // if (string[endPos] == '\n')

		endPos++;

	} // while (endPos < size)

	if (endPos != startPos)
	{

		this->_strings.push_back(string.substring(startPos, endPos - startPos));

		if (this->_textinfo.font != nullptr)
		{

			this->_text.setString(this->_strings[this->_strings.size() - 1]);

			int width = _text.getGlobalBounds().width + this->_text.getLocalBounds().left;
			if (width > maxWidth)
				maxWidth = width;

			height += this->_text.getGlobalBounds().height + this->_textinfo.lineSpacing + this->_text.getLocalBounds().top;

		} // if (this->_textinfo.font != nullptr)

	} // if (endPos != startPos)

	if (this->_textinfo.font != nullptr)
	{

		this->_size = sf::Vector2f(sf::Vector2i(maxWidth + this->_textinfo.margin.x * 2, height + this->_textinfo.margin.y * 2));
		this->_box.setSize(this->_size);
		this->_createTexture();

	} // if (this->_textinfo.font != nullptr)

	return *this;

} // Text& Text::operator=(const sf::String &string)

Text& Text::setText(const sf::String &string)
{

	*this = string;
	return *this;

} // set text

Text& Text::setText(const sf::String &string, int charPerStroke)
{

	sf::String st = L"";
	
	for (int i = 0; i < string.getSize(); i++)
	{

		if (i % charPerStroke == 0 && i != 0)
			st += '\n';
		st += string[i];

	} // for

	*this = st;
	return *this;

} // set text

Text& Text::render(sf::RenderTarget &target)
{

	target.draw(this->_box);

	return *this;

} // Text& Text::render(sf::RenderTarget &target)

Text& Text::_createTexture()
{

	sf::Clock cl;
	sf::Time time;
	cl.restart();

	if (!this->_strings.size() || this->_textinfo.font == nullptr)
		return *this;

	this->setPosition(this->_position);

	// made for optimizing, cause sf::RenderTexture::create(...) requires lots of time
	sf::Vector2u rsize = this->_renderTexture.getSize();
	if (rsize.x != this->_size.x)
	{

		rsize.x = this->_size.x;

		if (rsize.y != this->_size.y)
			rsize.y = this->_size.y;

		this->_renderTexture.create(rsize.x, rsize.y);

	} // if (rsize.x < this->_size.x)

	else if (rsize.y != this->_size.y)
	{

		rsize.y = this->_size.y;

		if (rsize.x != this->_size.x)
			rsize.x = this->_size.x;

		this->_renderTexture.create(rsize.x, rsize.y);

	} // else if (rsize.y < this->_size.y)

	this->_renderTexture.clear(this->_textinfo.backgroundColor);

	this->_text.setString(this->_strings[0]);
	this->_text.setPosition(0, 0);
	this->_text.move(sf::Vector2f(sf::Vector2i(this->_textinfo.margin)));

	// horizontal align
	if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
		this->_text.setPosition(sf::Vector2f(sf::Vector2i(this->_size.x / 2 - this->_text.getGlobalBounds().width / 2, this->_text.getPosition().y + this->_textinfo.margin.y)));
	else if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
		this->_text.setPosition(sf::Vector2f(sf::Vector2i(this->_size.x - this->_textinfo.margin.x - this->_text.getGlobalBounds().width, this->_text.getPosition().y + this->_textinfo.margin.y)));

	this->_renderTexture.draw(this->_text);

	int size = this->_strings.size();
	for (int i = 1; i < size; i++)
	{

		this->_text.move(0, this->_text.getGlobalBounds().height + this->_textinfo.lineSpacing);
		this->_text.setString(this->_strings[i]);

		if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Middle)
			this->_text.setPosition(sf::Vector2f(sf::Vector2i(this->_size.x / 2 - this->_text.getGlobalBounds().width / 2, this->_text.getPosition().y + this->_textinfo.margin.y)));
		else if (this->_textinfo.horizontalAlign == TextInfo::eHorizontalAlign::Right)
			this->_text.setPosition(sf::Vector2f(sf::Vector2i(this->_size.x - this->_textinfo.margin.x - this->_text.getGlobalBounds().width, this->_text.getPosition().y + this->_textinfo.margin.y)));

		this->_renderTexture.draw(this->_text);

	} // for (int i = 1; i < size; i++)

	this->_renderTexture.display();
	this->_box.setTexture(&this->_renderTexture.getTexture(), true);

	return *this;

} // Text& Text::_createTexture()