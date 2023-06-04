#pragma once
#include "Model.h"
#include "input.h"
#include "EnemyBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

class Enemy {

public:

	Vector3 GetWorldPosition() {
		Vector3 worldPos;

		worldPos.x = worldTransform_.translation_.x;
		worldPos.y = worldTransform_.translation_.y;
		worldPos.z = worldTransform_.translation_.z;

		return worldPos;
	};

	enum class Phase {
		Approach,
		Leave,
	};

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Fire();

	static const int kFireInterval = 60;
	void ApproachInitialize();

	void SetPlayer(Player* player) { player_ = player; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	std::list<EnemyBullet*> bullets_;
	Phase phase_ = Phase::Approach;
	int32_t shotTimer_ = 60;
	int32_t shotInterval_ = 60;
	Player* player_ = nullptr;
};


