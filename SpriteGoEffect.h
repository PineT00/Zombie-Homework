#pragma once
#include "SpriteGo.h"
class SpriteGoEffect :
    public SpriteGo
{
protected:
    float duration = 3.f;
    float timer = 0.f;

public:
    SpriteGoEffect(const std::string& name = "");
    ~SpriteGoEffect() = default;

    void SetDuration(float s) { duration = s; }

    void Reset();

    void Update(float dt);
};

