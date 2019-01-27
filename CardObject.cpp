#include "CardObject.h"

CardObject::CardObject(sf::Image &panelSheet,
					   sf::Image &buttonSheet) : GameObject(panelSheet)
{

	this->_panelSheet = &panelSheet;
	this->_buttonSheet = &buttonSheet;

	GameObject::setPosition(BasicSettings::WINDOW_SIZEX / 2 - this->getSize().x / 2,
							BasicSettings::WINDOW_SIZEY / 2 - this->getSize().y / 2);

} // default constructor

CardObject::~CardObject()
{

	this->clear();

} // destructor

CardObject& CardObject::clear()
{

	this->_card = nullptr;

	for (int i = 0; i < this->buttons.size(); i++)
		delete this->buttons[i];

	this->buttons.clear();

	delete this->eventText;
	this->eventText = nullptr;
	
	delete this->imageObject;
	this->imageObject = nullptr;

	return *this;

} // clear

CardObject& CardObject::setCard(Card *card)
{

	this->clear();

	if (card == nullptr)
		return *this;

	this->_card = card;

	int size = card->choices.size();

	for (int i = 0; i < size; i++)
	{

		Button *button = new Button(*this->_buttonSheet);
		button->text.setText(card->choices[i]->text, 25);
		button->setSize(sf::Vector2f(this->getGlobalBounds().width / size - 100, 150));
		button->setPosition(this->getGlobalBounds().left + this->getGlobalBounds().width / size * i + this->getGlobalBounds().width / size / 2.0 - button->getGlobalBounds().width / 2.0,
							BasicSettings::WINDOW_SIZEY / 2.0 - button->getGlobalBounds().height / 2 + this->getSize().y / 4);
		button->text.setTextInfo(this->textinfo);

		this->buttons.push_back(button);

	} // for

	this->eventText = new Text;
	this->eventText->setText(card->cardtext, 70);
	this->eventText->setPosition(BasicSettings::WINDOW_SIZEX / 2.0,
								BasicSettings::WINDOW_SIZEY / 2.0 + this->getSize().y / 9);
	this->eventText->setTextInfo(this->textinfo);

	this->imageObject = new GameObject(card->sheet.getSheet());
	this->imageObject->setScale(0.6, 0.6);
	this->imageObject->setPosition(BasicSettings::WINDOW_SIZEX / 2.0 - this->imageObject->getGlobalBounds().width / 2.0,
								  BasicSettings::WINDOW_SIZEY / 2.0 - this->getSize().y / 3);

	return *this;

} // set from card

Card* CardObject::getCard()
{

	return this->_card;

} // get card

CardObject& CardObject::move(const sf::Vector2f &offset)
{

	GameObject::move(offset);

	this->imageObject->move(offset);

	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i]->move(offset);

	this->eventText->move(offset);

	return *this;

} // moving 

CardObject& CardObject::move(float offsetX, float offsetY)
{

	return this->move(sf::Vector2f(offsetX, offsetY));

} // moving

CardObject& CardObject::setPosition(const sf::Vector2f &position)
{
	
	return this->move(position - this->getPosition());

} // setting position

CardObject& CardObject::setPosition(float x, float y)
{

	return this->move(sf::Vector2f(x - this->getPosition().x, y - this->getPosition().y));

} // setting position

int CardObject::input(sf::Event &event, sf::Vector2i mousePos)
{

	GameObject::input(event, mousePos);

	int size = this->buttons.size();

	if (size < 2)
	{

		if (event.type == sf::Event::KeyPressed)
			return 1;

	} // any key
	else if (size == 2)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return 2;

	} // two

	for (int i = 0; i < size; i++)
	{

		if (this->buttons[i]->isPressed(event, mousePos))
			return i + 1;

	} // for

	return GameObject::None;

} // input

CardObject& CardObject::update(float dt)
{

	GameObject::update(dt);

	this->imageObject->update(dt);

	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i]->update(dt);

	return *this;

} // updating

CardObject& CardObject::render(sf::RenderTarget &target)
{

	GameObject::render(target);

	this->imageObject->render(target);
	
	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i]->render(target);

	this->eventText->render(target);

	return *this;

} // rendering