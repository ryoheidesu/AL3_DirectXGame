#pragma once

#include "Input.h"
#include "MathUtility.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include <list>

class Player {

public:
	
	

	/// <summary>
	/// ワールド座標
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	/// <param name="trans"></param>
	void Initialize(Model* model, uint32_t textureHandle,const Vector3& trans);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection& viewProjection);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);
	void DrawUI();

	/// <summary>
	///　攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 自機デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 当たり判定
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 自機の弾
	/// </summary>
	/// <returns></returns>
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	/// <summary>
	/// 半径
	/// </summary>
	/// <returns></returns>
	float GetRadius() { return radius_; }
	
	/// <summary>
	/// 親子関係を作る
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	std::list<PlayerBullet*> bullets_;
	float radius_ = 1.0f;
	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3Dreticle_;
	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
};