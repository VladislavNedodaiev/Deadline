#include "PlayState.h"

PlayState::PlayState(GameHelper &gameHelper) :
	State(gameHelper),
	_projectBar(sf::Vector2f(1080, 60), sf::Color::Green, 0, sf::Color::Cyan)
{

	this->loadContent().initialize();

} // constructor

PlayState::~PlayState()
{

	this->unloadContent();

} // destructor

PlayState& PlayState::initialize()
{

	this->_backgroundObject.setAnimation(this->_backgroundSheet.getSheet()).setSize(sf::Vector2f(1920, 1080));

	this->_textinfo.font = &this->_gameHelper->font;
	this->_textinfo.characterSize = 32;
	this->_textinfo.horizontalAlign = this->_textinfo.Middle;
	this->_textinfo.verticalAlign = this->_textinfo.Center;

	this->_cardObject = new CardObject(this->_panelSheet.getSheet(),
									   this->_buttonSheet.getSheet());
	this->_cardObject->textinfo = this->_textinfo;
	this->_cardObject->setCard(this->_deck.getRandomCard());

	this->_stats.health = 75;
	this->_stats.joy = 75;
	this->_stats.money = 100;
	this->_stats.project = 0;

	
	this->_textinfo.characterSize = 96;
	this->_dayText = "DAY " + std::to_string(this->_stats.day);
	this->_dayText.setTextInfo(this->_textinfo);
	this->_dayText.setPosition(BasicSettings::WINDOW_SIZEX / 2.0, this->_cardObject->getGlobalBounds().top + 100);

	this->_textinfo.characterSize = 64;
	this->_textinfo.horizontalAlign = this->_textinfo.Left;

	this->_healthObject.setAnimation(this->_healthSheet.getSheet()).setSize(sf::Vector2f(80, 80)).setPosition(this->_cardObject->getGlobalBounds().left, 20);
	this->_healthText.setTextInfo(this->_textinfo).setPosition(this->_cardObject->getGlobalBounds().left + this->_healthObject.getGlobalBounds().width * 1.5, 20 + this->_healthObject.getGlobalBounds().height / 2);
	this->_healthText = std::to_string(this->_stats.health) + "%";

	this->_joyObject.setAnimation(this->_joySheet.getSheet()).setSize(sf::Vector2f(80, 80)).setPosition(this->_cardObject->getGlobalBounds().left + this->_cardObject->getGlobalBounds().width / 3.0, 20);
	this->_joyText.setTextInfo(this->_textinfo).setPosition(this->_cardObject->getGlobalBounds().left + this->_cardObject->getGlobalBounds().width / 3.0 + this->_joyObject.getGlobalBounds().width * 1.5, 20 + this->_joyObject.getGlobalBounds().height / 2);
	this->_joyText = std::to_string(this->_stats.joy) + "%";

	this->_moneyObject.setAnimation(this->_moneySheet.getSheet()).setSize(sf::Vector2f(80, 80)).setPosition(this->_cardObject->getGlobalBounds().left + this->_cardObject->getGlobalBounds().width / 3.0 * 2.0, 20);
	this->_moneyText.setTextInfo(this->_textinfo).setPosition(this->_cardObject->getGlobalBounds().left + this->_cardObject->getGlobalBounds().width / 3.0 * 2.0 + this->_moneyObject.getGlobalBounds().width * 1.5, 20 + this->_moneyObject.getGlobalBounds().height / 2);
	this->_moneyText = std::to_string(this->_stats.money);

	this->_textinfo.characterSize = 32;
	this->_textinfo.horizontalAlign = this->_textinfo.Middle;

	this->_projectBar.setPosition(sf::Vector2f(this->_gameHelper->settings.WINDOW_SIZEX / 2 - this->_projectBar.getSize().x / 2,
											   this->_gameHelper->settings.WINDOW_SIZEY - this->_projectBar.getSize().y * 1.5));
	this->_projectText.setTextInfo(this->_textinfo);
	this->_projectText.setPosition(sf::Vector2f(this->_gameHelper->settings.WINDOW_SIZEX / 2,
												this->_gameHelper->settings.WINDOW_SIZEY - this->_projectBar.getSize().y));
	this->_projectText = L"Project readiness indicator";

	this->_music.setLoop(true);
	this->_music.play();

	return *this;

} // initializing

PlayState& PlayState::loadContent()
{

	this->_backgroundSheet.load("Data/background_sheet.png");
	this->_panelSheet.load("Data/panel_sheet.png");
	this->_buttonSheet.load("Data/button_sheet.png");

	this->_healthSheet.load("Data/health_sheet.png");
	this->_joySheet.load("Data/joy_sheet.png");
	this->_moneySheet.load("Data/money_sheet.png");

	this->_deck.loadFromFile("Data/deck.dat");

	this->_music.openFromFile("Data/game.ogg");
	this->_music.stop();

	return *this;

} // loading

PlayState& PlayState::unloadContent()
{

	delete _cardObject;
	this->_music.stop();

	return *this;

} // unloading

State& PlayState::input()
{

	sf::Vector2i mousePos = sf::Vector2i(_gameHelper->renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_gameHelper->renderWindow)));

	if (this->_cardObject != nullptr)
	{

		int inp = this->_cardObject->input(this->_gameHelper->event, mousePos);
		if (inp)
		{

			Card *card = this->_cardObject->getCard();
			if (card != nullptr)
			{
				inp--;
				if (card->choices.size() > inp)
				{
					this->_stats += card->choices[inp]->stats;
					this->_projectBar.setRate((float)this->_stats.project / (float)this->_stats.PROJECT_WORK);
					this->_healthText = std::to_string(this->_stats.health) + "%";
					this->_joyText = std::to_string(this->_stats.joy) + "%";
					this->_moneyText = std::to_string(this->_stats.money);
					this->_dayText = "DAY " + std::to_string(this->_stats.day);
					if (!(this->_stats.isAlive()) || this->_stats.project >= this->_stats.PROJECT_WORK)
					{

						State *state;

						if (this->_stats.health <= 0)
						{

							sf::String musicpath = L"Data/bad_end.ogg";
							sf::String endText = L"YOU DIED";
							state = new EndGame(*this->_gameHelper, endText, sf::Color(200, 100, 100, 255), musicpath);

						} // if
						else if (this->_stats.joy <= 0)
						{

							sf::String musicpath = L"Data/bad_end.ogg";
							sf::String endText = L"SUICIDE COMMITTED";
							state = new EndGame(*this->_gameHelper, endText, sf::Color(200, 100, 100, 255), musicpath);

						} // else if
						else
						{

							sf::String musicpath = L"Data/good_end.ogg";
							sf::String endText = L"PROJECT DONE!";
							state = new EndGame(*this->_gameHelper, endText, sf::Color(100, 200, 100, 255), musicpath);

						} // done!

						this->_music.stop();
						this->toDelete = true;
						return *state;

					} // if
					else if (card->choices[inp]->nextCard != Choice::NO_NEXT_CARD)
					{

						if (card->choices[inp]->nextCard == Choice::RANDOM_NEXT_CARD)
							this->_cardObject->setCard(this->_deck.getRandomCard());
						else
							this->_cardObject->setCard(this->_deck.getCard(card->choices[inp]->nextCard));

					} // else if
					else
					{

						this->_stats.update();
						this->_projectBar.setRate((float)this->_stats.project / (float)this->_stats.PROJECT_WORK);
						this->_healthText = std::to_string(this->_stats.health) + "%";
						this->_joyText = std::to_string(this->_stats.joy) + "%";
						this->_moneyText = std::to_string(this->_stats.money);
						this->_dayText = "DAY " + std::to_string(this->_stats.day);
						if (!(this->_stats.isAlive()) || this->_stats.project >= this->_stats.PROJECT_WORK)
						{

							State *state;

							if (this->_stats.health <= 0)
							{

								sf::String musicpath = L"Data/bad_end.ogg";
								sf::String endText = L"YOU DIED";
								state = new EndGame(*this->_gameHelper, endText, sf::Color(200, 100, 100, 255), musicpath);

							} // if
							else if (this->_stats.joy <= 0)
							{

								sf::String musicpath = L"Data/bad_end.ogg";
								sf::String endText = L"SUICIDE COMMITTED";
								state = new EndGame(*this->_gameHelper, endText, sf::Color(200, 100, 100, 255), musicpath);

							} // else if
							else
							{

								sf::String musicpath = L"Data/good_end.ogg";
								sf::String endText = L"PROJECT DONE!";
								state = new EndGame(*this->_gameHelper, endText, sf::Color(100, 200, 100, 255), musicpath);

							} // done!

							this->_music.stop();
							this->toDelete = true;
							return *state;

						} // if
						this->_cardObject->setCard(this->_deck.getRandomCard());

					} // else

				} // if

			} // if

		} // if

	} // if

	return *this;

} // input

PlayState& PlayState::update(float dt)
{

	if (this->_music.getStatus() != this->_music.Playing)
		this->_music.play();

	this->_backgroundObject.update(dt);
	if (this->_cardObject != nullptr)
		this->_cardObject->update(dt);

	return *this;

} // updating

PlayState& PlayState::render()
{

	this->_backgroundObject.render(this->_gameHelper->renderWindow);
	if (this->_cardObject != nullptr)
		this->_cardObject->render(this->_gameHelper->renderWindow);

	this->_projectBar.render(this->_gameHelper->renderWindow);
	this->_projectText.render(this->_gameHelper->renderWindow);

	this->_healthObject.render(this->_gameHelper->renderWindow);
	this->_healthText.render(this->_gameHelper->renderWindow);

	this->_joyObject.render(this->_gameHelper->renderWindow);
	this->_joyText.render(this->_gameHelper->renderWindow);

	this->_moneyObject.render(this->_gameHelper->renderWindow);
	this->_moneyText.render(this->_gameHelper->renderWindow);

	this->_dayText.render(this->_gameHelper->renderWindow);

	return *this;

} // rendering