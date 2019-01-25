#include "State.h"

State::State(GameHelper &gameHelper)
{

	this->_gameHelper = &gameHelper;
	this->toDelete = false;

} // constructor

State::~State() {} // destructor