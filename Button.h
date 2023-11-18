#pragma once

enum ButtonState { BTN_IDLE = 0, BTN_HOVERED, BTN_PRESSED };

class Button
{
private:
	bool pressBlockade; // blokuje podw�jne klikni�cia
	bool clicked; // prawda je�eli przycisk zosta� klikni�ty w ci�gu ostatniej klatki
	unsigned short state;

	sf::RectangleShape rect;

	sf::Font font;
	sf::Text text;
	
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

	sf::Color outlineColor;

public:
	// constructor:
	Button(
		float posX, float posY,
		float sizeX, float sizeY,
		sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
		sf::Color outlineColor, int outlineThickness,
		sf::Font& font, std::string text, int textSize, sf::Color textColor
	);

	// predicates:
	bool isClicked() const; // zwraca warto�� zmiennej "clicked"

	// other methods:
	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget& target);
};