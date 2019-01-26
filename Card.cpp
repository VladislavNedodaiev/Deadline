#include "Card.h"

Card::Card()
{

	this->cardtext = L"";

} // default constructor

Card::~Card()
{

	for (int i = 0; i < this->choices.size(); i++)
		delete this->choices[i];

	this->choices.clear();

} // destructor