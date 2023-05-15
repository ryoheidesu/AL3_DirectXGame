#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;

	textureHandle_ = TextureManager::Load("/cube/cube.jpg");
	velocity_ = velocity;
	worldTransform_.Initialize();
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;
	worldTransform_.translation_.z = position.z;
}

void PlayerBullet::Update() {

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	// 行列転送
	worldTransform_.TransferMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}