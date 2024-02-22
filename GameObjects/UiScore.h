#pragma once
#include "TextGo.h"

class UiScore :
    public TextGo
{
protected:
    std::string textFormat = "SCORE = ";
    int score = 0;

public:
    UiScore(const std::string& name = "");

    void Reset() override;

    void SetScore(int score);

    void AddScore(int addedScore);
};

