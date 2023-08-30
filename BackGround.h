#pragma once
#include <ImGuiManager.h>
#include <Model.h>
#include <Sprite.h>

class BackGround {
public:
	void Initialize();

	~BackGround();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="type">０タイトル　１リザルト</param>
	void Draw(int type);

private:
	Sprite* spriteTitle_ = nullptr;
	Sprite* spriteResult_ = nullptr;
};
