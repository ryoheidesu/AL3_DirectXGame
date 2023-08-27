#include "Enemy.h"
#include "ImGuiManager.h"
#include "Input.h"
#include <cassert>
#include "MathUtility.h"
#include "Player.h"
#include "GameScene.h"


void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	textureHandle_ = textureHandle;
	worldTransform_.translation_.y = 3.0f;
	worldTransform_.translation_.z = 50.0f;
	ApproachInitialize();

}

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	
	textureHandle_ = textureHandle;
	worldTransform_.translation_ = pos;
	worldTransform_.translation_ = pos;
	ApproachInitialize();
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::Update() {

	
	//移動
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

	
}


void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
}


void Enemy::Fire() {
	assert(player_);
	const float kBulletSpeed = 1.0f;
	/*Vector3 velocity(0, 0, -kBulletSpeed);
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);*/
	Vector3 a = GetWorldPosition();
	Vector3 b = player_->GetWorldPosition();
	Vector3 c = {};
	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	float length = sqrtf(c.x * c.x + c.y * c.y + c.z * c.z);
	Vector3 dir = { c.x / length, c.y / length, c.z / length };

	Vector3 velocity(kBulletSpeed * dir.x, kBulletSpeed * dir.y, kBulletSpeed * dir.z);


	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	gamescene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize() {
	shotTimer_ = shotInterval_;
}

void Enemy::OnCollision() {
	isDead_ = true;
}