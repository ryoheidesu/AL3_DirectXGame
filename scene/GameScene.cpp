#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <Player.h>
#include <Enemy.h>
#include <EnemyBullet.h>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	textureHandleP_ = TextureManager::Load("sample.png");
	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	textureHandleE_ = TextureManager::Load("sample.png");
	// 天球の生成
	skydome_ = new Skydome();
	
	
	// ビュープロジェクションの初期化
	


	// 読み込み
	// モデル生成
	model_ = Model::Create();
	player_->Initialize(model_, textureHandleP_);
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, textureHandleE_);
	
	//3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//　天球の初期化
	skydome_->Initialize(modelSkydome_);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	/*viewProjection_.farZ = 10.0f;
	viewProjection_.Initialize();*/
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// 敵キャラの更新
	enemy_->Update();
	CheckAllCollisions();

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}
#endif // DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵キャラの描画
	enemy_->Draw(viewProjection_);
	// 天球の描画
	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA,posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	//自キャラと敵弾の当たり判定
	#pragma region 
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet_ : enemyBullets) {
		posB = bullet_->GetWorldPosition();
		float dist = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		             (posB.z - posA.z) * (posB.z - posA.z);

		if (dist < (player_->GetRadius() + enemy_->GetRadius())) {
			player_->OnCollision();

			bullet_->OnCollision();
		}
	}

	
	#pragma endregion

	//自弾と敵キャラの当たり判定
	#pragma region
	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet_ : playerBullets) {
		posB = bullet_->GetWorldPosition();
		float dist = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		             (posB.z - posA.z) * (posB.z - posA.z);

		if (dist < (bullet_->GetRadius() + enemy_->GetRadius())) {
			enemy_->OnCollision();

			bullet_->OnCollision();
		}
	}
	#pragma endregion

	//自弾と敵弾の当たり判定
	#pragma region
	

	for (PlayerBullet* playerbullet_ : playerBullets) {
		for (EnemyBullet* enemybullet_ : enemyBullets) {
			posA = enemybullet_->GetWorldPosition();
			posB = playerbullet_->GetWorldPosition();
			float dist = (posB.x - posA.x) * (posB.x - posA.x) +
			             (posB.y - posA.y) * (posB.y - posA.y) +
			             (posB.z - posA.z) * (posB.z - posA.z);

			if (dist < (playerbullet_->GetRadius() + enemybullet_->GetRadius())) {
				enemybullet_->OnCollision();
				playerbullet_->OnCollision();
			}

		}
		
	}
	#pragma endregion
}

