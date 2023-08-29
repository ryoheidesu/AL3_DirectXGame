#include "Score.h"
#include <stdio.h>

void Score::Initialize() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] = nullptr;
		}
	};
	uint32_t textureNum[10] = {
	    TextureManager::Load("num/0.png"), TextureManager::Load("num/1.png"),
	    TextureManager::Load("num/2.png"), TextureManager::Load("num/3.png"),
	    TextureManager::Load("num/4.png"), TextureManager::Load("num/5.png"),
	    TextureManager::Load("num/6.png"), TextureManager::Load("num/7.png"),
	    TextureManager::Load("num/8.png"), TextureManager::Load("num/9.png"),
	};
	float posX = 1250;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] =
			    Sprite::Create(textureNum[j], {posX, 30}, {1, 1, 1, 1}, {(1.0f), (0.0f)});
		}
		posX -= 50;
	}
}

void Score::DrawScoreUI(int score) {
	int aa[6];
	int bb = 0;
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			bb = 100000;
		}
		aa[i] = score / bb;
		score -= aa[i] * bb;
		bb /= 10;
	}
	sprite2DNum_[0][aa[5]]->Draw();
	sprite2DNum_[1][aa[4]]->Draw();
	sprite2DNum_[2][aa[3]]->Draw();
	sprite2DNum_[3][aa[2]]->Draw();
	sprite2DNum_[4][aa[1]]->Draw();
	sprite2DNum_[5][aa[0]]->Draw();
}

Score::~Score() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			delete sprite2DNum_[i][j];
		}
	}
}