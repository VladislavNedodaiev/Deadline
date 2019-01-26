#pragma once

struct PlayStateStats
{

	// used for counter stats, such as health and joy
	static const int MAX = 100;
	static const int MIN = 0;

	// the amount of work needed for project to be done
	static const int PROJECT_WORK = 100;

	int health;
	int joy;
	int money;
	int project;

	PlayStateStats();

}; 