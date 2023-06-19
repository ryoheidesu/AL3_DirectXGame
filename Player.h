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
	
	Vector3 GetWorldPosition();
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Attack();
	~Player();
	void OnCollision();
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }
	float GetRadius() { return radius_; }
	//void SetParent(const WorldTransform* parent);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	std::list<PlayerBullet*> bullets_;
	float radius_ = 1.0f;
};