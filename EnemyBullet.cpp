#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	model_ = model;
	velocity_ = velocity;
	textureHandle_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;
	worldTransform_.translation_.z = position.z;
}

void EnemyBullet::Update() {

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	worldTransform_.UpdateMatrix();

	/*if (--deathTimer_ <= 0) {
		isDead_ = true;
	}*/
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}