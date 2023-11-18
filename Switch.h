#pragma once

class Switch
{
private:
	bool pressBlockade; // blokuje podw�jne klikni�cia
	bool change; // prawda je�eli OSTATNIE wywo�anie funkcji update zmieni�o stan przycisku (on/off) 
	bool on;
	bool hovered; // prawda je�eli kursor myszki jest nad przyciskiem
	
	sf::RectangleShape rect;

	sf::Font font;
	sf::Text text;
	
	sf::Color on_idle_color;
	sf::Color on_hover_color;
	sf::Color off_idle_color;
	sf::Color off_hover_color;

	sf::Color on_outline_color;
	sf::Color off_outline_color;

public:
	// constructor:
	Switch(
		float posX, float posY,
		float sizeX, float sizeY,
		sf::Color on_idle_color, sf::Color on_hover_color, sf::Color off_idle_color, sf::Color off_hover_color,
		sf::Color on_outline_color, sf::Color of_outline_color, int outlineThickness,
		sf::Font& font, std::string text, int textSize, sf::Color textColor, bool on
	);
	
	// predictors:
	bool getChange() const; // zwraca warto�� zmiennej "change"
	bool isTurnedOn() const; // zwraca warto�� zmiennej "on", czyli czy przycisk jest w��czony

	// modifiers:
	void setOn(bool on); // pozwala na r�czn� zmian� stanu przycisku
	
	// other methods: 
	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget& target);
};
