#include "BackGround.h"

BackGround::~BackGround() {
	delete spriteTitle_;
	delete spriteResult_;
}

void BackGround::Initialize() {
	// テクスチャ取得
	uint32_t texTitle = TextureManager::Load("Title.png");
	uint32_t texResult = TextureManager::Load("Result.png");
	// 生成
	spriteTitle_ = Sprite::Create(texTitle, {0, 0}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
	spriteResult_ = Sprite::Create(texResult, {0, 0}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
}

void BackGround::Draw(int type) {
	if (type == 0) {
		spriteTitle_->Draw();
	} else if (type == 1) {
		spriteResult_->Draw();
	}
}
