#pragma once

#include "Card.h"

#include <cwchar>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Deck
{

private:

	std::vector <Card*> _cards;
	std::vector <Card*> _last;

public:

	static const int DEFAULT_MEMORY_LAST = 5;

	int memory_last;

	Deck();
	~Deck();

	Deck& loadFromFile(std::string path);
	Deck& clear();

	Card* addCard(Card *card);

	Card* getCard(int position);

	bool isInDeck(Card *card);

	Card* getRandomCard();

};