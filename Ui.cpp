#include "Ui.h"

Ui::~Ui() { delete spriteTitle_; }

void Ui::Initialize() {
	// タイトルテクスチャ取得
	uint32_t texTitle = TextureManager::Load("Title.png");
	// 生成
	spriteTitle_ = Sprite::Create(texTitle, {0, 0}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
	spriteTitle_->SetPosition(Vector2(0, 0));
}

void Ui::Draw() { spriteTitle_->Draw(); }
