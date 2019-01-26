#include "PlayStateStats.h"

const int PlayStateStats::MAX;
const int PlayStateStats::MIN;
const int PlayStateStats::PROJECT_WORK;

PlayStateStats::PlayStateStats()
{

	this->health = 0;
	this->joy = 0;
	this->money = 0;
	this->project = 0;

} // default constructor

PlayStateStats::PlayStateStats(PlayStateStats &pss)
{

	this->operator=(pss);

} // constructor

PlayStateStats& PlayStateStats::operator=(PlayStateStats &pss)
{

	this->health = pss.health;
	this->joy = pss.joy;
	this->money = pss.money;
	this->project = pss.project;

	return *this;

} // =

PlayStateStats& PlayStateStats::operator+(PlayStateStats &pss)
{

	return PlayStateStats() + pss;

} // +

PlayStateStats& PlayStateStats::operator+=(PlayStateStats &pss)
{

	this->health += pss.health;
	this->joy += pss.joy;
	this->money += pss.money;
	this->project += pss.project;

	return *this;

} // +=

PlayStateStats& PlayStateStats::update()
{

	this->health += this->PRG_HEALTH;
	this->joy += this->PRG_JOY;
	this->money += this->PRG_MONEY;

	return *this;

} // update

PlayStateStats& PlayStateStats::update(bool project)
{

	this->health += this->PRG_HEALTH;
	this->joy += this->PRG_JOY;
	this->money += this->PRG_MONEY;
	if (project)
		this->project += this->PRG_PROJECT;

	return *this;

} // update

PlayStateStats& PlayStateStats::update(int health,
	int joy,
	int money,
	int project)
{

	this->health += health;
	this->joy += joy;
	this->money += money;
	this->project += project;

	return *this;

} // update

PlayStateStats& PlayStateStats::update(PlayStateStats &pss)
{

	return (*this += pss);

} // update

bool PlayStateStats::isAlive()
{

	return (this->health > this->MIN && this->joy > this->MIN);

} // isAlive