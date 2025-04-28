#include "Mario.h"
Mario::Mario()
{

	setTag("Player");
	marioSpriteSheet.loadFromFile("gfx/MarioSheetT.png");
	setSize(sf::Vector2f(15 * 4, 21 * 4));
	setPosition(400, 100);
	setTexture(&marioSpriteSheet);



	Walk.addFrame(sf::IntRect(0, 0, 15, 21));
	Walk.addFrame(sf::IntRect(15, 0, 15, 21));
	Walk.addFrame(sf::IntRect(30, 0, 15, 21));
	Walk.addFrame(sf::IntRect(45, 0, 15, 21));
	Walk.setFrameSpeed(1.f / 10.f);


	Swim.addFrame(sf::IntRect(0, 21, 16, 20));
	Swim.addFrame(sf::IntRect(16, 21, 16, 20));
	Swim.addFrame(sf::IntRect(32, 21, 16, 20));
	Swim.setFrameSpeed(1.f / 4.f);

	Duck.addFrame(sf::IntRect(0, 44, 17, 17));
	Duck.setFrameSpeed(1.f / 2.f);

	currentAnimation = &Walk;
	setTextureRect(currentAnimation->getCurrentFrame());
}

Mario::~Mario()
{
}

void Mario::update(float dt)
{
}

void Mario::handleInput(float dt)
{
	velocity.x = 0;

	setTextureRect(currentAnimation->getCurrentFrame());


	if (input->isKeyDown(sf::Keyboard::Left))
	{
		currentAnimation->setFlipped(true);
		currentAnimation = &Walk;
		velocity.x = -200;
	}
	else if (input->isKeyDown(sf::Keyboard::Right))
	{
		currentAnimation->setFlipped(false);
		velocity.x = 200;
		currentAnimation = &Walk;

	}
	else if (input->isKeyDown(sf::Keyboard::Down))
	{
		currentAnimation = &Duck;
	}
	else if (input->isKeyDown(sf::Keyboard::Up))
	{
		currentAnimation = &Swim;
	}
	else
	{
		currentAnimation->reset();
		currentAnimation = &Walk;
	}

	if (input->isKeyDown(sf::Keyboard::Space) && canJump)
	{
		Jump(100.f);
		audio->playSoundbyName("jump");
	}
	currentAnimation->animate(dt);
}