#pragma once

class SpeedModifier
{
private:
	std::map<std::string, sf::Texture> axisTextures;
	std::map<std::string, sf::Texture> handleTextures;

	std::map<std::string, sf::Sprite> axes;
	std::map<std::string, sf::Sprite> handles;

	std::string state;
	
	// po�o�enie (w pikselach) lewej i prawej kraw�dzi osi:
	float left;
	float right;
	
	bool max_on_the_left; // je�eli prawda to warto�� zwi�kszamy przesuwaj�c uchwyt w lewo (dla false w prawo)
	float maxValue; // maksymalna warto�� jaka mo�e zwr�ci� suwak

	float value; // warto�� jak� zwraca suwak

public:
	// constructor:
	SpeedModifier(
		float posX, float posY,
		float height,
		float maxValue, bool max_on_the_left,
		const char* axis_idle_path, const char* handle_idle_path,
		const char* axis_hover_path, const char* handle_hover_path,
		const char* axis_pressed_path, const char* handle_pressed_path
	);

	// accessors:
	float getValue() const;
	float getMaxValue() const;

	// other methods:
	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget& target);
};

