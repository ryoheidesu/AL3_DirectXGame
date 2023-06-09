#pragma once
#include "Model.h"
#include "WorldTransform.h"

class PlayerBullet {

public:

	Vector3 GetWorldPosition();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

	void OnCollision();

	float GetRadius() { return radius_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	float radius_ = 1.0f;
};