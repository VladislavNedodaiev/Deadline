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
	this->day = 0;

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
	this->day = pss.day;

	this->checkForMax();

	return *this;

} // =

PlayStateStats& PlayStateStats::operator+(PlayStateStats &pss)
{

	PlayStateStats st;
	st += pss;

	return st;

} // +

PlayStateStats& PlayStateStats::operator+=(PlayStateStats &pss)
{

	this->health += pss.health;
	this->joy += pss.joy;
	this->money += pss.money;
	this->project += pss.project;
	this->day += pss.day;

	this->checkForMax();

	return *this;

} // +=

PlayStateStats& PlayStateStats::update()
{
	if (this->money >= 0)
	{
		this->health += this->PRG_HEALTH;
		this->joy += this->PRG_JOY;
	} // if
	else
	{
		this->health += this->PRG_HEALTH * 2;
		this->joy += this->PRG_JOY * 2;
	} // else

	this->money += this->PRG_MONEY;
	this->day += 1;

	this->checkForMax();

	return *this;

} // update

PlayStateStats& PlayStateStats::update(bool project)
{

	if (this->money >= 0)
	{
		this->health += this->PRG_HEALTH;
		this->joy += this->PRG_JOY;
	} // if
	else
	{
		this->health += this->PRG_HEALTH * 2;
		this->joy += this->PRG_JOY * 2;
	} // else
	this->money += this->PRG_MONEY;
	if (project)
		this->project += this->PRG_PROJECT * this->joy / this->MAX;
	this->day += 1;

	this->checkForMax();

	return *this;

} // update

PlayStateStats& PlayStateStats::update(int health,
	int joy,
	int money,
	int project,
	int day)
{

	this->health += health;
	this->joy += joy;
	this->money += money;
	this->project += project;
	this->day += day;

	this->checkForMax();

	return *this;

} // update

PlayStateStats& PlayStateStats::update(PlayStateStats &pss)
{

	*this += pss;
	return (this->checkForMax());

} // update

PlayStateStats& PlayStateStats::checkForMax()
{
	
	if (this->health > this->MAX)
		this->health = this->MAX;
	if (this->joy > this->MAX)
		this->joy = this->MAX;

	return *this;

} // check for max

bool PlayStateStats::isAlive()
{

	return (this->health > this->MIN && this->joy > this->MIN);

} // isAlive