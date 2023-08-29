#pragma once
#include <Model.h>
#include <Sprite.h>

class Score {
public:
	/// <summary>
	/// initialize
	/// </summary>
	void Initialize();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score();

	void DrawScoreUI(int score);

private:
	Sprite* sprite2DNum_[6][10];
};