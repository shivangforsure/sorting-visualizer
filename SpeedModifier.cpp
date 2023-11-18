#include "stdafx.h"
#include "SpeedModifier.h"

// constructor:
SpeedModifier::SpeedModifier(
	float posX, float posY,
	float height,
	float maxValue, bool max_on_the_left,
	const char* axis_idle_path, const char* handle_idle_path,
	const char* axis_hover_path, const char* handle_hover_path,
	const char* axis_pressed_path, const char* handle_pressed_path)
{
	// wczytywanie textur osi:
	if (!this->axisTextures["IDLE"].loadFromFile(axis_idle_path) ||
		!this->axisTextures["HOVERED"].loadFromFile(axis_hover_path) ||
		!this->axisTextures["PRESSED"].loadFromFile(axis_pressed_path))
	{
		throw "ERROR: SPEEDMODIFIER::SPEEDMODIFIER: CANNOT LOAD AXIS TEXTURE FROM FILE";
	}

	// wczytywanie textur uchwytu: 
	if (!this->handleTextures["IDLE"].loadFromFile(handle_idle_path) ||
		!this->handleTextures["HOVERED"].loadFromFile(handle_hover_path) ||
		!this->handleTextures["PRESSED"].loadFromFile(handle_pressed_path))
	{
		throw "ERROR: SPEEDMODIFIER::SPEEDMODIFIER: CANNOT LOAD HANDLE TEXTURE FROM FILE";
	}

	// nadawanie texturom g³adkoœci:
	for (auto& it : this->axisTextures)
		it.second.setSmooth(true);
	
	for (auto& it : this->handleTextures)
		it.second.setSmooth(true);
	
	// tworzenie osi:	
	for (auto& it : this->axisTextures)
	{
		sf::Sprite temp;
		
		temp.setTexture(it.second);
		temp.scale(
			sf::Vector2f(
				height / temp.getGlobalBounds().height,
				height / temp.getGlobalBounds().height
			)
		);
		temp.setPosition(posX, posY);

		this->axes[it.first] = temp;
	}

	// tworzenie uchwytów:
	for (auto& it : this->handleTextures)
	{
		sf::Sprite temp;
		
		temp.setTexture(it.second);
		temp.scale(
			sf::Vector2f(
				height / temp.getGlobalBounds().height,
				height / temp.getGlobalBounds().height
			)
		);
		temp.setOrigin(0.f, 0.f);
		temp.setPosition(
			sf::Vector2f(
				this->axes["IDLE"].getGlobalBounds().left + this->axes["IDLE"].getGlobalBounds().width / 2.f - temp.getGlobalBounds().width / 2.f,
				this->axes["IDLE"].getGlobalBounds().top
			)
		);

		this->handles[it.first] = temp;
	}
	
	this->state = "IDLE";
	
	this->left = this->axes["IDLE"].getGlobalBounds().left;
	this->right = this->left + this->axes["IDLE"].getGlobalBounds().width;

	this->max_on_the_left = max_on_the_left;
	this->maxValue = maxValue;
}

// accessors:
float SpeedModifier::getValue() const
{
	return this->value;
}

float SpeedModifier::getMaxValue() const
{
	return this->maxValue;
}

// other methods:
void SpeedModifier::update(sf::Vector2i mousePosWindow)
{
	if (this->state == "IDLE") 
	{
		if (this->axes[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) || 
			this->handles[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->state = "HOVERED";
			this->axes[state].setTexture(this->axisTextures["HOVERED"]);
			this->handles[state].setTexture(this->handleTextures["HOVERED"]);
		}
	}
	else if (this->state == "HOVERED")
	{
		if (!this->axes[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) &&
			!this->handles[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->state = "IDLE";
			this->axes[this->state].setTexture(this->axisTextures["IDLE"]);
			this->handles[this->state].setTexture(this->handleTextures["IDLE"]);
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->state = "PRESSED";
				this->axes[this->state].setTexture(this->axisTextures["PRESSED"]);
				this->handles[this->state].setTexture(this->handleTextures["PRESSED"]);
			}
		}
	}
	else if(this->state == "PRESSED")
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->axes[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) ||
				this->handles[this->state].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			{
				this->state = "HOVERED";
				this->axes[this->state].setTexture(this->axisTextures["HOVERED"]);
				this->handles[this->state].setTexture(this->handleTextures["HOVERED"]);
			}
			else
			{
				this->state = "IDLE";
				this->axes[this->state].setTexture(this->axisTextures["IDLE"]);
				this->handles[this->state].setTexture(this->handleTextures["IDLE"]);
			}
		}
		else 
		{
			if (mousePosWindow.x >= this->left && mousePosWindow.x <= this->right)
				for (auto& it : this->handles)
					it.second.setPosition(
						sf::Vector2f(
							mousePosWindow.x - this->handles[this->state].getGlobalBounds().width / 2.f, 
							this->handles[this->state].getPosition().y
						)
					);
		}
	}

	// aktualizowanie wartoœci:
	float x = this->handles[this->state].getPosition().x + this->handles[this->state].getGlobalBounds().width / 2.f;

	if (this->max_on_the_left)
		this->value = this->maxValue * (this->right - x) / (this->right - this->left);
	else
		this->value = this->maxValue * (x - this->left) / (this->right - this->left);

	// minimalizowanie skrajnie ma³ych wartoœci do 0:
	if (this->value < 0.1f * this->maxValue)
		this->value = 0.f;
}

void SpeedModifier::render(sf::RenderTarget& target)
{
	target.draw(this->axes[this->state]);
	target.draw(this->handles[this->state]);
}
