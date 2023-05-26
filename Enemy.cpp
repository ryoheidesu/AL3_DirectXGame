#include "Enemy.h"
#include "ImGuiManager.h"
#include "Input.h"
#include <cassert>

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	textureHandle_ = textureHandle;
	worldTransform_.translation_.y = 3.0f;
	worldTransform_.translation_.z = 50.0f;
	

}


void Enemy::Update() {
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	/*const float kCharacterSpeed = 0.02f;

	move.z -= kCharacterSpeed;

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;*/
	worldTransform_.UpdateMatrix();

	switch (phase_) {
	case Phase::Approach:
	default:

		worldTransform_.translation_.z -= 0.3f;

		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;

    case Phase::Leave:
		worldTransform_.translation_.y += 0.3f;
		break;
	}
}


void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}