#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"
#include "RailCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//衝突判定と応答
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// テクスチャハンドル
	uint32_t textureHandleP_ = 0;
	uint32_t textureHandleE_ = 0;
	// モデル
	Model* model_ = nullptr;

	Player* player_ = nullptr;

	Enemy* enemy_ = nullptr;

	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;




};
