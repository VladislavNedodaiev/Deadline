#include "Deck.h"

const int Deck::DEFAULT_MEMORY_LAST;

Deck::Deck()
{

	std::srand(std::time(0));

	this->memory_last = 5;

} // default constructor

Deck::~Deck()
{
	
	this->clear();

} // destructor

Deck& Deck::loadFromFile(std::string path)
{

	// TODO load from file

} // load from file

Deck& Deck::clear()
{

	for (int i = 0; i < this->_cards.size(); i++)
		delete this->_cards[i];

	this->_cards.clear();

} // clear deck

Card* Deck::addCard(Card *card)
{

	if (card != nullptr && !this->isInDeck(card))
		this->_cards.push_back(card);

	return card;

} // add card

Card* Deck::getCard(int position)
{

	if (position < this->_cards.size() && position >= 0)
		return this->_cards[position];

	return nullptr;

} // getting card on pos

bool Deck::isInDeck(Card *card)
{

	if (card == nullptr)
		return false;

	for (int i = 0; i < this->_cards.size(); i++)
	{
		
		if (this->_cards[i] == card)
			return true;

	} // for

	return false;

} // check if the card is in the deck

Card* Deck::getRandomCard()
{

	int size = this->_cards.size();
	int lastsize = this->_last.size();

	if (size == 0 || size <= lastsize)
		return nullptr;

	std::vector <Card*> rndcards;
	for (int i = 0; i < size; i++)
	{

		bool islast = false;

		for (int k = 0; k < lastsize; k++)
		{

			if (this->_cards[i] == this->_last[k])
			{

				islast = true;
				break;

			} // if

		} // for

		if (!islast)
			rndcards.push_back(this->_cards[i]);

	} // for

	return rndcards[std::rand() % rndcards.size()];

} // getting random card