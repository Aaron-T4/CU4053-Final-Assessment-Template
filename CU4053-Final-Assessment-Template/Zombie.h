#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Zombie :
    public GameObject
{

    sf::Texture zombieTexture;
    Animation walk;

public:
    Zombie();
    ~Zombie();

    void update(float dt) override;
    void handleInput(float dt) override;


};

