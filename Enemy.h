#pragma once
#include "Model.h"
#include "input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class Enemy {

public:
	enum class Phase {
		Approach,
		Leave,
	};

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);


private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	std::list<PlayerBullet*> bullets_;
	Phase phase_ = Phase::Approach;

};


