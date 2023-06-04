#pragma once

#include "Input.h"
#include "MathUtility.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>

class Player {

public:

	Vector3 GetWorldPosition() {
		Vector3 worldPos;

		worldPos.x = worldTransform_.translation_.x;
		worldPos.y = worldTransform_.translation_.y;
		worldPos.z = worldTransform_.translation_.z;

		return worldPos;
	};

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Attack();
	~Player();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	std::list<PlayerBullet*> bullets_;
};