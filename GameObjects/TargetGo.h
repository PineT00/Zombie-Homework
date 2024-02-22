#pragma once
#include "SpriteGo.h"
class TargetGo :
    public SpriteGo
{

protected:

public:
    TargetGo(const std::string& name = "");
    ~TargetGo() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

};

