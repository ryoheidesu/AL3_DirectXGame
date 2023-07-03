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
#include <sstream>

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
	/// 敵弾を追加
	/// </summary>
	/// <param name="enemybullet"></param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵を追加
	/// </summary>
	/// <param name="enemybullet"></param>
	void AddEnemy(Enemy* enemy);
	
	void AddEnemy(Vector3 pos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//衝突判定と応答
	void CheckAllCollisions();

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	//敵発生コマンド
	std::stringstream enemyPopCommands;


private:
	
	// メンバ変数
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

	std::list<Enemy*> enemys_;
	//敵弾
	std::list<EnemyBullet*> enemyBullets_;

	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	bool waitFlag = false;

	int waitTimer = 120;


};
