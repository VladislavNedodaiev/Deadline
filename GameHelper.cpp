#include "GameHelper.h"

GameHelper::GameHelper()
{

	font.loadFromFile("Data/GameFont.ttf");

	isPlaying = true;
	resetWindow();

} // constructor

GameHelper::~GameHelper()
{

	renderWindow.close();

} // destructor

GameHelper& GameHelper::resetWindow()
{

	renderWindow.create(settings.getVideoMode(),
		settings.getWindowName(),
		settings.getWindowStyle(),
		settings.getContextSettings());

	_view.reset(sf::FloatRect(0, 0, settings.WINDOW_SIZEX, settings.WINDOW_SIZEY));
	setLetterboxView();

	return *this;

} // resetWindow()

GameHelper& GameHelper::setLetterboxView()
{

	float windowRatio = renderWindow.getSize().x / (float)renderWindow.getSize().y;
	float viewRatio = _view.getSize().x / (float)_view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;
	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.0;
	} // if (horizontalSpacing) 
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.0;
	} // else
	_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	renderWindow.setView(_view);

	return *this;

} // setLetterboxView()