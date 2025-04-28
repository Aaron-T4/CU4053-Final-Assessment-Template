#include "Zombie.h"

Zombie::Zombie()
{
	zombieTexture.loadFromFile("gfx/animZombie.png");
	setSize(sf::Vector2f(55, 108));
	setPosition(300, 100);
	setTexture(&zombieTexture);
	// Setup walk animation.
	walk.addFrame(sf::IntRect(0, 0, 55, 108));
	walk.addFrame(sf::IntRect(55, 0, 55, 108));
	walk.addFrame(sf::IntRect(110, 0, 55, 108));
	walk.addFrame(sf::IntRect(165, 0, 55, 108));
	walk.addFrame(sf::IntRect(220, 0, 55, 108));
	walk.addFrame(sf::IntRect(275, 0, 55, 108));
	walk.addFrame(sf::IntRect(330, 0, 55, 108));
	walk.addFrame(sf::IntRect(385, 0, 55, 108));

	walk.setFrameSpeed(1.f / 10.f);
	//setTag("Player");
	setCollisionBox(0, 0, 55, 108);
}

Zombie::~Zombie()
{
}

void Zombie::update(float dt)
{
	setTextureRect(walk.getCurrentFrame());
}

void Zombie::handleInput(float dt)
{

	velocity.x = 0;

	if (input->isKeyDown(sf::Keyboard::A))
	{
		walk.setFlipped(true);
		walk.animate(dt);
		velocity.x = -200;
	}

	if (input->isKeyDown(sf::Keyboard::D))
	{
		walk.setFlipped(false);
		velocity.x = 200;
		walk.animate(dt);

	}
}
