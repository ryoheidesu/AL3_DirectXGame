#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:

	void Initialize(Model* model, const Vector3& position);


	void Update();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
};
