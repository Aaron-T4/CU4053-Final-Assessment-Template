#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Background :
    public GameObject
{
    sf::Texture GameBackground;
public:

    Background();
    ~Background();

    void update(float dt) override;
    void handleInput(float dt) override;




};

