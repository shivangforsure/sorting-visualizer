#pragma once

#include "Set.h"
#include "Button.h"
#include "Switch.h"
#include "SpeedModifier.h"

class Set;
class Button;
class Switch;
class SpeedModifier;

class App
{
private:
	float delay; // minimalny czas jaki musi up³yn¹æ pomiêdzy dwoma kolejnymi krokami sortowania
	float timer; // przechowuje pomiary czasu
	sf::Clock clock; // s³u¿y do mierzenia czasu

	bool endApp;

	sf::RenderWindow* window;
	sf::VideoMode videoMode; // wymiary okna (oraz inne mniej wa¿ne rzeczy)
	sf::Vector2i mousePosWindow;

	Set* set; // zawiera zbiór liczb oraz zarz¹dza jego sortowaniem oraz wizualizacj¹

	std::map<std::string, Switch*> leftSwitches; // STOP
	std::map<std::string, Button*> leftButtons; // RESTART, NEW SET, EXIT
	std::map<std::string, Switch*> rightSwitches; // BUBBLE, SELECTION, HEAP, QUICK	

	SpeedModifier* speedModifier;

	sf::Font font;

	// private methods:
	void initVariables();
	void initWindow();
	void initSet();
	void initButtons();
	void initSpeedModifier();

public:
	// constructor / destructor:
	App();
	~App();

	void updateDt(); // updates delta time

	void update();
	void updateSfmlEvents();
	void updateMousePos();
	void updateSpeedModifier();
	void updateButtons();
	void updateSorting();

	void render();

	void run(); // everything happens here
};