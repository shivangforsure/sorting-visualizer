#include "stdafx.h"
#include "Button.h"

// constructor:
Button::Button(
	float posX, float posY,
	float sizeX, float sizeY,
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
	sf::Color outlineColor, int outlineThickness,
	sf::Font& font, std::string text, int textSize, sf::Color textColor)
{
	this->pressBlockade = false;
	this->clicked = false;
	this->state = BTN_IDLE;

	this->rect.setPosition(posX, posY);
	this->rect.setSize(sf::Vector2f(sizeX, sizeY));
	this->rect.setOutlineThickness(outlineThickness);
	this->rect.setOutlineColor(outlineColor);
	this->rect.setFillColor(idleColor);

	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(textSize);
	this->text.setFillColor(textColor);

	// wyœrodkowywanie tekstu:
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	this->text.setPosition(
		sf::Vector2f(
			this->rect.getPosition().x + this->rect.getSize().x / 2, 
			this->rect.getPosition().y + this->rect.getSize().y / 2
		)
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->outlineColor = outlineColor;
}

// predicates:
bool Button::isClicked() const 
{
	return this->clicked;
}

// other methods:
void Button::update(sf::Vector2i mousePosWindow)
{
	this->clicked = false;

	if (this->state == BTN_PRESSED)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->pressBlockade = false;
			
			if (this->rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
				this->state = BTN_HOVERED;
			else
				this->state = BTN_IDLE;
		}
	}
	else if (this->state == BTN_HOVERED)
	{
		if (!this->rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->state = BTN_IDLE;
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->pressBlockade)
			{
				this->pressBlockade = true;
				this->state = BTN_PRESSED;
				this->clicked = true;
			}
		}
	}
	else if (this->state == BTN_IDLE)
	{
		if (this->rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->state = BTN_HOVERED;
	}
	
	if (this->state == BTN_PRESSED)
	{
		this->rect.setFillColor(this->pressedColor);
	}
	else if (this->state == BTN_HOVERED)
	{
		this->rect.setFillColor(this->hoverColor);
	}
	else if (this->state == BTN_IDLE)
	{
		this->rect.setFillColor(this->idleColor);
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->rect);
	target.draw(this->text);
}