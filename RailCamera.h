#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Matrix4x4.h"

class RailCamera {
public:

	void Initialize(Vector3 trans,Vector3 rot);


	void Update();


	ViewProjection GetViewProjection() { return viewProjection_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	
};
