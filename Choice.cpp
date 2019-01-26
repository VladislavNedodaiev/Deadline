#include "Choice.h"

const int Choice::RANDOM_NEXT_CARD = -2;
const int Choice::NO_NEXT_CARD = -1;

Choice::Choice()
{
	
	this->nextCard = this->NO_NEXT_CARD;

	this->text = L"";

} // default constructor