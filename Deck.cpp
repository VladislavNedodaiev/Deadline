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


	std::wifstream wifs(path);

	if (!wifs.is_open())
		return *this;

	std::wstring buf = L"";

	int count = 0;
	std::getline(wifs, buf);
	count = std::stoi(buf);

	for (int i = 0; i < count && !wifs.eof(); i++)
	{

		Card *card = new Card;
		
		// card text
		std::getline(wifs, buf);
		card->cardtext = buf;

		// card image
		std::getline(wifs, buf);
		card->sheet.load(sf::String(buf).toAnsiString());

		// choices count
		int choice_count = 0;
		std::getline(wifs, buf);
		choice_count = std::stoi(buf);
		for (int k = 0; k < choice_count && !wifs.eof(); k++)
		{

			Choice *choice = new Choice;
			std::getline(wifs, buf);
			choice->text = buf;

			// health
			std::getline(wifs, buf);
			choice->stats.health = stoi(buf);

			// joy
			std::getline(wifs, buf);
			choice->stats.joy = stoi(buf);

			// money
			std::getline(wifs, buf);
			choice->stats.money = stoi(buf);

			// project
			std::getline(wifs, buf);
			choice->stats.project = stoi(buf);

			// next card
			std::getline(wifs, buf);
			choice->nextCard = stoi(buf);

			card->choices.push_back(choice);

		} // for

		this->_cards.push_back(card);

	} // for

	return *this;

} // load from file

Deck& Deck::clear()
{

	for (int i = 0; i < this->_cards.size(); i++)
		delete this->_cards[i];

	this->_cards.clear();

	return *this;

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

	Card *card = rndcards[std::rand() % rndcards.size()];

	if (lastsize > this->DEFAULT_MEMORY_LAST)
		this->_last.pop_back();
	this->_last.insert(this->_last.begin(), card);

	return card;

} // getting random card