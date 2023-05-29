#include "Enemy.h"
#include "ImGuiManager.h"
#include "Input.h"
#include <cassert>
#include "MathUtility.h"



void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	textureHandle_ = textureHandle;
	worldTransform_.translation_.y = 3.0f;
	worldTransform_.translation_.z = 50.0f;
	Fire();
	ApproachInitialize();

}


void Enemy::Update() {

	/*bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});*/

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
		shotTimer_--;

		if (shotTimer_ <= 0) {
			Fire();

			shotTimer_ = kFireInterval;
		}

		worldTransform_.translation_.z -= 0.3f;

		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		
		}
		break;

    case Phase::Leave:
		worldTransform_.translation_.y += 0.3f;
		break;
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}


void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}


void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
}

void Enemy::ApproachInitialize() {
	shotTimer_ = shotInterval_;
}