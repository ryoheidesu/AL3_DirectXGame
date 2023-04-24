#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Player {

private:

	WorldTransform worldtransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;


public:


	void Initialize();


	void Update();

	void Draw();




};
