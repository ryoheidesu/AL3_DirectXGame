#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:

	void Initialize(Vector3 trans,Vector3 rot);


	void Update();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	
};
