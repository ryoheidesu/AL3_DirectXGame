#pragma once
#include <ImGuiManager.h>
#include <Model.h>
#include <Sprite.h>

class Ui {
public:
	void Initialize();

	~Ui();

	void Draw();

private:
	Sprite* spriteTitle_ = nullptr;
};
