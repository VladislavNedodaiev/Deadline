#include "Choice.h"

const int Choice::RANDOM_NEXT_CARD;
const int Choice::NO_NEXT_CARD;

Choice::Choice()
{
	
	this->nextCard = this->NO_NEXT_CARD;

	this->text = L"";

} // default constructor