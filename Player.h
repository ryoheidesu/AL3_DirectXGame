#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"Input.h"
#include"PlayerBullet.h"

class Player {

private:

	WorldTransform worldTransform_;
	//ViewProjection viewProjection_;


	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;

	void Attack();

public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
};
