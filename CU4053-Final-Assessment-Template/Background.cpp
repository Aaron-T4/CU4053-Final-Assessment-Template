#include "Background.h"

Background::Background()
{
	GameBackground.loadFromFile("gfx/clouds.png");
	GameBackground.setRepeated(true);
	setTexture(&GameBackground);
	setSize(sf::Vector2f(2796, 1036));
	//setScale(0.5, 0.5);
}

Background::~Background()
{
}

void Background::update(float dt)
{
	static float offsetX = 0.0f;

	float scrollSpeed = 100.f;

	offsetX += scrollSpeed * dt;

	if (offsetX > GameBackground.getSize().x)
	{
		offsetX -= GameBackground.getSize().x;
	}
	setTextureRect(sf::IntRect(static_cast<int>(offsetX), 0, 2796, 1036));
}

void Background::handleInput(float dt)
{
}
