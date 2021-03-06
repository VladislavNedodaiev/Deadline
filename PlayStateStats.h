#pragma once

struct PlayStateStats
{

	// used for counter stats, such as health and joy
	static const int MAX = 100;
	static const int MIN = 0;

	// the amount of progress per update
	static const int PRG_HEALTH = -5;
	static const int PRG_JOY = -5;
	static const int PRG_MONEY = -5;
	static const int PRG_PROJECT = 10;

	// the amount of work needed for project to be done
	static const int PROJECT_WORK = 150;

	int health;
	int joy;
	int money;
	int project;
	int day;

	PlayStateStats();
	PlayStateStats(PlayStateStats &pss);
	
	PlayStateStats& operator=(PlayStateStats &pss);
	PlayStateStats& operator+(PlayStateStats &pss);
	PlayStateStats& operator+=(PlayStateStats &pss);

	PlayStateStats& update();
	PlayStateStats& update(bool project);
	PlayStateStats& update(int health,
						   int joy,
						   int money,
						   int project,
						   int day);
	PlayStateStats& update(PlayStateStats &pss);

	PlayStateStats& checkForMax();

	bool isAlive();

}; 