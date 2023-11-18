#include "stdafx.h"
#include "Switch.h"

// constructor:
Switch::Switch(
	float posX, float posY,
	float sizeX, float sizeY,
	sf::Color on_idle_color, sf::Color on_hover_color, sf::Color off_idle_color, sf::Color off_hover_color,
	sf::Color on_outline_color, sf::Color off_outline_color, int outlineThickness,
	sf::Font& font, std::string text, int textSize, sf::Color textColor, bool on)
{
	this->pressBlockade = false;
	this->change = false;
	this->on = on;
	this->hovered = false;
	
	this->rect.setPosition(posX, posY);
	this->rect.setSize(sf::Vector2f(sizeX, sizeY));
	this->rect.setOutlineThickness(outlineThickness);

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
	
	if (on)
	{
		this->rect.setFillColor(on_idle_color);
		this->rect.setOutlineColor(on_outline_color);
	}
	else
	{
		this->rect.setFillColor(off_idle_color);
		this->rect.setOutlineColor(off_outline_color);
	}

	this->on_idle_color = on_idle_color;
	this->on_hover_color = on_hover_color;
	this->off_idle_color = off_idle_color;
	this->off_hover_color = off_hover_color;

	this->on_outline_color = on_outline_color;
	this->off_outline_color = off_outline_color;
}

// predictors:
bool Switch::getChange() const
{
	return this->change;
}

bool Switch::isTurnedOn() const
{
	return this->on;
}

// modifiers:
void Switch::setOn(bool on)
{
	this->on = on;
	
	if (this->on)
	{
		if (this->hovered)
			this->rect.setFillColor(this->on_hover_color);
		else
			this->rect.setFillColor(this->on_idle_color);

		this->rect.setOutlineColor(this->on_outline_color);
	}
	else
	{
		if (this->hovered)
			this->rect.setFillColor(this->off_hover_color);
		else
			this->rect.setFillColor(this->off_idle_color);

		this->rect.setOutlineColor(this->off_outline_color);
	}
}

// other methods: 
void Switch::update(sf::Vector2i mousePosWindow)
{
	this->change = false;
	
	if (this->rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->hovered = true;
		
		if (!this->pressBlockade && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->pressBlockade = true;
			this->change = true;

			if (this->on)
				this->on = false;
			else
				this->on = true;
		}
		else if (this->pressBlockade && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->pressBlockade = false;
	}
	else
		this->hovered = false;
	
	if (this->on)
	{
		if (this->hovered)
			this->rect.setFillColor(this->on_hover_color);
		else
			this->rect.setFillColor(this->on_idle_color);

		this->rect.setOutlineColor(this->on_outline_color);
	}
	else
	{
		if (this->hovered)
			this->rect.setFillColor(this->off_hover_color);
		else
			this->rect.setFillColor(this->off_idle_color);
		
		this->rect.setOutlineColor(this->off_outline_color);
	}
}

void Switch::render(sf::RenderTarget& target)
{
	target.draw(this->rect);
	target.draw(this->text);
}
