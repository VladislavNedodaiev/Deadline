#include "GameStateManager.h"

GameStateManager::GameStateManager(GameHelper &gameHelper)
{

	this->_gameHelper = &gameHelper;

} // constructor

GameStateManager::~GameStateManager()
{

	this->clear();

} // destructor

GameStateManager& GameStateManager::clear()
{

	this->_states.clear();

	return *this;

} // clear gsm 

GameStateManager& GameStateManager::pushState(State *state)
{

	_states.push_back(state);

	return *this;

} // push state (without popping)

GameStateManager& GameStateManager::setState(State *state)
{

	this->popState();
	this->pushState(state);

	return *this;

} // pop current state and push new

GameStateManager& GameStateManager::popState()
{

	if (_states.size() > 0)
	{
		delete _states[_states.size() - 1];
		_states.pop_back();
	}

	return *this;

} // pop current state

unsigned long long GameStateManager::getStatesCount()
{

	return _states.size();

} // getting current states count

GameStateManager& GameStateManager::input()
{

	if (_states.size() > 0)
	{
		State *st = &_states[_states.size() - 1]->input();
		if (st != _states[_states.size() - 1])
			pushState(st);
		if (_states[_states.size() - 1]->toDelete)
			popState();
	}

	return *this;

} // input into current state

GameStateManager& GameStateManager::update(float dt)
{

	if (_states.size() > 0)
	{
		_states[_states.size() - 1]->update(dt);
		if (_states[_states.size() - 1]->toDelete)
			popState();
	} // if

	return *this;

} // update current state

GameStateManager& GameStateManager::render()
{

	if (_states.size() > 0)
		_states[_states.size() - 1]->render();

	return *this;

} // render current state